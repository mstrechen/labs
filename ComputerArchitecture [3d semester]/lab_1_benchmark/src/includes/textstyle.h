#ifndef _TEXTSTYLE_H_
#define _TEXTSTYLE_H_

#include<string>
using namespace std;

namespace TEXT{
    #ifdef __linux__ 
        const string REGULAR = "\033[0m";
        
        const string RED = "\033[1;31m";
        const string GREEN = "\033[1;32m";
        const string YELLOW = "\033[1;33m";
        const string BLUE = "\033[1;34m";
        const string MAGENTA = "\033[1;35m";
        const string CYAN = "\033[1;36m";
        const string BLACK = "\033[1;30m";
        const string WHITE_BACKGROUND = "\033[1;47m";
    #else
        const string REGULAR = "";
        
        const string RED = "";
        const string GREEN = "";
        const string YELLOW = "";
        const string BLUE = "";
        const string MAGENTA = "";
        const string CYAN = "";
        const string BLACK = "";
        const string WHITE_BACKGROUND = "";
    #endif

    template<int LENGTH = 1>
    string CORNER(){
        #ifdef __linux__
            return BLACK + WHITE_BACKGROUND + string(LENGTH, ' ') + REGULAR;
        #else 
            return '█';
        #endif
    }
    
    string perfomance_line(int, int);
}


#endif