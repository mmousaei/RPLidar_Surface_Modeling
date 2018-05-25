/*    csvreader.cpp - class source for csvreader class that reads data from
 *                    archived radPiper data files
 *
 *    Carnegie Mellon University
 *    Authors: Lawrence Papincak
 *
 */

#include "csvreader.h"

Error CSVReader::read(std::string fname, std::vector<std::vector<double>> *data) {
    // Open file stream to given csv
    std::ifstream f(fname);
    if( !f.is_open() ) {
        return FAILED_FILE_OPEN;
    }
    // Define line data for string and double types
    std::vector<std::string> splitString;
    std::string line = "";
    double res;

    // Logic for whether line width matches what we expect, based on first line
    bool validLine = false;
    // Initialize loop counter
    uint32_t lcount = 0;
    // Initialize column counter
    size_t ccount = 0;

    // Remove first line as it contains text descriptions of column contents
    getline(f,line);

    // Iterate over all lines and extract data
    while( getline(f,line) && lcount < MAX_LINE_ITER ) {
        // Split string via comma delimitation
        boost::split(splitString, line, boost::is_any_of(","));
        // Initialize column count based on first line
        if(lcount == 0) {
            data->resize(splitString.size());
            // Save column count
            ccount = splitString.size();
        }

        // Enforce column uniformity
        if( splitString.size() != ccount ) {
            validLine = false;
        } else {
            validLine = true;
        }

        if( validLine ) {
            // Iterate over all split strings and convert to doubles
            for( size_t i = 0; i < splitString.size(); i++ ) {
                // Catch empty columns
                try{
                    res = std::stod(splitString[i]);
                } catch(const std::invalid_argument&) {
                    res = 0.0;
                }
                // Push data into column
                data->at(i).push_back(res);
            }
        }
        // Incrememnt loop count
        lcount++;
    }
    // Close file
    f.close();

    return NO_ERROR;
}

Error CSVReader::read(std::string fname, std::vector<std::vector<std::string>> *data) {
    // Open file stream to given csv
    std::ifstream f(fname);
    if( !f.is_open() ) {
        return FAILED_FILE_OPEN;
    }
    // Define line data for string and double types
    std::vector<std::string> splitString;
    std::string line = "";

    // Logic for whether line width matches what we expect, based on first line
    bool validLine = false;
    // Initialize loop counter
    uint32_t lcount = 0;
    // Initialize column counter
    size_t ccount = 0;

    // Remove first line as it contains text descriptions of column contents
    getline(f,line);
    // Iterate over all lines and extract data
    while( getline(f,line) && lcount < MAX_LINE_ITER ) {
        // Split string via comma delimitation
        boost::split(splitString, line, boost::is_any_of(","));
        // Initialize column count based on first line
        if(lcount == 0) {
            data->resize(splitString.size());
            // Save column count
            ccount = splitString.size();
        }

        // Enforce column uniformity
        if( splitString.size() != ccount ) {
            validLine = false;
        } else {
            validLine = true;
        }

        if( validLine ) {
            // Iterate over all split strings and convert to doubles
            for( size_t i = 0; i < splitString.size(); i++ ) {
                // Push data into column
                data->at(i).push_back(splitString[i]);
            }
        }
        // Incrememnt loop count
        lcount++;
    }
    // Close file
    f.close();

    return NO_ERROR;
}


CSVReader::~CSVReader() {}
