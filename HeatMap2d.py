import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as colors
from unwrap_25d import Unwrapping


unwrap = Unwrapping()
unwrap.unwraped_data_gen("rplidar_scan_cub_RPV3.csv")


def to360degrees(dataList):
	dist = 360.0/float(len(dataList))
	L = []
	for i in range(360):
		x = float(i)/dist
		xIndex = int(round(x))
		# Naive filtering of infinities
		if(dataList[xIndex] == float('inf')): xIndex += 1
		L.append(dataList[xIndex])
	return L



# NEED TO: filter out high frequencies, low pass filter
# a, b, and c: arrays of data points from unwrap function 
aOld = []
bOld = []
cOld = []


for i in range(50,150):
    aOld.append(to360degrees(unwrap.unwraped_data[i].x))
    bOld.append(to360degrees(unwrap.unwraped_data[i].y))
    cOld.append(to360degrees(unwrap.unwraped_data[i].z))


a = []
b = []
c = []



a = np.array(aOld)
b = bOld
c = np.array(cOld)



#convert intensity (list of lists) to a numpy array for plotting
intensity = np.array(b)



#now just plug the data into pcolormesh, it's that easy!
plt.pcolormesh(a, c, intensity, cmap="gist_rainbow", shading="flat")
plt.colorbar() #need a colorbar to show the intensity scale
plt.show() #boom


plt.pcolormesh(a, c, intensity, cmap="gist_rainbow", shading="gouraud")
plt.colorbar() #need a colorbar to show the intensity scale
plt.show() #boom




