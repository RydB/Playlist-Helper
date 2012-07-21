/* 
 * File:   Options.h
 * artist: ben
 *
 * Created on March 12, 2012, 12:14 PM
 */

#ifndef OPTIONS_H
#define	OPTIONS_H

#include "Index.h"

class Options{
    char c;
    void printHelp();
    void printVersion();
public:
    
    //Parses the options using the getopt library.  Returns false if help or
    // version is chosen as an option, true otherwise.
    bool parse(int argc, char** argv, Index& index);
    
};


#endif	/* OPTIONS_H */

