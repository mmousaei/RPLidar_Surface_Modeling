/*    error.h - definition for processing errors
 *
 *    Carnegie Mellon University
 *    Authors: Lawrence Papincak
 *
 */

#ifndef ERROR_H
#define ERROR_H

#include <iostream>

#define BOLDBLUE "\033[1m\033[94m"
#define BOLDRED  "\033[1m\033[31m"
#define BOLDYEL  "\033[1m\033[93m"
#define ENDC     "\033[0m"

#define DEBUG

enum Error {
    NO_ERROR               = 0,
    NO_MOTOR_DATA          = 1,
    NO_RANGE_DATA          = 2,
    NO_COMMENT_DATA        = 3,
    READ_MOTOR_FAIL        = 4,
    READ_RANGE_FAIL        = 5,
    READ_COMMENT_FAIL      = 6,
    INVALID_CMD_INPUT      = 7,
    NO_DATA_DIRECTORY      = 8,
    FAILED_FILE_OPEN       = 9,
    NO_REVERSAL_TIME_FOUND = 10,
    NO_IMAGES_DATA         = 11,
    NO_IMAGES_FOUND        = 12,
    READ_IMG_META_FAIL     = 13,
    LINEFIT_XY_SIZE        = 14
};

static const char* Error_Message[] = {
    "No error",
    "No motor_status.csv file found, aborting!",
    "No range_values.csv file found, aborting!",
    "No executive_comments.csv file found, aborting!",
    "Failed to read motor data, aborting!",
    "Failed to read range data, aborting!",
    "Failed to read rosout data, aborting!",
    "Incorrect command call.",
    "Archived data directory does not exists.",
    "Failed to open file for reading.",
    "No reversal time found for segmenting data, aborting!",
    "No camera_image_raw_compressed.csv file found, aborting!",
    "No camera_image_raw_compressed directory found in archieved directory, aborting!",
    "Failed to read image meta data, aborting!",
    "X and Y data sizes are not consistent or empty, aborting line fit"
};

// Prototype for error reporting
void showErr(Error *err);

// Prototype for warning reporting
void showWarn(Error *err);

#endif
