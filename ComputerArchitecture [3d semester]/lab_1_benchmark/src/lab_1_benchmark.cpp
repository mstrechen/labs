#include<iostream>
#include<iomanip>
#include<chrono>
#include<functional>
#include<vector>
#include<cmath>

using namespace std;

const int COUNT_OF_ITERATIONS = 1e7;
const int INIT_VALUE = 11323;
const int MOD = 16 * 16 * 16 * 16;
const int MAX_COUNT_OF_MARKS = 25;


namespace TEXT{
    string RED = "\033[1;31m";
    string GREEN = "\033[1;32m";
    string YELLOW = "\033[1;33m";
    string BLUE = "\033[1;34m";
    string MAGENTA = "\033[1;35m";
    string CYAN = "\033[1;36m";
    
    string REGULAR = "\033[0m";
    string BLACK = "\033[1;30m";
    string WHITE_BACKGROUND = "\033[1;47m";

    string CORNER = BLACK + WHITE_BACKGROUND + " " + REGULAR;
 
}

class CPUID {
  uint32_t regs[4];

public:
  explicit CPUID(unsigned i) {
#ifndef _WIN32
    asm volatile
      ("cpuid" : "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])
       : "a" (i), "c" (0));
    // ECX is set to zero for CPUID function 4
#endif
  }

  const uint32_t &EAX() const {return regs[0];}
  const uint32_t &EBX() const {return regs[1];}
  const uint32_t &ECX() const {return regs[2];}
  const uint32_t &EDX() const {return regs[3];}
};

string getCPUVendor(){
    string vendor;
    #ifdef _WIN32
    	vendor = "unknown";
    #else
	CPUID cpuID(0); // Get CPU vendor
        vendor += string((const char *)&cpuID.EBX(), 4);
        vendor += string((const char *)&cpuID.EDX(), 4);
        vendor += string((const char *)&cpuID.ECX(), 4);
    #endif
    return vendor;
}

string getHeadline(){
    string result;
    result += TEXT::RED 
           + "CPU vendor : "
    	   + getCPUVendor()
           + TEXT::REGULAR
	   + "\n";
    result += TEXT::GREEN 
	   + "COUNT OF ITERATIONS : " 
           + to_string(COUNT_OF_ITERATIONS) 
	   + " (10^" + to_string((int)log10(COUNT_OF_ITERATIONS)) + ")" 
           + "    TYPE : " 
	   + to_string(sizeof(void *) * 8) 
           + "-BIT" 
           + TEXT::REGULAR;
   return result;
}

string getPerfomanceLine(int perfomance){
    return string(perfomance, '#') + string(MAX_COUNT_OF_MARKS - perfomance, ' ');
}

void makeHeader(){
    cout << TEXT::BLACK << TEXT::WHITE_BACKGROUND << 
    "   OPERATION  :"
    "    TIME    :"
    "   REAL TIME   :"
    "       %      :"
    "   OP PER SEC  :"
    " " << string(MAX_COUNT_OF_MARKS, '#') << "  " << endl;
    cout << TEXT::REGULAR;
}
void makeLastRow(){
    cout << TEXT::BLACK << TEXT::WHITE_BACKGROUND;
    for(int i = 0; i < 103; i++)
        cout << " ";
    cout << TEXT::REGULAR;
}


void makeRow(string name, double time, double min_time, double basic_result, double plus_result){
    cout << TEXT::CORNER 
	 << " " << setw(11 + 7) << name 
	 << TEXT::REGULAR 
	 << " : " << setw(10) << time << " : " 
	 << setw(10);
    if(basic_result != time){
        cout << time -  basic_result << " ms : " 
	     << setw(12) <<  plus_result / (time - basic_result) << " : " 
	     << setw(13) << (scientific)
             << (long long)(COUNT_OF_ITERATIONS / (time - basic_result)) * 1e3
             << (fixed)
             << " : ";
    } else {
        cout << "  ¯\\_(ツ)_/¯  :";
        cout << "  ¯\\_(ツ)_/¯  : ";
        cout << "  ¯\\_(ツ)_/¯  : ";
    }
    
    int perfomance;
    if(basic_result >= time)
        perfomance = MAX_COUNT_OF_MARKS;
    else
        perfomance = min<int>(MAX_COUNT_OF_MARKS, ceil(min_time * MAX_COUNT_OF_MARKS / (time - basic_result)));
   
    cout << getPerfomanceLine(perfomance) 
	 << " "
    	 << TEXT::CORNER
    	 << endl;
}

