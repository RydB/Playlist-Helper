/* 
 * File:   MyHash.h
 * Author: ben
 *
 * Created on March 17, 2012, 2:04 PM
 */

#ifndef MYHASH_H
#define	MYHASH_H

#include "Bucket.h"

const int TABLE_SIZE = 4259;


class MyHash{
    //vector< vector<Bucket> > table;
    
        
public:
     vector< vector<Bucket> > table;
    
    MyHash();
    
    int hashing(string key);
       
    
    void insert(string key, int index);
    unsigned int findTableIndex(string key);
    
    void search(vector<string> keys, vector<int>& intersect);
    
    void printBuckets() const;
    
};


#endif	/* MYHASH_H */

