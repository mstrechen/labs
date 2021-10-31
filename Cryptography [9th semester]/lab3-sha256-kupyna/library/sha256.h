//
// Created by Matvii Strechen on 31/10/2021.
//

#ifndef CRYPTO_SHA256_H
#define CRYPTO_SHA256_H

#include "common.h"
#include <vector>
#include <bit>
#include <bitset>


namespace cryptography {

    const array<uint32_t, 8> SQUARE_ROOTS = {
            0x6A09E667,
            0xBB67AE85,
            0x3C6EF372,
            0xA54FF53A,
            0x510E527F,
            0x9B05688C,
            0x1F83D9AB,
            0x5BE0CD19,
    };
    const array<uint32_t, 64> CUBIC_ROOTS = {
            0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
            0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
            0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
            0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
            0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
            0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
            0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
            0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
    };


    Hash<32> sha256(const std::vector<uint8_t> & _bytes){
        uint32_t
            h0 = SQUARE_ROOTS[0],
            h1 = SQUARE_ROOTS[1],
            h2 = SQUARE_ROOTS[2],
            h3 = SQUARE_ROOTS[3],
            h4 = SQUARE_ROOTS[4],
            h5 = SQUARE_ROOTS[5],
            h6 = SQUARE_ROOTS[6],
            h7 = SQUARE_ROOTS[7];
        std::vector<uint8_t> bytes = _bytes;
        bytes.push_back(128);
        while(bytes.size() % 64 != 56){
            bytes.push_back(0);
        }
        uint64_t orig_size = _bytes.size() * 8;
        for(size_t i = 0; i < 8; i++){
            bytes.push_back(
                (orig_size >> ((7 - i) * 8)) & (uint8_t)(0xFF)
            );
        }
        for(size_t i = 0; i < bytes.size(); i += 64){
            array<uint32_t, 64> words{};
            for(size_t j = 0; j < 64; j++){
                words[j / 4] += (uint32_t(bytes[i + j]) << uint32_t((3 - (j % 4)) * 8));
            }

            for(size_t j = 16; j < 64; j++){
                uint32_t s0 = (
                        std::rotr(words[j - 15], 7) ^
                        std::rotr(words[j - 15], 18) ^
                        (words[j - 15] >> (uint32_t) 3)
                );
                uint32_t s1 = (
                        std::rotr(words[j - 2], 17) ^
                        std::rotr(words[j - 2], 19) ^
                        (words[j - 2] >> (uint32_t) 10)
                );
                words[j] = words[j - 16] + words[j - 7] + s0 + s1;
            }
            uint32_t
                a = h0,
                b = h1,
                c = h2,
                d = h3,
                e = h4,
                f = h5,
                g = h6,
                h = h7;
            for(size_t j = 0; j < 64; j++){
                uint32_t sum0 = (
                    (std::rotr(a, 2)) ^
                    (std::rotr(a, 13)) ^
                    (std::rotr(a, 22))
                );
                uint32_t ma = (
                        (a & b) ^
                        (a & c) ^
                        (b & c)
                );
                uint32_t sum1 = (
                        (std::rotr(e, 6)) ^
                        (std::rotr(e, 11)) ^
                        (std::rotr(e, 25))
                );
                uint32_t ch = (
                        (e & f) ^
                        ((~e) & g)
                );
                uint32_t t1 = h + sum1 + ch + CUBIC_ROOTS[j] + words[j];
                uint32_t t2 = sum0 + ma;

                h = g;
                g = f;
                f = e;
                e = d + t1;
                d = c;
                c = b;
                b = a;
                a = t1 + t2;
            }
            h0 += a;
            h1 += b;
            h2 += c;
            h3 += d;
            h4 += e;
            h5 += f;
            h6 += g;
            h7 += h;
        }
        array<uint32_t, 8> result_32{h0, h1, h2, h3, h4, h5, h6, h7};
        array<uint8_t, 32> result_8{};
        for(size_t i = 0; i < 32; i++){
            result_8[i] = ((result_32[i / 4] >> uint32_t( (3 - i%4) * 8)) & uint8_t (0xFF));
        }
        return Hash<32>(result_8);
    }
}


#endif //CRYPTO_SHA256_H