int main(){
    cout << getHeadline() << endl;


    vector<function<pair<string, double>() > > functions_to_run = { 
        []() -> pair<string, double> {
            int x = INIT_VALUE; 
            for(int i = 0; i < COUNT_OF_ITERATIONS; i++)
                x = i,
                x %= MOD;

            return {TEXT::GREEN + "int  =", x};
        },
        []() -> pair<string, double> {
            int x = INIT_VALUE; 
            for(int i = 0; i < COUNT_OF_ITERATIONS; i++)
                x += i,
                x %= MOD;
            return  {TEXT::GREEN + "int +=", x};
        },
        []() -> pair<string, double> {
            unsigned int x = INIT_VALUE; 
            for(int i = 0; i < COUNT_OF_ITERATIONS; i++)
                x += i,
                x %= MOD;
            return  {TEXT::GREEN + "uint +=", x};
        },
        []() -> pair<string, double> {
            int x = INIT_VALUE; 
            for(int i = 0; i < COUNT_OF_ITERATIONS; i++)
                x -= i,
                x %= MOD;
            return {TEXT::GREEN + "int -=", x};
        },
        []() -> pair<string, double> {
            int x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i,
                x %= MOD;
            return  {TEXT::GREEN + "int *=", x};
        },
        []() -> pair<string, double> {
            unsigned int x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i,
                x %= MOD;
            return  {TEXT::GREEN + "uint *=", x};
        },
        []() -> pair<string, double> {
            int x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x += COUNT_OF_ITERATIONS,
                x /= i;
            return {TEXT::GREEN + "int /=", x};
        },
        []() -> pair<string, double> {
            int x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x += COUNT_OF_ITERATIONS,
                x %= i;
            return {TEXT::GREEN + "int %=", x};
        },


        []() -> pair<string, double> {
            char x = 0x3f; 
            for(int i = 0; i < COUNT_OF_ITERATIONS; i++)
                x += i,
                x %= MOD;
            return  {TEXT::CYAN + "char +=", x};
        },
        []() -> pair<string, double> {
            int16_t x = 0x3f; 
            for(int i = 0; i < COUNT_OF_ITERATIONS; i++)
                x += i,
                x %= MOD;
            return  {TEXT::MAGENTA + "int16_t +=", x};
        },

        []() -> pair<string, double> {
            int64_t x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x += i,
                x %= MOD;
            return {TEXT::RED + "int64_t +=", x};
        },
        []() -> pair<string, double> {
            uint64_t x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x += i,
                x %= MOD;
            return {TEXT::RED + "uint64_t +=", x};
        },
        []() -> pair<string, double> {
            int64_t x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i,
                x %= MOD;
            return {TEXT::RED + "int64_t *=", x};
        },
        []() -> pair<string, double> {
            uint64_t x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i,
                x %= MOD;
            return {TEXT::RED + "uint64_t *=", x};
        },
        []() -> pair<string, double> {
            float x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x += i;
            return {TEXT::YELLOW + "float  +=", x};
        },
        []() -> pair<string, double> {
            float x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i;
            return {TEXT::YELLOW + "float  *=", x};
        },
        []() -> pair<string, double> {
            float x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x /= i;
            return {TEXT::YELLOW +"float  /=", x};
        },
        []() -> pair<string, double> {
            float x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i,
                x /= i;
            return {TEXT::YELLOW +"float */=", x};
        },
        []() -> pair<string, double> {
            double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x += i;
            return {TEXT::MAGENTA + "double  +=", x};
        },
        []() -> pair<string, double> {
            double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i;
            return {TEXT::MAGENTA + "double  *=", x};
        },
        []() -> pair<string, double> {
            double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x /= i;
            return {TEXT::MAGENTA +"double  /=", x};
        },
        []() -> pair<string, double> {
            double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i,
                x /= i;
            return {TEXT::MAGENTA +"double */=", x};
        },
        []() -> pair<string, double> {
            long double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x += i;
            return {TEXT::MAGENTA + "float80  +=", x};
        },
        []() -> pair<string, double> {
            long double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i;
            return {TEXT::MAGENTA + "float80  *=", x};
        },
        []() -> pair<string, double> {
            long double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x /= i;
            return {TEXT::MAGENTA +"float80  /=", x};
        },
        []() -> pair<string, double> {
            long double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i,
                x /= i;
            return {TEXT::MAGENTA +"float80 */=", x};
        },
        
        
    };

    vector<pair<string, double > > results;
    for(auto & f : functions_to_run){
        auto begin = chrono::high_resolution_clock::now();
        auto res = f();
        auto end = chrono::high_resolution_clock::now();
        int duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
        results.emplace_back(res.first,  duration / 1e3);
    }   

    double basic_result = results.front().second;
    double plus_result = 100 * (results[1].second - basic_result);

    double min_time = 1e40;
    for(auto & res : results)
        if(res.second != basic_result)
            min_time = min(min_time, res.second - basic_result);


    cout.precision(3);
    cout << (fixed);
    
    makeHeader();
    
    for(auto & result : results)
        makeRow(result.first, result.second, min_time, basic_result, plus_result);
    

    makeLastRow();
    cout << endl;

}