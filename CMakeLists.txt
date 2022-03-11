cmake_minimum_required(VERSION 3.21)
project(huffman C)

set(CMAKE_C_STANDARD 11)

add_executable(huffman src/source/main.c src/source/processFile.c src/headers/processFile.h src/source/list.c src/headers/list.h src/source/encoding.c src/headers/encoding.h src/source/decoding.c src/headers/decoding.h)
