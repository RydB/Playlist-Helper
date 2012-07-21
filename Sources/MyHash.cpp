#include "MyHash.h"


MyHash::MyHash(){
	table.reserve(TABLE_SIZE);
}


int MyHash::hashing(string key){
    
    const char* temp = key.c_str();
    int c;
    unsigned int hash = 5381;
    
    while(c = *temp++){
    	hash = ((hash << 5) + hash) + c;
    }
    
    return hash;
    
}

void MyHash::insert(string key, int index){
	unsigned int loc = findTableIndex(key);
	
	if(table[loc].size() == 0){
		Bucket temp(key, index);
		table[loc].push_back(temp);
	} else {
		bool repeatWord = false;
		
		unsigned int i = 0;
		for (; i < table[loc].size(); i++){
			if(key == table[loc][i].key){
				repeatWord = true;
				break;
			}
			
		}
		
		if(repeatWord){
			bool indexFound = false;
			for(unsigned int j = 0; j < table[loc].size(); j++){
				for (unsigned int k = 0; k < table[loc][j].indices.size(); k++){
					if(index == table[loc][j].indices[k]) indexFound = true;
				}
			
			}
			if(!indexFound) table[loc][i].indices.push_back(index);
			
		} else{
			Bucket temp(key, index);
			table[loc].push_back(temp);
		}
	
	}
	
	
}

unsigned int MyHash::findTableIndex(string key){
	unsigned int WHY = hashing(key);
	WHY = WHY % TABLE_SIZE;
	return WHY;
}

void MyHash::printBuckets() const{
    
    
    std::cout << table[342][0].key;
    std::cout << table[342][0].indices[0];
    std::cout << table[342][0].indices[1];
    std::cout << table[342][0].indices[2];
    
    /*std::set<int>::const_iterator it;
    for(unsigned int i = 0; i < buckets.size(); i++){
        std::cout << buckets[i].keyword << ": ";
        for(it = buckets[i].indices.begin(); it != buckets[i].indices.end(); it++){
            std::cout << *it << ", ";
        }
        std::cout << "\n\n";
    }
    
    
    for(unsigned int i = 0; i < TABLE_SIZE; i++){
    	if(table[i].size() > 0){
    		std::cout << "Table Entry " << i << ": \n";
    		for (unsigned int j = 0; table[i].size(); j++){
    			std::cout << "Bucket" << j << " | " << "word: " << table[i][j].key << ": ";
    			for(unsigned int k = 0; k < table[i][j].indices.size(); k++){
    				std::cout << table[i][j].indices[k];    			
    			}
    			std::cout << "\n";
    		}
    		std::cout << "\n"; 
    	}
    }*/
}

void MyHash::search(vector<string> keys, vector<int>& intersect){

	vector<int> a, b;
	bool match;
	
	for(unsigned int i = 0; i < keys.size(); i++){
		match = false;
		//Find the index into the hash table
		int loc = findTableIndex(keys[i]);
		
		//Make sure there's actually a keyword corresponding to the key.
		if(table[loc].size() > 0){
			
			//Loop through each bucket at that table entry.
			for(unsigned int j = 0; j < table[loc].size(); j++){
				//If there is a match with the current key and the key at that table entry
				if(table[loc][j].key == keys[i]){
					//Loop through all the data at that table entry and place them in a.
 					for (unsigned int k = 0; k < table[loc][j].indices.size(); k++){
						a.push_back(table[loc][j].indices[k]);
					}
				}
			}
			
			//Assuming out intersect vector has stuff in it..
			if(intersect.size() > 0){
				//Loop through a and intersect and any matching indices will be placed in b.
				//  There is where the intersection happens.
				for(unsigned int j = 0; j < a.size(); j++){
					for(unsigned int k = 0; k < intersect.size(); k++){
						if(a[j] == intersect[k]){
							match = true;
							b.push_back(a[j]);
							break;
						}
					}
				}
			} else {
				//If intersect is empty we can just skip right to making b = a
				match = true;
				b = a;
			}
			
			//Set intersect = b, since b currently holds the intersection between a and intersect.
			//Afterwards clear a and b to start again.
			intersect = b;
			b.clear();
			a.clear();
		}
		
		//If no matches were found for this word, then clear out the whole intersect vector
		// since no songs match one word in the keyword search.
		if(!match) intersect.clear();
	
	}

    /*std::set<int> a, b, inter;
    std::set<int>::iterator it, it2;
    bool match = false;
    
    for(unsigned int i = 0; i < keys.size(); i++){
        for(unsigned int j = 0; j < buckets.size(); j++){
            if(keys[i] == buckets[j].keyword){
            	match = true;
                for(it = buckets[j].indices.begin(); it != buckets[j].indices.end(); it++){
                    a.insert(*it);
                }
                
                
                if(inter.size() > 0){
                    for(it = a.begin(); it != a.end(); it++){
                        for(it2 = inter.begin(); it2 != inter.end(); it2++){
                            if(*it == *it2){
                                b.insert(*it);
                                break;
                            }
                        }
                    }
                } else {
                    b = a;
                }
                
                inter = b;
                
                b.clear();
                a.clear();
                break;
            }
            
            if(j == buckets.size()-1 && !match){
            	inter.clear();
            	b.clear();
            	a.clear();
            }
            
        }
    }
    intersect = inter;
    */
}



