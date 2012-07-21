#include "Index.h"

vector<Playlist>& Index::getMaster(){
    return master;
}

vector<Playlist>& Index::getPlay(){
    return play;
}

map<string, multimap <string, int> > & Index::getSearch(){
    return search;
}

std::ifstream& Index::getStream() {
    return ins;
}

CommandType Index::getType() const{
    return type;
}

void Index::initMaster(){
    
    Tools drill;
    string holder;
    int index = 1;
    
    while( (getline(ins, holder)) ) {
        if(holder == "") continue;
        Playlist temp, lower;
        if(holder == "|"){
            temp.song = "";
            temp.artist = "";
        } else {
            vector<string> container = split(holder, BAR, USE_ONLY_DEL);

            if (container.size() != 2) throw IndexError(INVALID_BARS);
            temp.song = container[C_SONG];
            temp.artist = container[C_ARTIST];
            trim(temp);
            lower.song = drill.transformLower(temp.song);
            lower.artist = drill.transformLower(temp.artist);
        }
        
        temp.masterIndex = index;
        lower.masterIndex = index;
        
        master.push_back(temp);
        lowerMaster.push_back(lower);
        
        artistIndex.insert(std::make_pair(lower.artist, index));
        titleIndex.insert(std::make_pair(lower.song, index));
                
        index++;
    }
    
    //Put all the words into the hash table.
    for(unsigned int i = 0; i < master.size(); i++){
        vector<string> s_words = split(master[i].song, NOT_APPLICABLE, USE_ALL_NON_ALNUMS);
        vector<string> a_words = split(master[i].artist, NOT_APPLICABLE, USE_ALL_NON_ALNUMS);
        
        for(unsigned int j = 0; j < s_words.size(); j++){
            if(s_words[j] != ""){
                hash.insert(drill.transformLower(s_words[j]), i+1);
            }
        }
        
        for(unsigned int j = 0; j < a_words.size(); j++){
            if(a_words[j] != ""){
                hash.insert(drill.transformLower(a_words[j]), i+1);
            }
        }
    }
    
}

void Index::setHolder(){
    std::cout << "% ";
    getline(std::cin, cHolder);
    while (cHolder == ""){
        std::cout << "% ";
        getline(std::cin, cHolder);
    }
}

void Index::setType(){
    if(command == 't') type = TITLE;
    else if(command == 'a') type = ARTIST;
    else if(command == 'k') type = KEYWORD;
    else if(command == 'd') type = DELETE;
    else if(command == 'i') type = INSERT;
    else if(command == 's') type = INS_SEARCH;
    else if(command == 'b') type = BEGINNING;
    else if(command == 'e') type = END;
    else if(command == 'p') type = PRINT;
    else if(command == 'q') type = QUIT;
    else type = INVALID;
}

bool Index::parse(){
    do{
        setHolder();
        command = cHolder[0];
        setType();
    }while (type == INVALID);
        
    if(type == QUIT) return false;
    
    if(cHolder.length() > 1){
        if(cHolder[1] == ' '){            
                argument.assign(cHolder, 2, cHolder.length()-1);
        } else {
                argument.assign(cHolder, 1, cHolder.length()-1);
        }
    }
           
    return true;
}

void Index::print(ListType type) const{
    switch(type){
        case HASH_SEARCH:
            for(unsigned int i = 0; i < hashSearch.size(); i++){
                std::cout << hashSearch[i].masterIndex << " "
                          << hashSearch[i].song << "|" 
                          << hashSearch[i].artist << std::endl;
            }
            break;
        case MASTER:
            for(unsigned int i = 0; i < master.size(); i++){
                std::cout << master[i].song << "|" 
                          << master[i].artist << std::endl;
            }
            break;
        case PLAY:
            for(unsigned int i = 0; i < play.size(); i++){
                std::cout << i+1 << " " 
                          << play[i].masterIndex << " "
                          << play[i].song << "|" 
                          << play[i].artist << std::endl;
            }
            break;
        case SEARCH:
            
            map<string, multimap<string, int> >::const_iterator out;
            multimap<string, int>::const_iterator in;
            for(out = search.begin(); out != search.end(); out++){
                for(in = out->second.begin(); in != out->second.end(); in++){
                    std::cout << in->second << " "
                              << master[in->second-1].song  << "|"
                              << master[in->second-1].artist << "\n";
                    
                }
            }
            break;                      
    }
    return;
}

void Index::trim(Playlist& p){  
    size_t startpos = p.song.find_first_not_of(" \t");
    size_t endpos = p.song.find_last_not_of(" \t");
    if(startpos == endpos){
        if(p.song == " "){
            p.song == "";
        }
    } 
    else p.song = p.song.substr(startpos, endpos-startpos+1);
    
    startpos = p.artist.find_first_not_of(" \t");
    endpos = p.artist.find_last_not_of(" \t");
    if(startpos == endpos){
        if(p.artist == " "){
            p.artist == "";
        }
    } 
    else p.artist = p.artist.substr(startpos, endpos-startpos+1);
    
}


