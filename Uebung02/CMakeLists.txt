cmake_minimum_required(VERSION 3.12)
project(Uebung02)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(01_Sequence)

add_executable(Uebung02
        01_Sequence/test/2Bit_test.cpp
        01_Sequence/test/DNA_test.cpp
        01_Sequence/test/Fasta_test.cpp
        01_Sequence/test/main_test.cpp
        01_Sequence/test/Peptide_test.cpp
        01_Sequence/test/RNA_test.cpp
        01_Sequence/test/Sequence_test.cpp
        01_Sequence/2Bit.cpp
        01_Sequence/2Bit.h
        01_Sequence/convert.cpp
        01_Sequence/DNA.cpp
        01_Sequence/DNA.h
        01_Sequence/Fasta.h
        01_Sequence/InvalidCharacter.cpp
        01_Sequence/InvalidCharacter.h
        01_Sequence/ParsingException.cpp
        01_Sequence/ParsingException.h
        01_Sequence/Peptide.cpp
        01_Sequence/Peptide.h
        01_Sequence/RNA.cpp
        01_Sequence/RNA.h
        01_Sequence/Sequence.h
        test/2Bit_test.cpp
        test/DNA_test.cpp
        test/Fasta_test.cpp
        test/Graph_test.cpp
        test/main_test.cpp
        test/Peptide_test.cpp
        test/RNA_test.cpp
        test/Sequence_test.cpp
        Assembler.cpp
        Assembler.h
        Graph.h)
