#ifndef __UNIVERSAL_TYPE_H__
#define __UNIVERSAL_TYPE_H__

#include <cmath>
#include <string>
using namespace std;

using FLOAT_TYPE = double;

struct UniversalType{
    FLOAT_TYPE float_val;
    string str_val;
    UniversalType(): float_val(NAN), str_val("NaS"){}
    UniversalType(double float_val) : float_val(float_val), str_val("NaN") {}
    UniversalType(const string & str_val) : float_val(NAN), str_val(str_val) {}
    UniversalType pow(const UniversalType &) const;
};


#endif