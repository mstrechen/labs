//
// Created by Matvii Strechen on 31/10/2021.
//

#ifndef CRYPTO_COMMON_H
#define CRYPTO_COMMON_H

#include <cstddef>
#include <array>
#include <string>
#include <algorithm>
#include <string_view>
#include <cassert>
#include <map>


namespace cryptography {
    const auto ALPHABET = "0123456789ABCDEF";
    const std::map<char, uint8_t> REVERSE_ALPHABET = {
            {'0', 0},
            {'1', 1},
            {'2', 2},
            {'3', 3},
            {'4', 4},
            {'5', 5},
            {'6', 6},
            {'7', 7},
            {'8', 8},
            {'9', 9},
            {'A', 10},
            {'B', 11},
            {'C', 12},
            {'D', 13},
            {'E', 14},
            {'F', 15},
            {'a', 10},
            {'b', 11},
            {'c', 12},
            {'d', 13},
            {'e', 14},
            {'f', 15},
    };

    using std::array;

    template<size_t size>
    class Hash {
    public:
        array<uint8_t, size> bytes;
        Hash(const Hash &) = default;
        Hash(Hash &&) noexcept = default;
        explicit Hash(const array<uint8_t, size> & bytes) : bytes(bytes) {}
        explicit Hash(const std::string_view & hexdigest){
            assert(hexdigest.size() <= size * 2 && "hexdigest length should not be more than expected size");
            bytes.fill(0);
            for(size_t i = 0; i < hexdigest.size(); i++){
                assert(REVERSE_ALPHABET.count(hexdigest[i]) && "Unrecognized character in hexdigest");
                if ((hexdigest.size() - i - 1) % 2 == 0){
                    bytes[(hexdigest.size() - i - 1) / 2] += REVERSE_ALPHABET.at(hexdigest[i]);
                } else {
                    bytes[(hexdigest.size() - i - 1) / 2] += REVERSE_ALPHABET.at(hexdigest[i]) * 16;
                }
            }
            std::reverse(bytes.begin(), bytes.end());
        }

        std::string hexdigest() {
            std::string res;
            res.reserve(size * 2);
            for(auto byte : bytes){
                res.push_back(ALPHABET[byte / 16]);
                res.push_back(ALPHABET[byte % 16]);
            }
            return res;
        }

        bool operator == (const Hash & other) const = default;
    };

}


#endif //CRYPTO_COMMON_H
