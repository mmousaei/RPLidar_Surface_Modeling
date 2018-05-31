/*    rpread.cpp - class source for reader class that reads data from
 *                    RPLidar cvs file and returns ranges and angles
 *
 *    Carnegie Mellon University
 *    Authors: Mohammadreza Mousei
 *    Contact: mmousaei@andrew.cmu.edu
 *
 */


#include "rpreader.h"

std::vector<std::vector<double>> RPReader::original_csv;

Error RPReader::read(std::string fname,std::vector<std::vector<std::pair < double, double >>> *polar)
{
  // std::vector<std::vector<double>> original_csv;

  std::vector<std::pair < double, double >> row;
  err = csv.read(fname, &original_csv);
  double angle_increment, angle_min, angle_max, angle;
  std::pair < double, double > pol;

  // if( err ) { showErr(&err); return FAILED_FILE_OPEN; }

  for(int i = 0; i < original_csv[0].size(); i++)
  {
    angle_increment = original_csv[8][i];
    angle_min = original_csv[6][i];
    angle_max = original_csv[7][i];
    for(int j = 13; j < 13+360; j++)
    {
      angle = angle_min + (j-13)*angle_increment;
      pol.first = original_csv[j][i];
      pol.second = angle;
      row.push_back(pol);
    }
    polar->push_back(row);
    row.erase(row.begin(), row.end());
  }
  return NO_ERROR;
}


Error RPReader::write(std::string fname,std::vector<std::vector<std::pair < double, double >>> *polar)
{
    std::vector<double> row;
    std::vector<std::vector<double>> output;

    for(int i = 0; i < polar->size(); i++)
    {
      row.push_back(original_csv[3][i]);
      row.push_back(original_csv[4][i]);
      for(int j = 0; j < polar->at(0).size(); j++)
      {
        row.push_back(polar->at(i)[j].first);
      }
      for(int j = 0; j < polar->at(0).size(); j++)
      {
        row.push_back(polar->at(i)[j].second);
      }
      output.push_back(row);
      row.erase(row.begin(), row.end());
    }
    csv.writeLog("../csv/centered.csv", output);
}
