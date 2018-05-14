#! /usr/bin/python

import numpy as np
from read_scans import ScanSeries
import matplotlib.pyplot as plt
import hough as H
from ellipses import LSqEllipse


class CenterScanData:
    # Initialize the class
    def __init__(self):
        # timestamp for each individual scan 
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
        # array of centers (Represented as (x,y))
        self.center = []

        self.avg_radius = []


class CenterScanSeries:
    # Initialize the class
    def __init__(self):
        # timestamps for each individual scan 
        self.center_scan_timestamps = []
        # array of ScanData objects
        self.center_scan_data = []
        # number of scans
        self.num_scans = -1

    def radius_smoothing(self, ranges, alpha):
        SmoothRanges = []
        SmoothRanges.append(ranges[0])
        n = len(ranges)
        for i in range(1, n):
            r = alpha*ranges[i-1] + (1 - alpha)*ranges[i]
            SmoothRanges.append(r)

        return SmoothRanges

    def read_scan_data(self,filename, smoothingFactor):
        scan_series_regular = ScanSeries()
        scan_series_regular.read_scan_data(filename)
        for i in range(scan_series_regular.num_scans):
            # print(i)
            self.center_scan_data.append(CenterScanData())
            self.center_scan_data[i].timestamp = scan_series_regular.scan_data[i].timestamp
            self.center_scan_data[i].min_angle = scan_series_regular.scan_data[i].min_angle
            self.center_scan_data[i].max_angle = scan_series_regular.scan_data[i].max_angle
            self.center_scan_data[i].angle_increment = scan_series_regular.scan_data[i].angle_increment
            self.center_scan_data[i].time_increment = scan_series_regular.scan_data[i].time_increment
            self.center_scan_data[i].time = scan_series_regular.scan_data[i].time
            self.center_scan_data[i].min_range = scan_series_regular.scan_data[i].min_range
            self.center_scan_data[i].max_range = scan_series_regular.scan_data[i].max_range
            self.center_scan_data[i].num_points = scan_series_regular.scan_data[i].num_points
            self.center_scan_data[i].ranges = self.radius_smoothing(scan_series_regular.scan_data[i].ranges, smoothingFactor)
            self.center_scan_data[i].intensities = scan_series_regular.scan_data[i].intensities
            self.center_scan_data[i].angles = scan_series_regular.scan_data[i].angles



            currRanges = self.center_scan_data[i].ranges
            currAngles = self.center_scan_data[i].angles

            n = len(currRanges)
            assert(n == len(currAngles))

            #This will be the arrays of filtered ranges and angles
            data_r = []
            data_a = []

            for j in range(n):
                r = currRanges[j]
                a = currAngles[j]

                if r != float("inf") and r != float("nan"):
                    data_r.append(r)
                    data_a.append(a)

                

            x = np.multiply(data_r,np.cos(data_a))
            y = np.multiply(data_r,np.sin(data_a))

            data = (x,y)

            lsqe = LSqEllipse()
            lsqe.fit(data)
            (currCenter, a, b, c) = lsqe.parameters()

            cent_x = currCenter[0]
            cent_y = currCenter[1]

            self.center_scan_data[i].center = (cent_x,cent_y)
            self.center_scan_data[i].avg_radius = (a+b)/2


    def return_single_center(self, index):
        self.read_scan_data
        return self.center_scan_data[index].center


    
        
