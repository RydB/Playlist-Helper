#include "IndexError.h"

IndexError::IndexError(std::string e){
    error = e;
}

void IndexError::print(){
    std::cerr << error;
}

