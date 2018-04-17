#! /usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

class ScanData:
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


class ScanSeries:
    # Initialize the class
    def __init__(self):
        # timestamps for each individual scan 
        self.scan_timestamps = []
        # array of ScanData objects
        self.scan_data = []
        # number of scans
        self.num_scans = -1

    def read_scan_data(self,filename):
        try:
            # open the file for reading
            fh = open(filename,'r') 
             
            # grab all lines in the file, skipping header line
            lines = list(fh.readlines())[1:]
            # figure out how many lines there are
            self.num_scans = len(lines)

            for i in range(self.num_scans):

                # get the current line
                line = lines[i]

                # avoid trying to read later columns if line is malformed
                checknum = line.split(",")[0]
                try:
                    float(checknum)
                    num = True
                except ValueError:
                    num = False
                if num:
                    # create a ScanData object for this line
                    self.scan_data.append(ScanData())

                    # split line into rows based on commas
                    splitline = list(line.split(","))

                    # Timestamp as computed from stamp secs and nsecs
                    timestamp = float(splitline[3]) + float(splitline[4])/1E9
                    # append this to list of scan timestamps                    
                    self.scan_timestamps.append(timestamp)
                    # set the timestamp in the current ScanData object
                    self.scan_data[i].timestamp = timestamp

                    # min angle for this scan, radians
                    self.scan_data[i].min_angle = float(splitline[6])
                    # max angle for this scan, radians
                    self.scan_data[i].max_angle = float(splitline[7])
                    # angle increment for this scan
                    self.scan_data[i].angle_increment = float(splitline[8])
                    # time increment for this scan
                    self.scan_data[i].time_increment = float(splitline[9])
                    # time for this scan
                    self.scan_data[i].time = float(splitline[10])
                    # min range for this scan
                    self.min_range = float(splitline[11])
                    # max range for each scan
                    self.max_range = float(splitline[12])
       
                    # read scan ranges
                    
                    # number of points in this rotation's worth of data
                    self.scan_data[i].num_points = 0
                    done = False
                    #print('len(splitline) = ' + str(len(splitline)))
                    # loop through until we see a ']' or we reach the end of the line
                    while ( not done ) and ( self.scan_data[i].num_points + 13 < len(splitline) ):
                        #print( 'self.scan_data[i].num_points + 13 = ' + str( self.scan_data[i].num_points + 13 ))
                        # pull out the current point's range               
                        this_range = splitline[13+self.scan_data[i].num_points]
                        #print('this_range = ' + this_range) 
                        if self.scan_data[i].num_points == 0:
                            # if this is the first element in the range array, strip off '['
                            #print('in if self.scan_data[i].num_points == 0')
                            self.scan_data[i].ranges.append(float(this_range[1:]))
                        elif this_range.find("]") != -1:
                            # This is the last element in the range array. Strip off ']', 
                            #     and break out of while loop
                            #print('in elif this_range.find("]")')
                            self.scan_data[i].ranges.append(float(this_range[:-1]))
                            done = True
                        else:
                            #print('in else')
                            # This should be a float without stripping anything off
                            self.scan_data[i].ranges.append(float(this_range))

                        # increment the number of points
                        self.scan_data[i].num_points = self.scan_data[i].num_points + 1     

                    self.scan_data[i].angles = np.zeros(self.scan_data[i].num_points,'float')
                    # read scan intensities
                    for j in range(self.scan_data[i].num_points):
                        # pull out the current point's intensity               
                        #print(13+self.scan_data[i].num_points + j)
                        this_intensity = splitline[13+self.scan_data[i].num_points + j]
                        if j == 0:
                            # if this is the first element in the intensity array, strip off '['
                            self.scan_data[i].intensities.append(np.uint8(this_intensity[1:]))
                        elif j == self.scan_data[i].num_points - 1:
                            # This is the last element in the intensity array. Strip off ']', 
                            self.scan_data[i].intensities.append(np.uint8(this_intensity[:-1]))
                        else:
                            # This should be an int without stripping anything off
                            self.scan_data[i].intensities.append(np.uint8(this_intensity))
                        # array of angles
                        self.scan_data[i].angles[j] = self.scan_data[i].min_angle + self.scan_data[i].angle_increment*float(j)
                    
        except IOError:
            print("Error reading in scan data!")
            return
        finally:
            # if fh exists, close it
            try: 
                fh
            except NameError:
                print('')
            else:
                fh.close()
            return

    def plot_single_scan(self,index):
        y = -np.multiply(self.scan_data[index].ranges,np.cos(self.scan_data[index].angles))
        x = np.multiply(self.scan_data[index].ranges,np.sin(self.scan_data[index].angles))
        plt.plot(x,y,'.')
        plt.gca().set_aspect('equal')
        plt.show()
