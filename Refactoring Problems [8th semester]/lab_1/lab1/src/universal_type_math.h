#ifndef __UNIVERSAL_TYPE_MATH_H__
#define __UNIVERSAL_TYPE_MATH_H__

UniversalType operator + (const UniversalType & lval, const UniversalType & rval){
    return UniversalType(lval.float_val + rval.float_val); 
}
UniversalType operator - (const UniversalType & lval, const UniversalType & rval){
    return UniversalType(lval.float_val - rval.float_val); 
}
UniversalType operator * (const UniversalType & lval, const UniversalType & rval){
    return UniversalType(lval.float_val * rval.float_val); 
}
UniversalType operator / (const UniversalType & lval, const UniversalType & rval){
    return UniversalType(lval.float_val / rval.float_val); 
}
UniversalType operator - (const UniversalType & lval){
    return UniversalType(-lval.float_val);
}
UniversalType UniversalType::pow(const UniversalType & rval) const{
    return std::pow(this->float_val, rval.float_val);
}

#endif