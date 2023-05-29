import torch
import torch.nn as nn
import torch.nn.functional as F
import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import confusion_matrix
import torchvision.transforms as transforms
import torchvision as tv

train_batch_size = 64
test_batch_size = 1000

class Net(nn.Module) :
    def __init__(self) :
        super(Net, self).__init__()

        self.conv1 = nn.Conv2d(1, 6, 5, stride=1, padding=2)
        self.conv2 = nn.Conv2d(6, 16, 5, stride=1, padding=0)
        self.fc1 = nn.Linear(16 * 5 * 5, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)
        self.dropout=nn.Dropout(0.2)

    def forward(self, x) :
        x = F.max_pool2d(F.relu(self.conv1(x)), 2)
        x = F.max_pool2d(F.relu(self.conv2(x)), 2)
        x = x.view(-1, self.num_flat_features(x))
        x = F.relu(self.fc1(x))
        #x=self.dropout(x)
        x = F.relu(self.fc2(x))
        #x=self.dropout(x)
        x = self.fc3(x)
        #x=F.softmax(x)
        return x

    def num_flat_features(self, x) :
        # x is a 4D tensor
        x_size = x.size()[1 :]
        num = 1
        for n in x_size :
            num *= n
        return num

def load_data() :
    transform = transforms.Compose(
        [transforms.ToTensor()
         #transforms.Normalize((0.5,), (0.5,))
         ])
    train_set = tv.datasets.FashionMNIST(
        root='./data',
        train=True,
        download=True,
        transform=transform
    )
    train_loader = torch.utils.data.DataLoader(
        train_set,
        batch_size=train_batch_size,
        shuffle=True,
        num_workers=2)
    test_set = tv.datasets.FashionMNIST(
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

def generate_ConfusionMatrix(model,test_loader):
    model.eval()#eval:do not use normalization and dropout
    pred=[]
    true=[]
    with torch.no_grad():
        for data,target in test_loader:
            data, target = data, target
            output = model(data).to('cpu')
            # print(np.reshape(output.argmax(dim=1, keepdim=True).numpy(),(100)).tolist())
            # print(target.to('cpu').numpy().tolist())
            pred+=np.reshape(output.argmax(dim=1, keepdim=True).numpy(),(test_batch_size)).tolist()
            true+=target.to('cpu').numpy().tolist()
    return confusion_matrix(true,pred,normalize='true')

model=torch.load('EE569FashionMNIST_CNN.pth')
train_loader, test_loader = load_data()
cm=generate_ConfusionMatrix(model,test_loader)
print(cm)
import seaborn as sns
sns.heatmap(cm)


def findConfusedPairs(model,test_loader):
    model.eval()#eval:do not use normalization and dropout
    shown=[False,False,False]
    with torch.no_grad():
        for data,target in test_loader:
            data, target = data, target
            output = model(data)
            # print(np.reshape(output.argmax(dim=1, keepdim=True).numpy(),(100)).tolist())
            # print(target.to('cpu').numpy().tolist())
            pred=np.reshape(output.argmax(dim=1, keepdim=True).numpy(),(test_batch_size))
            true=target.numpy()
            for i in range(test_batch_size):
                if (not shown[0]) and pred[i]==6 and target[i]==0:
                    displayImage(data[i],28)
                    shown[0]=True
                if (not shown[1]) and pred[i] == 0 and target[i] == 6 :
                    displayImage(data[i], 28)
                    shown[1] = True
                if (not shown[2]) and pred[i] == 4 and target[i] == 6 :
                    displayImage(data[i], 28)
                    shown[2] = True


def displayImage(data,width):
    image=data.reshape(width,width)
    plt.imshow(image)
    plt.show()

findConfusedPairs(model,test_loader)
