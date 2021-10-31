#include <iostream>
#include "library/sha256.h"
#include "library/common.h"
#include <cmath>

using cryptography::Hash;

int main() {
    cryptography::Hash<8>h("abc");
    std::cout << h.hexdigest() << std::endl;

    std::string example = "The quick brown fox jumps over the lazy dog";
    std::vector<uint8_t> bytes(example.begin(), example.end());

    std::cout << cryptography::sha256(bytes).hexdigest();
    return 0;
}
