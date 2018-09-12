#include "cpuinfo.h"

string get_cpu_vendor(void){
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

string get_bit_capacity(){
  return to_string(sizeof(void *) * 8);
}
