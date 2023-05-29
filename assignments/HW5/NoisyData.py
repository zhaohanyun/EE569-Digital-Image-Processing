import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

import torchvision as tv
import torchvision.transforms as transforms

import matplotlib.pyplot as plt
import numpy as np
import math
import os

train_batch_size = 64
test_batch_size = 1000

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")


class Net(nn.Module) :
    def __init__(self) :
        super(Net, self).__init__()

        self.conv1 = nn.Conv2d(1, 6, 5, stride=1, padding=2)
        self.conv2 = nn.Conv2d(6, 16, 5, stride=1, padding=0)
        self.fc1 = nn.Linear(16 * 5 * 5, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)

    def forward(self, x) :
        x = F.max_pool2d(F.relu(self.conv1(x)), 2)
        x = F.max_pool2d(F.relu(self.conv2(x)), 2)
        x = x.view(-1, self.num_flat_features(x))
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return x

    def num_flat_features(self, x) :
        # x is a 4D tensor
        x_size = x.size()[1 :]
        num = 1
        for n in x_size :
            num *= n
        return num


class myMNIST(torch.utils.data.Dataset) :
    def __init__(self, error, train=True) :
        self.e = error
        self.transform = transforms.Compose(
            [transforms.ToTensor(),
             transforms.Normalize((0.1307,), (0.3081,))])
        self.data_set = tv.datasets.MNIST(
            root='./data',
            train=train,
            download=True,
            transform=self.transform
        )
        # self.labelConfusionMatrix(self.e)

    def labelConfusionMatrix(self, e) :
        matrix = []
        for i in range(10) :
            matrix.append([1 - e if i == j else e / 9 for j in range(10)])
        print(np.around(matrix, decimals=3))

    def randomLabel(self, target, e) :
        elements = [i for i in range(10)]
        # print(target[1])
        probabilities = [1 - e if target[1] == i else e / 9 for i in range(10)]
        return np.random.choice(elements, 1, p=probabilities)[0]

    def __len__(self) :
        return len(self.data_set)

    def __getitem__(self, index) :
        # print((self.data_set[index]))
        newlabel = self.randomLabel(self.data_set[index], self.e)
        return (self.data_set[index][0], newlabel)


def load_data(error) :
    transform = transforms.Compose(
        [transforms.ToTensor(),
         transforms.Normalize((0.1307,), (0.3081,))])
    # train_set = tv.datasets.MNIST(
    #     root='./data',
    #     train=True,
    #     download=True,
    #     transform=transform
    # )
    train_set = myMNIST(error, True)
    train_loader = torch.utils.data.DataLoader(
        train_set,
        batch_size=train_batch_size,
        shuffle=True,
        num_workers=2)
    test_set = tv.datasets.MNIST(
        root='./data',
        train=False,
        download=True,
        transform=transform
    )
    test_loader = torch.utils.data.DataLoader(
        test_set,
        batch_size=test_batch_size,
        shuffle=False,
        num_workers=2)
    print("data loaded successfully...")
    return train_loader, test_loader


def accuracy(model, x, neg=False) :
    with torch.no_grad() :
        correct = 0
        total = 0
        class_correct = list(0. for i in range(10))
        class_total = list(0. for i in range(10))
        for data in x :
            images, labels = data
            if neg :
                images = -images
            images, labels = images.to(device), labels.to(device)
            outputs = model(images)
            _, predicted = torch.max(outputs.data, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()

        return (100 * correct / total)


def train(train_loader, test_loader, model, criterion, optimizer, epoch) :
    model.train()
    running_loss = 0
    for i, data in enumerate(train_loader, 0) :
        inputs, labels = data
        inputs, labels = inputs.to(device), labels.to(device)
        optimizer.zero_grad()
        outputs = net(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        # print statistics
        # running_loss += loss.item()
        # if i % 200 == 199 :
        #     print("[epoch %d, iter %5d] loss: %.3f" % (epoch + 1, i + 1, running_loss / 200))
        #     running_loss = 0.0
    # train_acc = accuracy(model, train_loader)
    test_acc = accuracy(model, test_loader)
    print("epoch %d: test_acc %.3f" % (epoch + 1, test_acc))

    # return train_acc, test_acc
    return test_acc


def display(train_acc, test_acc) :
    fig, ax = plt.subplots()
    ax.plot(range(1, len(train_acc) + 1), train_acc, color='r', label='train_acc')
    ax.plot(range(1, len(test_acc) + 1), test_acc, color='b', label='test_acc')
    ax.legend(loc='lower right')
    plt.show()


if __name__ == '__main__' :
    acc_in_diff_err = []
    for i in range(5) :
        error = i * 0.2
        print("error=%.1f" % error)
        test_acc = []
        for j in range(5) :  # run 5 times for each e
            print("#%d for error=%.1f start" % (j + 1, error))
            # input MNIST
            train_loader, test_loader = load_data(error)

            # new model
            net = Net().to(device)

            # training
            learning_rate = 0.01
            momentum = 0.9
            max_epoch = 10
            criterion = nn.CrossEntropyLoss()
            optimizer = optim.SGD(net.parameters(), lr=learning_rate, momentum=momentum)

            for epoch in range(max_epoch) :
                test_acc_t = train(train_loader, test_loader, net, criterion, optimizer, epoch)
                if epoch == max_epoch - 1 :
                    test_acc.append(test_acc_t)
                    print("#%d for error=%.1f finish" % (j + 1, error))
        acc_in_diff_err.append(test_acc)
    print(acc_in_diff_err)


#test accuracy=[[98.94, 98.96, 98.77, 99.02, 99.05], [98.88, 98.9, 98.92, 98.92, 99.04], [98.74, 98.72, 98.74, 98.88, 98.84], [98.44, 98.43, 98.58, 97.9, 97.98], [96.36, 96.25, 96.21, 94.37, 95.99]]
    plt.plot([0,0.2,0.4,0.6,0.8],[np.mean(acc_in_diff_err[i]) for i in range(5)])
    plt.xlabel("label error rate")
    plt.ylabel("test set accuracy")
    plt.xticks([0,0.2,0.4,0.6,0.8])
    for list in acc_in_diff_err :
        print(np.std(list))
