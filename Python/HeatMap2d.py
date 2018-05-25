import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as colors
from unwrap_25d import Unwrapping
import math


smoothingFactor = 0.8

unwrap = Unwrapping()
unwrap.unwraped_data_gen("rplidar_scan_offcenter_mat_postcold_long_pipe_diff_heights.csv", smoothingFactor)

def findCloseIndex(val, arr):
	array = []
	for i in range(len(arr)):
		array.append(abs(val - arr[i]))
	minVal = array[0]
	minInd = 0
	for i in range(len(array)):
		if array[i] < minVal:
			minVal = array[i]
			minInd = i
	return minInd



def to360degrees(xList, yList, zList, angles):
	x = []
	y = []
	z = []
	ang = []
	for i in angles:
		ang.append(math.degrees(i) + 180)
	for i in range(360):
		ind = findCloseIndex(i, ang)
		x.append(xList[ind])
		y.append(yList[ind])
		z.append(zList[ind])
		# if(xList[ind] > 2):
		# 	print(xList[ind])
	return (x,y,z)





for j in range((len(unwrap.unwraped_data)//50)):
# NEED TO: filter out high frequencies, low pass filter
# a, b, and c: arrays of data points from unwrap function
	aOld = []
	bOld = []
	cOld = []




	for i in range(j*100,(j+1)*100):
		(xList, yList, zList) = to360degrees((unwrap.unwraped_data[i].x), (unwrap.unwraped_data[i].y), unwrap.unwraped_data[i].z, unwrap.unwraped_data[i].angles)
		aOld.append(xList)
		bOld.append(yList)
		cOld.append(zList)


	a = []
	b = []
	c = []



	a = np.array(aOld)
	b = bOld
	c = np.array(cOld)



	#convert intensity (list of lists) to a numpy array for plotting
	intensity = np.array(b)

	# print(intensity)

	# #now just plug the data into pcolormesh, it's that easy!
	# plt.pcolormesh(a, c, intensity, cmap="gist_rainbow", shading="flat")
	# plt.colorbar() #need a colorbar to show the intensity scale
	# plt.show() #boom

	# plt.pcolormesh(30*a, c/4, -intensity,cmap="jet", shading="gouraud")
	plt.pcolormesh(30*a, c/4, -intensity, vmin = -0.01, vmax = 0.025,cmap="jet", shading="gouraud")
	plt.colorbar() #need a colorbar to show the intensity scale
	# plt.show() #boom
	# plt.xlim((-35, 35))

	plt.savefig('plot %d.jpg' % j)

	plt.close()
