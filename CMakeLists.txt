cmake_minimum_required(VERSION 3.7)
project(assembler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Assembler.cpp
        src/Line.cpp
        src/Line.h
        src/Machine.cpp
        src/Machine.h
        src/OperationTable.cpp
        src/OperationTable.h
        src/OpInfo.cpp
        src/OpInfo.h
        src/SymbolTable.cpp
        src/SymbolTable.h
        src/TextRecord.cpp
        src/TextRecord.h src/Util.cpp src/Util.hpp src/Util.hpp src/Pass1.cpp src/Pass1.hpp src/Pass2.cpp src/Pass2.hpp src/LineGS.cpp)

add_executable(assembler ${SOURCE_FILES})