/*    rpread.h - class definition for reader class that reads data from
 *                    RPLidar cvs file and returns ranges and angles
 *
 *    Carnegie Mellon University
 *    Authors: Mohammadreza Mousei
 *    Contact: mmousaei@andrew.cmu.edu
 *
 */

 #ifndef RPREADER_H
 #define RPREADER_H


 #include "error.h"
 #include "csvreader.h"

 #include <stdlib.h>
 #include <stdio.h>
 #include <iostream>
 #include <cstdio>
 #include <iostream>
 #include <string>
 // #include <vector>
 #include <utility>

 #include <boost/program_options.hpp>
 #include <boost/filesystem.hpp>

class RPReader
{

public:
  RPReader(){};
  ~RPReader(){};
  Error read(std::string fname,std::vector<std::vector<std::pair<double, double>>> *polar);

private:
  Error err;
  CSVReader csv;
};

#endif
