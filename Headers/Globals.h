/* 
 * File:   Globals.h
 * Author: ben
 *
 * Created on March 12, 2012, 12:04 PM
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

#include <string>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <getopt.h>
#include <sstream>
#include <ctype.h>
#include <set>
#include <map>

using std::vector;
using std::string;
using std::multimap;
using std::map;

const string HELP_FILE = "help.txt";

//For use with the split function in tools.
const char BAR = '|';
const char SPACE = ' ';
const char NOT_APPLICABLE = 'N';
const bool USE_ALL_NON_ALNUMS = true;
const bool USE_ONLY_DEL = false;
/****************************************/

const int C_SONG = 0;
const int C_ARTIST = 1;




#endif	/* GLOBALS_H */

