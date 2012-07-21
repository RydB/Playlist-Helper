#include "Tools.h"

string Tools::transformLower(string s){
    for(unsigned int i = 0; i < s.length(); i++){
        s[i] = tolower(s[i]);
    }    
    
    return s;
}

bool Tools::strComp(const string& a, const string& b) const{
    if(strcasecmp(a.c_str(), b.c_str()) >= 0) return true;
    return false;
}

template <class T>
void Tools::printVector(const vector<T>& v) const{
    for(unsigned int i = 0; i < v.size(); i++){
        std::cout << v[i] << std::endl;
    }
}
