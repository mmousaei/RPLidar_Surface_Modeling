/*    rpread.cpp - class source for reader class that reads data from
 *                    RPLidar cvs file and returns ranges and angles
 *
 *    Carnegie Mellon University
 *    Authors: Mohammadreza Mousei
 *    Contact: mmousaei@andrew.cmu.edu
 *
 */


#include "rpreader.h"


Error RPReader::read(std::string fname,std::vector<std::vector<std::pair < double, double >>> *polar)
{
  std::vector<std::vector<double>> data;
  std::vector<std::pair < double, double >> row;
  err = csv.read(fname, &data);
  double angle_increment, angle_min, angle_max, angle;
  std::pair < double, double > pol;

  // if( err ) { showErr(&err); return FAILED_FILE_OPEN; }

  for(int i = 0; i < data[0].size(); i++)
  {
    angle_increment = data[8][i];
    angle_min = data[6][i];
    angle_max = data[7][i];
    for(int j = 13; j < 13+359; j++)
    {
      angle = angle_min + (j-13)*angle_increment;
      pol.first = data[j][i];
      pol.second = angle;
      row.push_back(pol);
    }
    polar->push_back(row);
    row.erase(row.begin(), row.end());
  }
  return NO_ERROR;
}
