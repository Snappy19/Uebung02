cmake_minimum_required(VERSION 3.12)
project(Uebung02)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(test)

add_executable(Uebung02
        test/2Bit_test.cpp
        test/CMakeLists.txt
        test/DNA_test.cpp
        test/Fasta_test.cpp
        test/Graph_test.cpp
        test/main_test.cpp
        test/Peptide_test.cpp
        test/RNA_test.cpp
        test/Sequence_test.cpp
        .clang-format
        Assembler.cpp
        Assembler.h
        CMakeLists.txt
        Graph.h)
