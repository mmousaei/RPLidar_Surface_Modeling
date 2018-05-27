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

 #include <cmath>
 #include <boost/tuple/tuple.hpp>
 #include "gnuplot-iostream.h"

void toCartesian(std::vector<std::vector<std::pair<double, double>>> *polar);

void centering(std::vector<std::vector<std::pair<double, double>>> *uncentered, double r0, double theta0);

void HeatMap(std::vector<std::vector<std::pair<double, double>>> *polarHeatmap);

void HeatMapTest();

int main(int argc, char** argv)
{
  Error err;
  CSVReader csv;
  RPReader rp;
  Hough hough;

  std::vector<std::vector<std::pair<double, double>>> rplidar_polar;

  rp.read("../csv/rplidar_scan_42.csv", &rplidar_polar);

  // toCartesian(&rplidar_polar);

  centering(&rplidar_polar, 0.085, 0.05);

  std::vector<std::vector<double>> centered;




  // std::cout << rplidar_polar.size() << '\n';
  // std::cout << rplidar_polar[0].size() << '\n';
  // HeatMap(&rplidar_polar);
  // HeatMapTest();

  std::vector<double> circle;
  std::vector<double> row;

  for(int i = 0; i < rplidar_polar[0].size(); i++)
  {
    for(int j = 0; j < rplidar_polar.size(); j++)
    {
      row.push_back(rplidar_polar[i][j].first);
    }
    centered.push_back(row);
    row.erase(row.begin(), row.end());
  }
  // std::cout << centered.size() << '\n';
  // std::cout << centered[100].size() << '\n';
  //   std::cout << centered[100][129] << '\n';

csv.writeLog("../csv/centered.csv", centered);

  std::vector<std::pair<double, double>> temp;
  temp = rplidar_polar[0];

  cv::Mat src;
  int dim = sqrt(temp.size())+1;
  src = cv::Mat(dim, dim, CV_64F, cv::Scalar(0));


  // std::cout<<temp.size();
// std::vector<double> hg;
// circle = hough.initializeHough(&temp);
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


void HeatMap(std::vector<std::vector<std::pair<double, double>>> *polarHeatmap)
{

  int y = polarHeatmap->size();
  int x = polarHeatmap->at(0).size();
  std::cout << y << '\n';
  std::cout << x << '\n';
  int frame[1029][359];

  // float *frame = new float[ysize][xsize];
  double radius = 0.375;
  int min_frame = 0;
  memset(frame,0,sizeof(frame));
  for(int i = 0; i < polarHeatmap->size(); i++)
  {
    for(int j = 0; j < polarHeatmap->at(0).size(); j++)
    {
      if(!std::isinf(polarHeatmap->at(i)[j].first) && !std::isinf(polarHeatmap->at(i)[j].second) && polarHeatmap->at(i)[j].first < 1 && polarHeatmap->at(i)[j].first > -1)
      {
        // std::cout << "range is: " << polarHeatmap->at(i)[j].first << " angle is: " << polarHeatmap->at(i)[j].second << std::endl;
        frame[i][j] = radius*1000 - polarHeatmap->at(i)[j].first*1000;
        // frame[i][j] = i+j;
      }
    }
  }
  Gnuplot gp;
  gp << "unset key\n";
  gp << "cd '../images'\n";
  gp << "set cbrange [-2:50]\n";
  gp << "set palette defined (-2 'navy', 4 'blue', 16 'green', 20 'yellow', 30 'orange', 40 'red')\n";
  gp << "set pm3d \n";
  gp << "set hidden3d\n";
  // gp << "set view map\n";
  gp << "set xrange [ 0 : 359 ] \n";
  gp << "set yrange [ 0 : 200 ] \n";
  gp << "set terminal png \n";
  std::string str1 = "set output 'Surface_Model_";
  std::string str2 = std::to_string(1);
  std::string str3 = ".png' \n";
  //
  gp << str1 + str2 + str3;
  gp << "splot '-'\n";
  gp.send2d(frame);

  str1 = "set output 'Surface_Model_";
  str2 = std::to_string(2);
  str3 = ".jpeg' \n";
  //
  gp << str1 + str2 + str3;
  gp << "splot '-'\n";
  gp.send2d(frame);
    // gp.flush();
}

void HeatMapTest()
{
  float frame[100][100];
    for (int n=0; n<100; n++)
    {
        for (int m=0; m<100; m++)
        {
        frame[n][m]=n+m;
        }
    }

    Gnuplot gp;
    gp << "unset key\n";
    gp << "cd '../images'\n";
    gp << "set pm3d\n";
    gp << "set hidden3d\n";
    gp << "set view map\n";
    // gp << "set xrange [ 0 : 5 ] \n";
    // gp << "set yrange [ 0 : 3 ] \n";
    gp << "set terminal jpeg \n";
    std::string str1 = "set output 'test_";
    std::string str2 = std::to_string(64);
    std::string str3 = ".jpeg' \n";

    gp << str1 + str2 + str3;
    gp << "splot '-'\n";
    gp.send2d(frame);
    // gp.flush();
}
