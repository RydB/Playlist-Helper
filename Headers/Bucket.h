/* 
 * File:   Bucket.h
 * Author: ben
 *
 * Created on March 19, 2012, 1:00 PM
 */

#ifndef BUCKET_H
#define	BUCKET_H

#include "Playlist.h"

struct Bucket{
	string key;
    vector<int> indices;
    Bucket(string k, int ind){
    	key = k;
    	indices.push_back(ind);
    }
};

#endif	/* BUCKET_H */

