cmake_minimum_required(VERSION 3.21)
project(huffman C)

set(CMAKE_C_STANDARD 11)

add_executable(huffman main.c processFile.c processFile.h)
