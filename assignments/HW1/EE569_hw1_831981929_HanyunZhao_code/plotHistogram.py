import sys
import matplotlib.pyplot as plt
#f=open("HatHistogram.txt")
#f=open("TransferFuncHisto.txt")
#f=open("HatCumHistoEnh.txt")
#f=open("Flower_gray_noise_Histo.txt")
f=open("Flower_B_noise_Histo.txt")
data=[]
temp=f.readline()
while temp:
   data.append(int(temp))
   temp=f.readline()

#plt.bar(range(len(data)), data,width=1.01)#avoid stripes
#plt.bar(range(-120,256-120), data,width=1.01)
plt.bar(range(-255,256*2-255), data,width=1.01)
ax=plt.gca()
#ax.xaxis.set_major_locator(plt.MultipleLocator(1))#调整x轴间距为1的倍数
plt.xlim(-255,255)#调整x轴范围
#ax.set_title("Hat.raw instensity histogram")
#ax.set_title("1.b.2 transfer function histogram")
#ax.set_title("1.b.3 Enhanced B Hat Cumulative histogram")
#ax.set_title("noise distribution of flower gray")
ax.set_title("Noise distribution of Flower.raw B channel")
plt.show()
