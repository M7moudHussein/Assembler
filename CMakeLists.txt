cmake_minimum_required(VERSION 3.7)
project(assembler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Assembler/src/Assembler.cpp
        Assembler/src/Error.cpp
        Assembler/src/Error.h
        Assembler/src/Label.cpp
        Assembler/src/Label.h
        Assembler/src/Line.cpp
        Assembler/src/Line.h
        Assembler/src/ListingFile.cpp
        Assembler/src/ListingFile.h
        Assembler/src/Machine.cpp
        Assembler/src/Machine.h
        Assembler/src/OperationTable.cpp
        Assembler/src/OperationTable.h
        Assembler/src/OpInfo.cpp
        Assembler/src/OpInfo.h
        Assembler/src/SymbolTable.cpp
        Assembler/src/SymbolTable.h
        Assembler/CMakeLists.txt Assembler/src/TextRecord.cpp Assembler/src/TextRecord.h)

add_executable(assembler ${SOURCE_FILES})