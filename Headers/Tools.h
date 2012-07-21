/* 
 * File:   Tools.h
 * Author: ben
 *
 * Created on March 20, 2012, 11:21 PM
 */

#ifndef TOOLS_H
#define	TOOLS_H

#include "Globals.h"

class Tools{
public:
    //Returns a copy of s in all lowercase letters.
    string transformLower(string s);
    
    //Compares two strings.  True if a >= b, false otherwise.
    bool strComp(const string& a, const string& b) const;
    
    //Prints the vector v.
    template <class T>
    void printVector(const vector<T>& v) const;
};



#endif	/* TOOLS_H */

