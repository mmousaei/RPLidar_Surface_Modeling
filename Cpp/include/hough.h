/*    hough.h - class definition for hough transform algorithm that
 *                    preforms hough transform to find the center
 *                    of the rplidar data
 *
 *    Carnegie Mellon University
 *    Authors: Mohammadreza Mousei
 *    Contact: mmousaei@andrew.cmu.edu
 *
 */

 #ifndef HOUGH_H
 #define HOUGH_H


 #include "error.h"
 #include "csvreader.h"

 #include <stdlib.h>
 #include <stdio.h>
 #include <iostream>
 #include <cstdio>
 #include <iostream>
 #include <string>
 #include <vector>
 #include <utility>

 #include <boost/program_options.hpp>
 #include <boost/filesystem.hpp>

 #include "opencv2/highgui.hpp"
 #include "opencv2/imgproc.hpp"

class Hough
{
public:
  Hough(){};
  ~Hough(){};
  std::vector<double> initializeHough(std::vector<std::pair<double, double>> *cartesian);

// private:

  void convertToMat(std::vector<std::pair<double, double>> *cartesian);

};

 #endif
