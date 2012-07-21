/* 
 * File:   Index.h
 * artist: ben
 *
 * Created on March 11, 2012, 9:47 PM
 */

#ifndef INDEX_H
#define	INDEX_H

#include "IndexError.h"

enum CommandType {TITLE, ARTIST, KEYWORD, DELETE, INSERT, INS_SEARCH, BEGINNING,
                  END, PRINT, QUIT, INVALID};
                  
enum ListType {MASTER, PLAY, SEARCH, HASH_SEARCH};

class Index{
    vector<Playlist> master, play, hashSearch, lowerMaster;
    
    //Contains title and artist search results.
    map<string, multimap <string, int> > search; 
    
    char command;
    string cHolder, argument;
    std::ifstream ins;
    CommandType type;
    multimap<string, int> artistIndex;
    multimap<string, int> titleIndex;
    MyHash hash;
    
    //Since the hash search and the search data members are different data
    // types, I need to be able to differentiate between which search playlist
    // is active for the insertSearchResults() function.
    bool useHashSearch;
    
    /******************/
    /* Error Checking */
    /******************/
    
    //Checks if the specified index is outside the range of the (listType)vector
    //  Used in the playlist operations.
    bool outsideRange(unsigned int index, ListType type);
    
    
    /*********************/
    /* Utility functions */
    /*********************/
    
    
    //In the parse function, it will convert the user command into an enum and
    // initialize the type data member.
    void setType();
    
    //Gets user inputted command and stores it in cHolder; also prints the %'s.
    void setHolder();
    
    //Trims trailing and leading whitespace in playlist data for printing.
    void trim(Playlist& line);
    
    //Places all the strings between lower and upper in the search vector.
    void findStrings(string upper, string lower, 
                        const std::multimap<string, int>& index);
    
    
    //Converts the argument data member to an int for playlist operations.
    int argToInt() const;
    
    /* Search Utilities*/
    
    bool getBounds(std::multimap<string, int>::const_iterator& bottom,
                        std::multimap<string, int>::const_iterator& top, 
                        const string& upper, const string& lower,
                        const std::multimap<string, int>& index) const;
    
    void titleSearchHelper(const string& upper,const string& lower);
    void artistSearchHelper(const string& upper, const string& lower);
    
    /************************************************************************/

public:
    
    /*************/
    /* Interface */
    /*************/
    
    /* Getters */
    vector<Playlist>& getMaster();
    vector<Playlist>& getPlay();
    map<string, multimap <string, int> >&  getSearch();
    std::ifstream& getStream();
    CommandType getType() const;
    
    vector<string> split(const string& str, const char del, bool all) const;
    
    /* Initialization and printing */
    
    //Reads a text file with the mp3 info and assembles
    // the master Playlist vector.
    void initMaster();
    bool parse();
    
    //Prints the specified playlist
    void print(ListType type) const;
    
    
    /* Search Functions */
    
    void artistSearch();
    void titleSearch();
    void keywordSearch();
    
    /* Playlist Operations */
    
    //Inserts the song at the specified index from the master playlist vector
    // to the end of the play playlist vector.
    void insertSong();
    
    //Adds appends the play playlist vector with all the items in 
    //the search vector.
    void insertSearchResults();
    
    //Deletes the song at the specified index from the play playlist vector.
    void deleteSong();
    
    //Moves the song at the specified index from the play playlist vector to the
    // beginning of the playlist.
    void moveBeginning();
    
    //Moves the song at the specified index from the play playlist vector to the
    // end of the playlist.
    void moveEnd();
};


#endif	/* INDEX_H */

