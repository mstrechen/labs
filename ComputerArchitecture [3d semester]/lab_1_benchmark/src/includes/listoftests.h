#ifndef LISTOFTESTS_H_
#define LISTOFTESTS_H_

#include<vector>
#include<functional>
#include<utility>

using namespace std;

#ifndef COUNT_OF_ITERATIONS
    #define COUNT_OF_ITERATIONS (1000*1000*100)
#endif

#ifndef MOD
    #define MOD (16 * 16 * 16 * 16)
#endif

#ifndef INIT_VALUE
    #define INIT_VALUE (11323)
#endif

namespace COLORS {
    const int REGULAR = 0; 
    const int RED = 1; 
    const int GREEN = 2;
    const int YELLOW = 3; 
    const int BLUE = 4;
    const int MAGENTA = 5;
    const int CYAN = 6;
    const int BLACK = 7;
};

vector<function<tuple<int, string, double>() > > get_functions_to_test();

#endif