vector<string> Index::split(const string& str, 
                                        const char del, bool all) const
{
    vector<string> container;
    
    int length = str.length();
    int pos(0), end(0);
     
    for(; end < length; end++){
        if(all){
            if(!isalnum(str[end])){
                 container.push_back(str.substr(pos, end-pos));
                 while(!isalnum(str[end]) && end < length){
                      end++;
                 }
                 pos = end;
            }
        } else {
            if(str[end] == del){
                container.push_back(str.substr(pos, end-pos));
                end++;
                pos = end;
            }
        }
    }
    
    container.push_back(str.substr(pos, end-pos));
    
    return container;
}

bool Index::getBounds(multimap<string, int>::const_iterator& bottom,
                        multimap<string, int>::const_iterator& top, 
                        const string& upper, const string& lower,
                        const multimap<string, int>& index) const
{
    if(upper < lower){
       bottom = index.lower_bound(upper);
       top = index.upper_bound(lower);
       return true;
    }
    
    bottom = index.lower_bound(lower);
    top = index.upper_bound(upper);
    
    return true;
}

void Index::artistSearchHelper(const string& upper, const string& lower)
{    
    multimap<string, int>::const_iterator bottom, top;
    getBounds(bottom, top, upper, lower, artistIndex);
    
    for(; bottom != top; bottom++){
        search[lowerMaster[bottom->second-1].artist].insert(std::make_pair(lowerMaster[bottom->second-1].song, bottom->second));
    } 
    
}

void Index::titleSearchHelper(const string& upper, const string& lower)
{    
    multimap<string, int>::const_iterator bottom, top;
    
    getBounds(bottom, top, upper, lower, titleIndex);
    for(; bottom != top; bottom++){
        search[lowerMaster[bottom->second-1].song].insert(std::make_pair(lowerMaster[bottom->second-1].artist, bottom->second));
    }  
       
}

int Index::argToInt() const{
    int arg;
    if (argument.length() == 0) return -1;
    std::istringstream (argument) >> arg;
    return arg;
}


/* Search Functions*/

void Index::titleSearch(){
    vector<string> range = split(argument, BAR, USE_ONLY_DEL);
    
    string upper, lower;
    Tools hammer_of_doom;
    lower = hammer_of_doom.transformLower(range[0]);
    upper = hammer_of_doom.transformLower(range[1]);
    
    if(search.size() != 0) search.clear();
    titleSearchHelper(upper, lower);
    useHashSearch = false;
    print(SEARCH);
}

void Index::artistSearch(){
    vector<string> range = split(argument, BAR, USE_ONLY_DEL);
        
    string upper, lower;
    Tools wrench;
    lower = wrench.transformLower(range[0]);
    upper = wrench.transformLower(range[1]);
       
    if(search.size() != 0) search.clear();
    artistSearchHelper(upper, lower);  
    useHashSearch = false;
    print(SEARCH);
}

void Index::keywordSearch(){
    vector<string> keys = split(argument, BAR, USE_ALL_NON_ALNUMS);
    Tools screwdriver;
    if(keys.size() == 0){
        std::cout << "Input at least one word.\n";
        return;
    }
    
    for (unsigned int i = 0; i < keys.size(); i++){
        keys[i] = screwdriver.transformLower(keys[i]);
    }
    
    if(hashSearch.size() != 0) hashSearch.clear();
    
    vector<int> intersect;
    hash.search(keys, intersect);
    
    for(unsigned int i = 0; i < intersect.size(); i++){
        hashSearch.push_back(master[intersect[i]-1]);
    }
    
    useHashSearch = true;
    print(HASH_SEARCH);
}


/* Playlist operations */

void Index::insertSong(){
    unsigned int index = argToInt();
    if (index > master.size()+1 || index < 1) return;
    play.push_back(master[index-1]);
}

void Index::deleteSong(){
    unsigned int index = argToInt();
    if (index > play.size()+1 || index < 1 || play.size() == 0) return;
    play.erase(play.begin()+index-1);
}

void Index::insertSearchResults(){
    if(useHashSearch){
        for(unsigned int i = 0; i < hashSearch.size(); i++){
            play.push_back(hashSearch[i]);
        }
    } else{
        map<string, multimap<string, int> >::const_iterator outer;
        multimap<string, int>::const_iterator inner;
        for(outer = search.begin(); outer != search.end(); outer++){
            for(inner = outer->second.begin(); inner != outer->second.end(); inner++){
                Playlist p_temp;
                p_temp.artist = master[inner->second-1].artist;
                p_temp.song = master[inner->second-1].song;
                p_temp.masterIndex = inner->second;

                play.push_back(p_temp);
            }
        }
    } 
}

void Index::moveBeginning(){
    unsigned int index = argToInt();
    if (index > play.size() || index < 1) return;
    Playlist temp = play[index-1];
    play.erase(play.begin()+index-1);
    play.insert(play.begin(), temp);
}

void Index::moveEnd(){
    unsigned int index = argToInt();
    if (index > play.size() || index < 1) return;
    Playlist temp = play[index-1];
    play.erase(play.begin()+index-1);
    play.push_back(temp);
}

bool Index::outsideRange(unsigned int index, ListType type){
    switch(type){
        case MASTER:
            if(index > master.size()-1) return true;
        case PLAY:         
            if(index > play.size()-1) return true;
        case SEARCH:
        case HASH_SEARCH:
        	break;
    }
    if(index-1 < 0) return true;
    
    return false;
}
