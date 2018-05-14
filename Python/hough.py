
import math
import numpy as np
import matplotlib.pyplot as plt

#Note from Arnav: I took out everything but the hough function, because the other packages are not needed in this case

# run ahough transform with different possible vaules of x, y, and r
# notice: x_values, y_values are lists of all values to consider
# the r possiblitlites are descriped by [r_min, r_max) with resolution of r_step
# data is a list of tuples of the form (distance, angle)
def hough(data, x_values, y_values, r_min, r_max, r_step):
    # print(data)
    # print(x_values)
    # print(y_values)
    # print(r_min)
    # print(r_max)
    # print(r_step)
    
    # count number of r values
    num_r_values = int((r_max - r_min) / r_step)
    # print(num_r_values)
    
    # init 3d maxtrix map to be indexed map[x][y][r]
    map = [
            [ 
              [0] * num_r_values
              for i in range(len(y_values))
            ] 
            for j in range(len(x_values))
          ]
    
    # print(len(map))
    # print(len(map[0]))
    # print(len(map[0][0]))
    
    # let every point in data vote
    for dist, angle in data:
        # convert polar point to cartesian point
        px = dist * math.cos(angle)
        py = dist * math.sin(angle)
        # print((dist, angle))
        # print((px, py))
        
        # compute the radius of every posibile circle thought this point
        # and vote for those circles
        for i in range(len(x_values)):
            # get x value
            x = x_values[i]
            for j in range(len(y_values)):
                # get y value
                y = y_values[j]
                
                # so for this center point and point on the circle, find r
                # this is actually just distance formula
                r = (((x - px) ** 2) + ((y - py) ** 2)) ** 0.5
                
                # find the closest value of r
                r_index = int(round((r / r_step) - r_min))
                
                # if it is within valid range then vote for [x][y][r]
                if 0 <= r_index and r_index < num_r_values:
                    # print("vote:")
                    # print(i)
                    # print(j)
                    # print(r_index)
                    map[i][j][r_index] += 1
    
    # find peak
    max_votes = map[0][0][0]
    max_i = 0
    max_j = 0
    max_k = 0
    for i in range(len(x_values)):
        # print()
        # print()
        for j in range(len(y_values)):
            # print()
            for k in range(num_r_values):
                # print(map[i][j][k], end=", ")
                if map[i][j][k] > max_votes:
                    max_votes = map[i][j][k]
                    max_i = i
                    max_j = j
                    max_k = k
    
    # return answers in tuple (x, y, r)
    return (x_values[max_i], y_values[max_j], r_step * max_k + r_min)

