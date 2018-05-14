from read_scans import ScanSeries
import numpy as np
import math
import matplotlib.pyplot as plt
from centering_scans import Centering
from scipy.interpolate import griddata

class unwrap:

	def __init__(self):
		# centered ranges 
		self.timestamp = -1
		# time increment for this scan
		self.time_increment = float('nan')
	    # time for this scan
		self.time = float('nan')
	    
	    # number of points in this rotation's worth of data
		self.num_points = -1
	    # array of ranges
		self.x = []
	    # array of intensities
		self.y = []
	    # array of angles
		self.z = []	

		self.angles = []



class Unwrapping:

	def __init__(self):
		
		self.unwraped_data = []
		self.num_scans = -1
		self.x = []
		self.y = []
		self.z = []


	def unwraped_data_gen(self, filename, smoothingFactor):

		centered_scans = Centering()
		centered_scans.centered_data_gen(filename, smoothingFactor)

		# print(centered_scans.centered_data[5].ranges[10])
		# print(centered_scans.centered_data[1].ranges[3])
		radius = 0.375 #30in pipe in meter
		# radius = 0.5334 #42in pipe in meter
		# radius = 0.523875 #42 cal test pipe
		vel = 5 #cmps
		freq = 7 #hz
		self.num_scans = centered_scans.num_scans

		# print(centered_scans.centered_data[10].angles)

		for i in range(centered_scans.num_scans):

			self.unwraped_data.append(unwrap())
			self.unwraped_data[i].timestamp = centered_scans.centered_data[i].timestamp
			self.unwraped_data[i].time_increment = centered_scans.centered_data[i].time_increment
			self.unwraped_data[i].time = centered_scans.centered_data[i].time
			self.unwraped_data[i].num_points = centered_scans.centered_data[i].num_points
			self.unwraped_data[i].angles = centered_scans.centered_data[i].angles
			self.unwraped_data[i].x = []
			self.unwraped_data[i].y = []
			self.unwraped_data[i].z = []
			radius = centered_scans.centered_data[i].avg_radius
			for j in range(len(centered_scans.centered_data[i].ranges)):

				x = centered_scans.centered_data[i].angles[j]*radius
				y = centered_scans.centered_data[i].ranges[j] - radius
				z = i * vel / freq

				self.x.append(x)
				self.y.append(y)
				self.z.append(z)

				self.unwraped_data[i].x.append(x)
				self.unwraped_data[i].y.append(y)
				self.unwraped_data[i].z.append(z)


	def print_unwraped_with_id(self, ind):
		# print(angles)
		# print(self.centered_data[1].angles)
		# print(scan.scan_data[3].ranges)
		# scan.plot_single_scan(3)
		# ind = 3
		# y = -np.multiply(self.ranges[ind], np.cos(self.angles[ind]))
		# x = np.multiply(self.ranges[ind],np.sin(self.angles[ind]))
		y = self.unwraped_data[ind].y
		x = self.unwraped_data[ind].x
		# print(y)
		plt.plot(x,y,'.')
		plt.gca().set_aspect('equal')
		plt.show()

	def plot_unwraped_heatmap(self):

		# Convert from pandas dataframes to numpy arrays
		X, Y, Z, = np.array([]), np.array([]), np.array([])
		for i in range(len(self.x)):
		        X = np.append(X,self.x[i])
		        Y = np.append(Y,self.y[i])
		        Z = np.append(Z,self.z[i])

		# create x-y points to be used in heatmap
		xi = np.linspace(X.min(),X.max(),1000)
		yi = np.linspace(Y.min(),Y.max(),1000)

		# Z is a matrix of x-y values
		zi = griddata((X, Y), Z, (xi[None,:], yi[:,None]), method='cubic')

		# I control the range of my colorbar by removing data 
		# outside of my range of interest
		zmin = 3
		zmax = 12
		zi[(zi<zmin) | (zi>zmax)] = None

		# Create the contour plot
		CS = plt.contourf(xi, yi, zi, 15, cmap=plt.cm.rainbow,
		                  vmax=zmax, vmin=zmin)
		plt.colorbar()  
		plt.show()


	# def plot_unwraped_heatmap2(self):

 #        # print(len(self.x))
 #        # print(len(self.y))
 #        # print(self.intensity[1][1])
 #        #setup the 2D grid with Numpy

 #        x_temp = []
 #        y_temp = []
 #        # intensity_temp = []
 #        # intensity_temp2 = []
 #        # intensity_temp2.append([[]])
        
 #        intensity_temp = [[0 for i in range(self.width)] for j in range(self.height)]

        
 #        print(self.width)
 #        print(self.height)




 #        for i in range(len(intensity_temp[0])):

 #            x_temp.append(i)

 #            for j in range(len(intensity_temp)):
 #                intensity_temp[j][i] = i*j


 #        for i in range(len(intensity_temp)):
 #            y_temp.append(i)

 #        print("x is: %f", len(self.x_plt))
 #        print("y is: %f", len(self.y_plt))

 #        x, y = np.meshgrid(self.x_plt, self.y_plt)

 #        #convert intensity (list of lists) to a numpy array for plotting
 #        intensity = np.array(self.intensity_plt)

 #        print(intensity.shape)

 #        # print(len(intensity[0]))

 #        #now just plug the data into pcolormesh, it's that easy!
 #        plt.pcolormesh(x, y, intensity)
 #        plt.colorbar() #need a colorbar to show the intensity scale
 #        plt.show() #boom

		







