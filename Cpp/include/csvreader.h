/*    csvreader.h - class definition for csvreader class that reads data from
 *                  archived radPiper data files
 *
 *    Carnegie Mellon University
 *    Authors: Lawrence Papincak
 *
 */

#ifndef CSVREADER_H
#define CSVREADER_H

#include "error.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <cstdio>
#include <inttypes.h>
#include <stdexcept>

#include <boost/algorithm/string.hpp>

#define MAX_LINE_ITER 100000

class CSVReader {

public:
    CSVReader(std::string delim = ",") :
              delim(delim)
    {}

    ~CSVReader();

    Error read(std::string fname, std::vector<std::vector<double>> *data);
    Error read(std::string fname, std::vector<std::vector<std::string>> *data);
private:
    std::string delim;
}; // CSVReader

#endif
