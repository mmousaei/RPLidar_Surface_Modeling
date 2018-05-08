import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as colors
from unwrap_25d import Unwrapping
import math

unwrap = Unwrapping()
# unwrap.unwraped_data_gen("rplidar_scan_small_cube.csv")
unwrap.unwraped_data_gen("rplidar_rear_scan_half_cm.csv")


def to360degrees(dataList):
	dist = 360.0/float(len(dataList))
	L = []
	for i in range(360):
		x = float(i)/dist
		xIndex = int(round(x))
		# Naive filtering of infinities
		if(np.isinf(dataList[xIndex]) ):
			L.append(dataList[xIndex])
			print(dataList[xIndex])
		L.append(dataList[xIndex])
	return L



# NEED TO: filter out high frequencies, low pass filter
# a, b, and c: arrays of data points from unwrap function
aOld = []
bOld = []
cOld = []


for i in range(0,220):
    aOld.append(to360degrees(unwrap.unwraped_data[i].x))
    bOld.append(to360degrees(unwrap.unwraped_data[i].y))
    cOld.append(to360degrees(unwrap.unwraped_data[i].z))


# for i in range(50,150):
#     aOld.append((unwrap.unwraped_data[i].x))
#     bOld.append((unwrap.unwraped_data[i].y))
#     cOld.append((unwrap.unwraped_data[i].z))


# for i in range(len(aOld)):
# 	if(math.isinf(aOld[i])):
# 		aOld[i] = aOld[i-1]

# for i in range(len(bOld)):
# 	if(math.isinf(bOld[i])):
# 		bOld[i] = bOld[i-1]

# for i in range(len(cOld)):
# 	if(math.isinf(cOld[i])):
# 		cOld[i] = cOld[i-1]


# for i in range(50,150):z
#     aOld.append(unwrap.unwraped_data[i].x)
#     bOld.append(unwrap.unwraped_data[i].y)
#     if( math.isinf( unwrap.unwraped_data[i].z )):
#     	cOld.append(unwrap.unwraped_data[i-1].z)
#     else:
# 		cOld.append(unwrap.unwraped_data[i].z)


a = []
b = []
c = []


a = np.array(aOld)
b = bOld
c = np.array(cOld)




#convert intensity (list of lists) to a numpy array for plotting
intensity = np.array(b)


# pc=plt.pcolormesh(a,c,intensity)
#now just plug the data into pcolormesh, it's that easy!
pc = plt.pcolormesh(30*a, c/4, -intensity, cmap="jet", shading="flat")
plt.colorbar(pc) #need a colorbar to show the intensity scale



plt.show() #boom


plt.pcolormesh(a, c, intensity, cmap="rainbow", shading="gouraud")
plt.colorbar(pc) #need a colorbar to show the intensity scale
plt.show() #boom
