cmake_minimum_required(VERSION 3.16)
project(crypto)

set(CMAKE_CXX_STANDARD 20)

add_executable(crypto main.cpp library/sha256.h library/common.h)