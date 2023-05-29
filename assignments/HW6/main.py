import numpy as np
from tensorflow.keras.datasets import mnist,fashion_mnist
from skimage.util import view_as_windows
from pixelhop import Pixelhop
from skimage.measure import block_reduce
import xgboost as xgb
import warnings, gc
import time


np.random.seed(1)

# Preprocess
N_Train_Reduced = 10000    # 10000
N_Train_Full = 60000     # 50000
N_Test = 10000            # 10000

BS = 2000 # batch size


def shuffle_data(X, y):
    shuffle_idx = np.random.permutation(y.size)
    X = X[shuffle_idx]
    y = y[shuffle_idx]
    return X, y


def select_balanced_subset(images, labels, use_num_images):
    '''
    select equal number of images from each classes
    '''
    num_total, H, W, C = images.shape
    num_class = np.unique(labels).size
    num_per_class = int(use_num_images / num_class)

    # Shuffle
    images, labels = shuffle_data(images, labels)

    selected_images = np.zeros((use_num_images, H, W, C))
    selected_labels = np.zeros(use_num_images)

    for i in range(num_class):
        selected_images[i * num_per_class:(i + 1) * num_per_class] = images[labels == i][:num_per_class]
        selected_labels[i * num_per_class:(i + 1) * num_per_class] = np.ones((num_per_class)) * i

    # Shuffle again
    selected_images, selected_labels = shuffle_data(selected_images, selected_labels)

    return selected_images, selected_labels

def Shrink(X, shrinkArg):
    #---- max pooling---- (2x2) -to- (1x1)
    pool = shrinkArg['pool']
    # TODO: fill in the rest of max pooling
    if pool:
        N, H, W, C = X.shape
        pool_out=np.zeros((N,H/2,W/2,C))
        for n in range(N):
            for c in range(C):
                for h in range(H/2):
                    for w in range(W/2):
                        pool_out[n,h,w,c]=X[n,h*2:h*2+1,w*2,w*2+1,c].max()
    else:
        pool_out=X

    #---- neighborhood construction
    win = shrinkArg['win']
    stride = shrinkArg['stride']
    pad = shrinkArg['pad']
    ch=pool_out.shape[-1]
    # TODO: fill in the rest of neighborhood construction

    if pad>0:
        out=np.pad(pool_out,((0,0), (pad,pad), (pad,pad), (0,0)), 'reflect')
    else:
        out=pool_out
    out = view_as_windows(out, (1, win, win, ch), (1, stride, stride, ch))
    return out.reshape(out.shape[0], out.shape[1], out.shape[2], -1)


# example callback function for how to concate features from different hops
def Concat(X, concatArg):
    return X

def get_feat(X, num_layers=3):
    output = p2.transform_singleHop(X,layer=0)
    if num_layers>1:
        for i in range(num_layers-1):
            output = p2.transform_singleHop(output, layer=i+1)
    return output


if __name__ == "__main__":
    warnings.filterwarnings("ignore")
    # ---------- Load MNIST data and split ----------
    (x_train, y_train), (x_test,y_test) = mnist.load_data()


    # -----------Data Preprocessing-----------
    x_train = np.asarray(x_train,dtype='float32')[:,:,:,np.newaxis]
    x_test = np.asarray(x_test,dtype='float32')[:,:,:,np.newaxis]
    y_train = np.asarray(y_train,dtype='int')
    y_test = np.asarray(y_test,dtype='int')

    # if use only 10000 images train pixelhop
    x_train_reduced, y_train_reduced = select_balanced_subset(x_train, y_train, use_num_images=N_Train_Reduced)

    x_train /= 255.0
    x_test /= 255.0


    # -----------Module 1: set PixelHop parameters-----------
    # TODO: fill in this part
    SaabArgs = [{'num_AC_kernels':-1, 'needBias':False, 'cw': False},
                {'num_AC_kernels':-1, 'needBias':True, 'cw':True},
                {'num_AC_kernels':-1, 'needBias':True, 'cw':True}]
    shrinkArgs = [{'func':Shrink, 'win':5, 'stride': 1,'pad':2,'pool':False},
                {'func': Shrink, 'win':5, 'stride': 1,'pad':0,'pool':True},
                {'func': Shrink, 'win':5, 'stride': 1,'pad':0,'pool':True}]
    concatArg = {'func':Concat}

    # -----------Module 1: Train PixelHop -----------
    # TODO: fill in this part
    p2 = Pixelhop(depth=3, TH1=0.005, TH2=0.001,
                SaabArgs=SaabArgs, shrinkArgs=shrinkArgs, concatArg=concatArg)
    p2.fit(x_train_reduced)

    # --------- Module 2: get only Hop 3 feature for both training set and testing set -----------
    # you can get feature "batch wise" and concatenate them if your memory is restricted
    # TODO: fill in this part
    train_hop3_feats = get_feat(x_train) #get_feat is already set to get 3rd feat
    test_hop3_feats = get_feat(x_test)
    

    # --------- Module 2: standardization
    STD = np.std(train_hop3_feats, axis=0, keepdims=1)
    train_hop3_feats = train_hop3_feats/STD
    test_hop3_feats = test_hop3_feats/STD
    
    #---------- Module 3: Train XGBoost classifier on hop3 feature ---------

    tr_acc = []
    te_acc = []
    
    clf = xgb.XGBClassifier(n_jobs=-1,
                        objective='multi:softprob',
                        # tree_method='gpu_hist', gpu_id=None,
                        max_depth=6,n_estimators=100,
                        min_child_weight=5,gamma=5,
                        subsample=0.8,learning_rate=0.1,
                        nthread=8,colsample_bytree=1.0)

    # TODO: fill in the rest and report accuracy

    
    
    
    
    
    
    
    
    
