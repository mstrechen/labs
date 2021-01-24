#ifndef __FUNCTION_EXECUTOR_H__
#define __FUNCTION_EXECUTOR_H__

#include "universal_type.h"
#include <map>
#include <functional>
#include <cmath>

using namespace std;



struct FunctionExecutor{
    static UniversalType execute_unary(const string & func_name, const UniversalType & operand){
        if(func_name == "abs")
            return abs(operand.float_val);
        throw "FAIL";
        return NAN;
    }
};

#endif