/*    main.cpp - Main file that calls surface modeling processes for radPiper
 *               data from rplidar
 *
 *    Carnegie Mellon University
 *    Authors: Mohammadreza Mousei
 *    Contact: mmousaei@andrew.cmu.edu
 *
 */

 #include "error.h"
 #include "csvreader.h"
 #include "rpreader.h"
 #include "hough.h"

 #include <stdlib.h>
 #include <stdio.h>
 #include <iostream>
 #include <cstdio>
 #include <iostream>
 #include <math.h>

 #include "opencv2/highgui.hpp"
 #include "opencv2/imgproc.hpp"

 #include <boost/program_options.hpp>
 #include <boost/filesystem.hpp>

void toCartesian(std::vector<std::vector<std::pair<double, double>>> *polar);

void centering(std::vector<std::vector<std::pair<double, double>>> *uncentered, double r0, double theta0);


int main(int argc, char** argv)
{
  Error err;
  CSVReader csv;
  RPReader rp;
  Hough hough;

  std::vector<std::vector<std::pair<double, double>>> rplidar_polar;

  rp.read("/home/radpiper/Documents/CMU/RadPiper/Post-Processing/Surface_Modeling/rplidar_scan.csv", &rplidar_polar);

  toCartesian(&rplidar_polar);
  // centering(&rplidar_polar, -0.08, 0);



  std::vector<double> circle;

  std::vector<std::pair<double, double>> temp;
  temp = rplidar_polar[0];

  cv::Mat src;
  int dim = sqrt(temp.size())+1;
  src = cv::Mat(dim, dim, CV_64F, cv::Scalar(0));


  // std::cout<<temp.size();

  hough.convertToMat(&temp);
  // std::cout << circle[0] << std::endl;
  // std::cout << circle[1] << std::endl;
  // std::cout << circle[2] << std::endl;



  // for(int i = 0; i < rplidar_polar.size(); i++)
  // {
  //   for(int j = 0; j < rplidar_polar[0].size(); j++)
  //   {
  //     std::cout << "range is: " << rplidar_polar[i][j].first << " angle is: " << rplidar_polar[i][j].second << std::endl;
  //   }
  // }


  // std::vector<std::vector<double>> read;

  // err = csv.read("/home/radpiper/Documents/CMU/RadPiper/Post-Processing/Surface_Modeling/rplidar_scan.csv", &read);

  // for(int i = 0; i < 10; i++)
  // {
  //   // for(int j = 0; j < read[0].size(); j++)
  //   // {
  //     std::cout << read[13+359][i]<<"  ";
  //   // }
  //   std::cout<<std::endl;
  // }

  return 0;
}


void toCartesian(std::vector<std::vector<std::pair<double, double>>> *polar)
{
  double r, theta;
  for(int i = 0; i < polar->size(); i++)
  {
    for(int j = 0; j < polar->at(0).size(); j++)
    {
      r = polar->at(i)[j].first;
      theta = polar->at(i)[j].second;
      polar->at(i)[j].first = r * cos(theta);
      polar->at(i)[j].second = r * sin(theta);
    }
  }
}

void centering(std::vector<std::vector<std::pair<double, double>>> *uncentered, double r0, double theta0)
{
  double r, theta, rp, thetap, cos_thetap;
  for(int i = 0; i < uncentered->size(); i++)
  {
    for(int j = 0; j < uncentered->at(0).size(); j++)
    {
      r = uncentered->at(i)[j].first;
      theta = uncentered->at(i)[j].second;

      rp = sqrt(r*r + r0*r0 + 2*r*r0*cos(theta0 - theta));
      cos_thetap = (r * cos(theta) + r0 * cos(theta0))/(rp);
      if (theta > 0)
        thetap = acos( (r * cos(theta) + r0 * cos(theta0))/(rp) );
      else
        thetap = -acos( (r * cos(theta) + r0 * cos(theta0))/(rp) );

      uncentered->at(i)[j].first = rp;
      uncentered->at(i)[j].second = thetap;
    }
  }
}
