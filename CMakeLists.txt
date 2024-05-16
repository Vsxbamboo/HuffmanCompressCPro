cmake_minimum_required(VERSION 3.26)
project(HuffmanCompressCPro)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
add_executable(HuffmanCompressCPro main.cpp
        SqList.h
        Compress.cpp
        Compress.h
        Dictionary.cpp
        Dictionary.h
        Huffman.cpp
        Huffman.h
        CharCount.cpp
        CharCount.h
        HuffmanTree.cpp
        HuffmanTree.h
        EntryInFile.cpp
        EntryInFile.h
        CodeBuffer.cpp
        CodeBuffer.h
)
