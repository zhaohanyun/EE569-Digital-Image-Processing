import numpy as np
from sklearn.cluster import KMeans

data=np.loadtxt("Filter Response35.txt")
print(data.shape)

estimator=KMeans(n_clusters=6)
estimator.fit(data)
count=[0,0,0,0,0,0]
fout=open("color35.txt",'w')
for i in estimator.labels_:
    count[i]+=1
    fout.write(str(i))
print(count)
fout.close()
