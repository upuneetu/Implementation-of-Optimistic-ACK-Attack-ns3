import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import pandas as pd

data1=pd.read_csv('optack.csv')
x1=data1['Time in Seconds']
y1=data1['Congestion Window']
data2=pd.read_csv('ack.csv')
x2=data2['Time in Seconds']
y2=data2['Congestion Window']

red_patch = mpatches.Patch(color='red', label='Without Optimistic Acking 42880 bytes of packets')
blue_patch = mpatches.Patch(color='blue', label='With Optimistic Acking 370912')
plt.legend(handles=[blue_patch,red_patch])
plt.plot(x1,y1,color='blue',label='GPU')
plt.plot(x2,y2,color='red',label='CPU')
plt.xlabel('Time in Seconds')
plt.ylabel('Congestion Window')
plt.title('Reasults of Optimistic ACKing TCP')
plt.show()
