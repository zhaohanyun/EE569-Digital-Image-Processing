myClassifierMNIST.py, myClassifierFashionMNIST.py, myClassifierCIFAR10.py are three classifier for different dataset. Their structure are the same, only dataset and some configuration are different. Hyperparameters are tuned directly in the code.

ConfusionMatrix.py load the classifier with best configuration, and generate the confusion matrix for test result. If you want to switch dataset, you have to modify load_data() function

NoisyData.py add noise to MNIST train set labels. It requires quite a long time to run since it train the model 25 times.
