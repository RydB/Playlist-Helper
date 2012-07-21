/* 
 * File:   IndexError.h
 * artist: ben
 *
 * Created on March 11, 2012, 10:38 PM
 */

#ifndef INDEXERROR_H
#define	INDEXERROR_H

#include "MyHash.h"

const string INVALID_BARS = "A:ERROR: Invalid number of '|'\n";
const string HELP_ERROR = "B:ERROR: cannot open help file.\n";
const string INDEX_FILE_ERROR = "C:ERROR: cannot open master index file.\n";
const string OUT_OF_RANGE = "D:ERROR: In playlist operations, out of range.\n";

class IndexError{
    std::string error;
public:
    IndexError(std::string e);
    void print();
};

#endif	/* INDEXERROR_H */

