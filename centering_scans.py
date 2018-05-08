from read_scans import ScanSeries
from centering_data_modification import CenterScanSeries
import numpy as np
import math
import matplotlib.pyplot as plt

class centered:

	def __init__(self):
		# centered ranges 
		self.timestamp = -1

		# min angle for this scan, radians
		self.min_angle = float('nan')
	    # max angle for this scan, radians
		self.max_angle = float('nan')
	    # angle increment for this scan
		self.angle_increment = float('nan')
	    # time increment for this scan
		self.time_increment = float('nan')
	    # time for this scan
		self.time = float('nan')
	    # min range for this scan
		self.min_range = float('nan')
	   	# max range for each scan
		self.max_range = float('nan')
	    
	    # number of points in this rotation's worth of data
		self.num_points = -1
	    # array of ranges
		self.ranges = []
	    # array of intensities
		self.intensities = []
	    # array of angles
		self.angles = []

		self.center = []

		self.avg_radius = []



class Centering:

	def __init__(self):
			

		self.centered_data = []

		self.num_scans = -1

	def centered_data_gen(self, filename):

		scan = ScanSeries()
		scan.read_scan_data(filename)
		# scan.plot_single_scan(1)
		# print(scan.scan_data[3].ranges[1])

		findCenter = CenterScanSeries()
		findCenter.read_scan_data(filename)

		# theta0 = 0
		# ranges = []
		# angles = []

		print(scan.num_scans)
		for k in range(scan.num_scans):
			ranges = []
			angles = []
			self.num_scans = scan.num_scans
			self.centered_data.append(centered())
			self.centered_data[k].timestamp = scan.scan_data[k].timestamp
			self.centered_data[k].min_angle = scan.scan_data[k].min_angle
			self.centered_data[k].max_angle = scan.scan_data[k].max_angle
			self.centered_data[k].angle_increment = scan.scan_data[k].angle_increment
			self.centered_data[k].time_increment = scan.scan_data[k].time_increment
			self.centered_data[k].time = scan.scan_data[k].time
			self.centered_data[k].min_range = scan.scan_data[k].min_range
			self.centered_data[k].max_range = scan.scan_data[k].max_range
			self.centered_data[k].num_points = scan.scan_data[k].num_points
			self.centered_data[k].ranges = []
			self.centered_data[k].intensities = scan.scan_data[k].intensities
			self.centered_data[k].angles = []
			self.centered_data[k].center = findCenter.center_scan_data[k].center
			self.centered_data[k].avg_radius = findCenter.center_scan_data[k].avg_radius



			(xneg, yneg) = (findCenter.return_single_center(k))
			# x = -xneg
			# y = -yneg

			# print(x)
			# print(y)



			# r0 = -math.sqrt(x**2 + y**2)
			r0 = 0
			# theta0 = np.arctan(y/x)
			theta0 = 0


			for i in range(len(scan.scan_data[k].ranges)):

				if( math.isinf( scan.scan_data[k].ranges[i] ) ):
					ranges.append( scan.scan_data[k].ranges[i] )
					angles.append( scan.scan_data[k].angles[i] )
					# self.centered_data[k].ranges.append( scan.scan_data[k].ranges[i-1] )
					# self.centered_data[k].angles.append( scan.scan_data[k].angles[i-1] )
				else:
					r = scan.scan_data[k].ranges[i]
					theta = scan.scan_data[k].angles[i]
					rp = math.sqrt(r**2 + r0**2 + 2*r*r0*math.cos(theta0 - theta))
					cos_thetap = (r * np.cos(theta) + r0 * np.cos(theta0))/(rp)
					if (theta > 0):
						thetap = np.arccos( (r * np.cos(theta) + r0 * np.cos(theta0))/(rp) )
					else:
						thetap = -np.arccos( (r * np.cos(theta) + r0 * np.cos(theta0))/(rp) )
					self.centered_data[k].ranges.append(rp)
					self.centered_data[k].angles.append(thetap)







	def print_centered_with_id(self, ind):
		# print(angles)
		# print(self.centered_data[1].angles)
		# print(scan.scan_data[3].ranges)
		# scan.plot_single_scan(3)
		# ind = 3
		# y = -np.multiply(self.ranges[ind], np.cos(self.angles[ind]))
		# x = np.multiply(self.ranges[ind],np.sin(self.angles[ind]))
		y = -np.multiply(self.centered_data[ind].ranges, np.cos(self.centered_data[ind].angles))
		x = np.multiply(self.centered_data[ind].ranges,np.sin(self.centered_data[ind].angles))
		# print(y)
		plt.plot(x,y,'.')
		plt.gca().set_aspect('equal')
		plt.show()





7