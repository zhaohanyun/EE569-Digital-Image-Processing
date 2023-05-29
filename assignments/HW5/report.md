### EE569 HW5   CNN Training on LeNet-5

#### Introduction

Convolutional neural network is popular today for image and speech recognition, and LeNet-5 is the earliest ancestor. It is designed by Lecun and others in 1998. The architecture is shown below. As one of the earliest convolutional neural networks, it promotes the development of deep learning, and defined the basic components in CNN. LeNet-5's most classical application is to recognize hand-written numbers (MNIST). In this assignment, apart from MNIST, we also apply it to FashionMNIST and CIFAR-10 datasets, and see how good it will perform.

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220414145543502.png" alt="image-20220414145543502" style="zoom: 50%;" />



![MNIST sample images](https://upload.wikimedia.org/wikipedia/commons/thumb/2/27/MnistExamples.png/320px-MnistExamples.png)

<center>MNIST dataset</center>

<img src="https://www.researchgate.net/profile/Saeed-Reza-Kheradpisheh/publication/342801790/figure/fig2/AS:911232181735425@1594266090934/Sample-images-from-Fashion-MNIST-dataset.png" alt="Sample images from Fashion-MNIST dataset. | Download Scientific Diagram" style="zoom: 50%;" />

<center>Fashion MNIST dataset

</center>

<img src="https://production-media.paperswithcode.com/datasets/CIFAR-10-0000000431-b71f61c0_U5n3Glr.jpg" alt="CIFAR-10 Dataset | Papers With Code" style="zoom: 40%;" />

<center>CIFAR 10 dataset

</center>



#### Procedure

##### Compare classification performance on different datasets

I use different configuration of LeNet-5, i.e. different learning rate, optimizer, regularization and so on, to find a relatively good outcome on each dataset. Generate learning curve. 

##### Analysis on confusion classes and hard samples

With the best models on previous steps, I generate confusion matrix on testing set of every dataset, and see how and why our models make mistakes.

##### Classification with noisy data

Data in real world application could be noisy with wrong labels. In this part we assign wrong label to the MNIST training set with certain probability, and see how symmetric label noise will affect our model



*All the computation are done on Google Colab online. But cuda is not available there so no GPU acceleration is used.*



#### Results

##### Classification performance

###### MNIST

- learning rate= 0.001, optimizer=SGD, momentum=0.9, epoch=10

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220409191215143.png" alt="image-20220409191215143" style="zoom:80%;" />

​			train_acc 98.707, test_acc 98.540



- ==learning rate=0.01, optimizer=SGD, momentum=0.9, epoch=10==

  <img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220409191636067.png" alt="image-20220409191636067" style="zoom: 67%;" />

  train_acc 99.717, test_acc 99.110

  

- learning rate=0.01, optimizer=Adam, momentum=0.9, epoch=10

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220409192408188.png" alt="image-20220409192408188" style="zoom: 80%;" />

​		train_acc 98.255, test_acc 97.790



###### Fashion MNIST

- learning rate= 0.001, optimizer=SGD, momentum=0.9, epoch=10

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220409200941823.png" alt="image-20220409200941823" style="zoom: 80%;" />



- learning rate=0.01, optimizer=SGD, momentum=0.9, epoch=10

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220409202040649.png" alt="image-20220409202040649" style="zoom:80%;" />



- learning rate=0.01, optimizer=Adam, momentum=0.9, epoch=10

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220409202632080.png" alt="image-20220409202632080" style="zoom:80%;" />



==learning rate=0.01, optimizer=SGD, momentum=0.9, epoch=20==

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220409204322171.png" alt="image-20220409204322171" style="zoom:80%;" />

 train_acc 94.465, test_acc 90.250





- learning rate= 0.001, optimizer=SGD, momentum=0.9, epoch=10, dropout=0.2, L2 regularization


![image-20220409214906510](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220409214906510.png)



###### CIFAR

- learning rate= 0.001, optimizer=SGD, momentum=0.9, epoch=20

![image-20220413011133766](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413011133766.png)



- learning rate= 0.01, optimizer=SGD, momentum=0.9, epoch=20

![image-20220413013507287](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413013507287.png)

epoch 20: train_acc 77.404, test_acc 60.530



- ==learning rate= 0.001, optimizer=Adam,  epoch=20, L2 regularization==

![](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413122334999.png)

epoch 20: train_acc 75.378, test_acc 63.880





##### Confusion Matrix

###### MNIST

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413205456086.png" alt="image-20220413205456086" style="zoom: 80%;" /><img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413205504272.png" alt="image-20220413205504272" style="zoom:80%;" />

some mistakes

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413205823478.png" alt="image-20220413205823478" style="zoom:70%;" /><img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413205837853.png" alt="image-20220413205837853" style="zoom:70%;" /><img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413205851342.png" alt="image-20220413205851342" style="zoom:70%;" />



###### Fashion MNIST

- 0: T-shirt/top
- 1: Trouser
- 2: Pullover
- 3: Dress
- 4: Coat
- 5: Sandal
- 6: Shirt
- 7: Sneaker
- 8: Bag
- 9: Ankle boot

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413201853594.png" alt="image-20220413201853594" style="zoom:80%;" /><img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413201905496.png" alt="image-20220413201905496" style="zoom:80%;" />



some mistakes

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413204221073.png" alt="image-20220413204221073" style="zoom:70%;" /><img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413204237280.png" alt="image-20220413204237280" style="zoom:70%;" /><img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413204306252.png" alt="image-20220413204306252" style="zoom:70%;" />

*here target and predict index start from 0. i.e. T-shirt is 0



###### CIFAR10

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413212345562.png" alt="image-20220413212345562" style="zoom:80%;" />

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413212223877.png" alt="image-20220413212223877" style="zoom:80%;" /><img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413212247062.png" alt="image-20220413212247062" style="zoom:80%;" />

some mistakes

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413213623919.png" alt="image-20220413213623919" style="zoom:75%;" /><img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413213636110.png" alt="image-20220413213636110" style="zoom:75%;" /><img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220413213651038.png" alt="image-20220413213651038" style="zoom:75%;" />





##### Noisy Label

confusion matrix for $\epsilon=0.4$

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220414135758107.png" style="zoom:80%;" />



Under specific error rate, the model was trained 5 times independently, and get 5 test set accuracy. 5 different error rate are used. The mean of accuracy vs. label error rate are plotted in the line chart.

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220414185037720.png" alt="image-20220414185037720" style="zoom:80%;" />

The standard deviation of the 5 test set accuracy under each error rate are:

0.097%, 0.056%, 0.064%, 0.273% 0.743%



#### Discussion

##### CNN components

1. Convolutional layer: convolutional layer is composed of some tunable filter. When the filter detect some features, for example, texture, or objects, they'll be activated. The output of convolutional layer is the features extracted. It greatly reduce the workload comparing with inputting every pixel into the FC layer.
2. Pooling layer: always added between two consecutive convolutional layer. The main purpose is to compress information. For example, in max pooling, we may only retain the local maximum in a 4*4  block. By doing so, we can keep the most significant features while remove most redundant information.

3. FC layer: fully connected layer. Always the last component of the network. It maps the implicit feature space obtained by convolution layer and pooling layer into the label space, just like a classifier. One of the main computational work is to tune the millions of parameter in fc layer during backpropogation.

4. Activation function: it can appears anywhere in the neural networl. the major purpose is to add non-linearity. If there's no activation function, then  every layer is linear and the whole model will be linear model. By adding activation functions, we can then approximate any curve.

5. Softmax function: always in the output layer. it convert a vector of numbers into a vector of probability. Each of them equals to exponetial of the original number at that position divided by sum of exponential of every element. The vector of probability represents how likely the input belongs to each class, and of course, it sums to 1. Another benefit of using softmax is, when collaborate with cross-entropy, the partial derivative of the loss function to each element is just $\hat{y}-y$, where y is one-hot encoded.



##### Overfitting issue

Overfitting means the model approximate the training data too much. It has small bias while variance will be large. It performs well on training set, but cannot generalize well.

Some techniques to avoid overfitting

- regularization: Overfitting often involves large weights. So to stop parameters becoming unnecessarily large, we add a term, which is always first norm or second norm of vector $w$, to loss fcuntion, in order to pose penalty on large weight.
- dropout layer: during training process, we randomly drops a certain proportion of weights and only using the rest. This can be understand as distribute the responsibility of some parameters to the rest, in case it takes up too much responsibility and becomes too large. 
- learning rate schedule: we often decrease the learning rate as training goes on, to make the model converge. But when the training epoch is large enough, small learning rate could lead  to overfitting. Thus, we have to properly schedule our learning rate, to let model converge as quickly as it can, at the same time not overfit.



##### Activation function ReLU, Leaky ReLU, and ELU

###### ReLU

The most commonly used activation function. It abondons all values less than 0, and keeps positive values.

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220409164517213.png" alt="image-20220409164517213" style="zoom: 50%;" />

Pros

- easy to compute
- gradient is either 0 or 1, which will not cause vanishing gradient problem

Cons

- gradient not defined at 0
- 0 gradient for x<0 can make some neuron never activated during forward propogation, and also can make some nerons never updated during back propogation.  -Dying ReLU problem
- Will not compress the range of output. The value will get larger and larger from layer to layer.



###### Leaky ReLU

An improved version of ReLU

Pros

- fixed dying ReLU problem

Cons

- Not necessarily performs better than ReLU, as well as sigmoid and Tanh
- Still not differntiable at 0
- Can blow up the output

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220409165621655.png" alt="image-20220409165621655" style="zoom:50%;" />



###### ELU



<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220409165903910.png" alt="image-20220409165903910" style="zoom: 40%;" />

Pros

- Can output negative values
- slowly and smoothly converge to $-\alpha$ as x goes to $-Inf$.
- Differentiable at 0

Cons

- more expensive to compute
- Can blow up the output

[images]: https://ml-cheatsheet.readthedocs.io/en/latest/activation_functions.html



##### Loss functions L1Loss, MSELoss and BCELoss

###### L1 Loss

$\sum\left|\hat{y_i}-y_i\right| $

In most cases, we would prefer L2 loss to L1 loss. But when there're some outliers, L2 Loss will be significantly interfered, because outliers will generate huge loss with square error. In this case, we can use L1 loss instead of L2 loss.



###### MSE Loss

$\frac{1}{n}\sum(\hat{y_i}-y_i)^2$

If we suppose our prediction are normally distributed with mean value equals true label, then we can use MSE loss. Also, the square term is consistent with many physical meanings, like energy.



###### BCE Loss

$\frac{1}{n}\sum y_i log(\hat{y_i})+(1-y_i)log(1-\hat{y_i})$

Very commonly used. Shows the difference of two distribution. Compare with MSE, BCE will give larger loss when prediction is close to target. This improves the training speed. Besides, when using softmax in the output layer, computing derivative of BCE loss will have a very tidy outcome, which simplify calculation.





##### b Difference performance of three datasets

I tried to vary optimizer, learning rate, regularization and dropout. It shows typically learning rate=0.01 works better than 0.001 for SGD optimizer, but is too large for Adam optimizer. Adam works better in complicated datasets like CIFAR10, but not that good in simple ones. Regularization and dropout will slightly decrease the train accuracy, but can reduce overfitting, and let the model more likely do better in generalization.

We can achieve very high accuracy easily on MNIST dataset. It's also not hard on Fashion MNIST. For CIFAR, it's challenging. They require different configuration to get the best performance.

The major reason is the dataset itself. MNIST are all numbers, which is the most determinate in shape. The FashionMNIST are clothes, which is not determinate how they should look like. So is CIFAR, it contains animals, and they're colored picture, which makes it most difficult to classify.x



##### c Confusion matrix and confusion pairs

I think in many cases it's not the fault of the program. Can human tell every shirt from T-shirt? No, I can not. And some will write 1 more similar to 7 than 1 itself. The confusion are caused by ambiguous human definition of what it is.



##### d Noisy label data

The noisy label with specific true label=i under certain $\epsilon$ follows the discrete distribution
$$
P(noisy label=i)=1-\epsilon, P(noisy label=j,j\neq i)=\frac{\epsilon}{9}
$$
I use *np.random.choice* to generate random variable following this distribution.



The result is quite surprising. Although accuracy drop accelerate, and deviation of test result becomes larger as label error rate begin to rise, the overall performance is excellent. When 80% of the labels are wrong, the model still reach 96% accuracy on testing set after 10 epoches of training, even though the accuracy on noisy training set is quite low. That shows CNN has strong robustness on symmetric label noise. I guess as long as the correct label has the highest probability, the resultant force will still drag the gradient to descent in the right direction. If it is trained for more iterations, maybe it will converge more sufficiently and achieve better result.



##### others

When constructing the network, I come up with the question. We only define the size of the convolution kernel, but did not define how the kernels are like. After reading the document, I found there're actually two conv2d function. The one used in this assignment is 

```python
torch.nn.Conv2d(in_channels, out_channels, kernel_size, stride=1, padding=0, dilation=1, groups=1, bias=True, padding_mode='zeros', device=None, dtype=None)
```

The kernels are pre-defined by pytorch, and I did not find any access to them.



To customize our own kernel, like gaussian filters, we should use

```python
torch.nn.functional.conv2d(input, weight, bias=None, stride=1, padding=0, dilation=1, groups=1)
```

here 'input' is the tensor representing our customized kernel.
