#ifndef CPUINFO_H_
#define CPUINFO_H_

#include<string>

using namespace std;

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

string get_cpu_vendor(void);

string get_bit_capacity(void);

#endif