cmake_minimum_required(VERSION 3.7)
project(Assembler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Assembler.cpp
        src/Error.cpp
        src/Error.h
        src/Label.cpp
        src/Label.h
        src/Line.cpp
        src/Line.h
        src/ListingFile.cpp
        src/ListingFile.h
        src/Machine.cpp
        src/Machine.h
        src/main.cpp
        src/OperationTable.cpp
        src/OperationTable.h
        src/OpInfo.cpp
        src/OpInfo.h
        src/SymbolTable.cpp
        src/SymbolTable.h)

add_executable(Assembler ${SOURCE_FILES})