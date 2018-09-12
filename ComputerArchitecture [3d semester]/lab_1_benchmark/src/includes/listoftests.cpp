#include "listoftests.h"

vector<function<tuple<int, string, double>() > > get_functions_to_test(){

    return { 
        []() -> tuple<int, string, double> {
            int x = INIT_VALUE; 
            for(int i = 0; i < COUNT_OF_ITERATIONS; i++)
                x = i, 
                x %= MOD;
            return  {COLORS::GREEN, "int  =", x};
        },
        []() -> tuple<int, string, double> {
            int x = INIT_VALUE; 
            for(int i = 0; i < COUNT_OF_ITERATIONS; i++)
                x += i,
                x %= MOD;
            return  {COLORS::GREEN, "int +=", x};
        },
        []() -> tuple<int, string, double> {
            unsigned int x = INIT_VALUE; 
            for(int i = 0; i < COUNT_OF_ITERATIONS; i++)
                x += i,
                x %= MOD;
            return  {COLORS::GREEN, "uint +=", x};
        },
        []() -> tuple<int, string, double> {
            int x = INIT_VALUE; 
            for(int i = 0; i < COUNT_OF_ITERATIONS; i++)
                x -= i,
                x %= MOD;
            return {COLORS::GREEN, "int -=", x};
        },
        []() -> tuple<int, string, double> {
            int x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i,
                x %= MOD;
            return  {COLORS::GREEN, "int *=", x};
        },
        []() -> tuple<int, string, double> {
            unsigned int x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i,
                x %= MOD;
            return  {COLORS::GREEN, "uint *=", x};
        },
        []() -> tuple<int, string, double> {
            int x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x += COUNT_OF_ITERATIONS,
                x /= i;
            return {COLORS::GREEN, "int /=", x};
        },
        []() -> tuple<int, string, double> {
            int x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x += COUNT_OF_ITERATIONS,
                x %= i;
            return {COLORS::GREEN, "int %=", x};
        },
        []() -> tuple<int, string, double> {
            char x = 0x3f; 
            for(int i = 0; i < COUNT_OF_ITERATIONS; i++)
                x += i,
                x %= MOD;
            return  {COLORS::CYAN, "char +=", x};
        },
        []() -> tuple<int, string, double> {
            int16_t x = 0x3f; 
            for(int i = 0; i < COUNT_OF_ITERATIONS; i++)
                x += i,
                x %= MOD;
            return  {COLORS::MAGENTA, "int16_t +=", x};
        },
        []() -> tuple<int, string, double> {
            int64_t x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x += i,
                x %= MOD;
            return {COLORS::RED, "int64_t +=", x};
        },
        []() -> tuple<int, string, double> {
            uint64_t x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x += i,
                x %= MOD;
            return {COLORS::RED, "uint64_t +=", x};
        },
        []() -> tuple<int, string, double> {
            int64_t x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i,
                x %= MOD;
            return {COLORS::RED, "int64_t *=", x};
        },
        []() -> tuple<int, string, double> {
            uint64_t x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i,
                x %= MOD;
            return {COLORS::RED, "uint64_t *=", x};
        },
        []() -> tuple<int, string, double> {
            float x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x += i;
            return {COLORS::YELLOW, "float  +=", x};
        },
        []() -> tuple<int, string, double> {
            float x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i;
            return {COLORS::YELLOW, "float  *=", x};
        },
        []() -> tuple<int, string, double> {
            float x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x /= i;
            return {COLORS::YELLOW, "float  /=", x};
        },
        []() -> tuple<int, string, double> {
            float x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i,
                x /= i;
            return {COLORS::YELLOW, "float */=", x};
        },
        []() -> tuple<int, string, double> {
            double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x += i;
            return {COLORS::MAGENTA, "double  +=", x};
        },
        []() -> tuple<int, string, double> {
            double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i;
            return {COLORS::MAGENTA, "double  *=", x};
        },
        []() -> tuple<int, string, double> {
            double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x /= i;
            return {COLORS::MAGENTA, "double  /=", x};
        },
        []() -> tuple<int, string, double> {
            double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i,
                x /= i;
            return {COLORS::MAGENTA, "double */=", x};
        },
        []() -> tuple<int, string, double> {
            long double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x += i;
            return {COLORS::MAGENTA, "float80  +=", x};
        },
        []() -> tuple<int, string, double> {
            long double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i;
            return {COLORS::MAGENTA, "float80  *=", x};
        },
        []() -> tuple<int, string, double> {
            long double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x /= i;
            return {COLORS::MAGENTA, "float80  /=", x};
        },
        []() -> tuple<int, string, double> {
            long double x = INIT_VALUE; 
            for(int i = 1; i <= COUNT_OF_ITERATIONS; i++)
                x *= i,
                x /= i;
            return {COLORS::MAGENTA, "float80 */=", x};
        },
    };
}