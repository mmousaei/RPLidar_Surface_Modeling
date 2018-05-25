/*    error.h - source for processing errors
 *
 *    Carnegie Mellon University
 *    Authors: Lawrence Papincak
 *
 */

#include "error.h"

void showErr(Error *err) {
    if( err ) {
        std::cout << BOLDRED << "Localization error - " << Error_Message[*err] << ENDC << std::endl;
    }
}

void showWarn(Error *err) {
    if( err ) {
        std::cout << BOLDYEL << "Localization warning - " << Error_Message[*err] << ENDC << std::endl;
    }
}
