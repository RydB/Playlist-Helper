#include "Options.h"
#include "Index.h"

bool Options::parse(int argc, char** argv, Index& index){
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'V'}
    };
    
    while ( (c = getopt_long(argc, argv, "hV", long_options, NULL)) ){
        if (c == -1) { 
            if (argc == optind+1){
                index.getStream().open(argv[optind]);
                if(!index.getStream().is_open()) 
                    throw IndexError(INDEX_FILE_ERROR);
            }
            break;
        }
        
        switch(c){
            case 'h':
                printHelp();
                return false;
            case 'V':
                printVersion();
                return false;
        }
    }
    return true;
}

void Options::printVersion(){
    std::cout << "mp3Index - v1.0\nartist: Ben Ryding\n";
}

void Options::printHelp(){
    std::ifstream helpFile(HELP_FILE.c_str());
    if (!helpFile) throw IndexError(HELP_ERROR);
    std::ostringstream os;
    os << helpFile.rdbuf();
    std::cout << os.str();
}


