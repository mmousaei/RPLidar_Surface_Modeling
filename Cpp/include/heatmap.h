/*    heatmap.h  -  class definition for heatmap image generation from
 *                    RPLidar surface model using gnuplot
 *
 *    Carnegie Mellon University
 *    Authors: Mohammadreza Mousei
 *    Contact: mmousaei@andrew.cmu.edu
 *
 */


 #include "error.h"
 #include "csvreader.h"

 #include <stdlib.h>
 #include <stdio.h>
 #include <iostream>
 #include <cstdio>
 #include <iostream>
 #include <math.h>

 #include <iomanip> // setprecision
 #include <sstream> // stringstream

 #include <boost/program_options.hpp>
 #include <boost/filesystem.hpp>

 #include <cmath>
 #include <boost/tuple/tuple.hpp>
 #include "gnuplot-iostream.h"



  #ifndef HEATMAP_H
  #define HEATMAP_H



 class HeatMap
 {
 public:
  HeatMap(){};
  ~HeatMap(){};
  Error generateHeatMaps(std::string fname, std::vector<std::vector<std::pair<double, double>>> *polarHeatmap);

private:
  Error err;
  CSVReader csv;
  std::vector<std::vector<std::pair<double, double>>> *heatmapVector;
  std::vector< std::pair < int, int > > sections_ind;
  static std::vector<std::vector<double>> original_request_csv;
  Error generateHeatMapSection(int section, bool forward_reverse, int begin, int end);
  std::string double2strPercision(double number, int percision);

 };







  #endif
