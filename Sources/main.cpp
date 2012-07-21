//To do:make generic function that separates strings based on some delimiter (a space)
//vector <string> split(string str, char, delimiter), loop over this to get all keywords; can use to find | or spaces, do error checking, check for vector.size() == 2 for |
#include "Options.h"
using namespace std;
/*
 * 
 */

int main(int argc, char** argv) {
       
    Index index;
    Options options;
    
    
    try{
        if(!options.parse(argc, argv, index)) return 0;

        index.initMaster();
        std::cout << index.getMaster().size() << " songs loaded\n";

        bool run = index.parse();
        while(run){
            switch(index.getType()){
                case TITLE:
                    index.titleSearch();
                    break;
                case ARTIST:
                    index.artistSearch();
                    break;
                case KEYWORD:
                    index.keywordSearch();
                    break;
                case DELETE:
                    index.deleteSong();
                    break;
                case INSERT:
                    index.insertSong();
                    break;
                case INS_SEARCH:
                    index.insertSearchResults();
                    break;
                case BEGINNING:
                    index.moveBeginning();
                    break;
                case END:
                    index.moveEnd();
                    break;
                case PRINT:
                    index.print(PLAY);
                    break;
                case INVALID:
                    break;
                case QUIT:
                   break;
            }

            run = index.parse();
        }


    } catch (IndexError& e){
        e.print();
        return 1;
    }
    
    return 0;
}

