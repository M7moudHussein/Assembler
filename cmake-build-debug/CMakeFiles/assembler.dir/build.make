# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.1.1\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.1.1\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/assembler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/assembler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/assembler.dir/flags.make

CMakeFiles/assembler.dir/src/Assembler.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/Assembler.cpp.obj: ../src/Assembler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/assembler.dir/src/Assembler.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\Assembler.cpp.obj -c "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Assembler.cpp"

CMakeFiles/assembler.dir/src/Assembler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/Assembler.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Assembler.cpp" > CMakeFiles\assembler.dir\src\Assembler.cpp.i

CMakeFiles/assembler.dir/src/Assembler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/Assembler.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Assembler.cpp" -o CMakeFiles\assembler.dir\src\Assembler.cpp.s

CMakeFiles/assembler.dir/src/Assembler.cpp.obj.requires:

.PHONY : CMakeFiles/assembler.dir/src/Assembler.cpp.obj.requires

CMakeFiles/assembler.dir/src/Assembler.cpp.obj.provides: CMakeFiles/assembler.dir/src/Assembler.cpp.obj.requires
	$(MAKE) -f CMakeFiles\assembler.dir\build.make CMakeFiles/assembler.dir/src/Assembler.cpp.obj.provides.build
.PHONY : CMakeFiles/assembler.dir/src/Assembler.cpp.obj.provides

CMakeFiles/assembler.dir/src/Assembler.cpp.obj.provides.build: CMakeFiles/assembler.dir/src/Assembler.cpp.obj


CMakeFiles/assembler.dir/src/Line.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/Line.cpp.obj: ../src/Line.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/assembler.dir/src/Line.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\Line.cpp.obj -c "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Line.cpp"

CMakeFiles/assembler.dir/src/Line.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/Line.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Line.cpp" > CMakeFiles\assembler.dir\src\Line.cpp.i

CMakeFiles/assembler.dir/src/Line.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/Line.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Line.cpp" -o CMakeFiles\assembler.dir\src\Line.cpp.s

CMakeFiles/assembler.dir/src/Line.cpp.obj.requires:

.PHONY : CMakeFiles/assembler.dir/src/Line.cpp.obj.requires

CMakeFiles/assembler.dir/src/Line.cpp.obj.provides: CMakeFiles/assembler.dir/src/Line.cpp.obj.requires
	$(MAKE) -f CMakeFiles\assembler.dir\build.make CMakeFiles/assembler.dir/src/Line.cpp.obj.provides.build
.PHONY : CMakeFiles/assembler.dir/src/Line.cpp.obj.provides

CMakeFiles/assembler.dir/src/Line.cpp.obj.provides.build: CMakeFiles/assembler.dir/src/Line.cpp.obj


CMakeFiles/assembler.dir/src/Machine.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/Machine.cpp.obj: ../src/Machine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/assembler.dir/src/Machine.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\Machine.cpp.obj -c "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Machine.cpp"

CMakeFiles/assembler.dir/src/Machine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/Machine.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Machine.cpp" > CMakeFiles\assembler.dir\src\Machine.cpp.i

CMakeFiles/assembler.dir/src/Machine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/Machine.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Machine.cpp" -o CMakeFiles\assembler.dir\src\Machine.cpp.s

CMakeFiles/assembler.dir/src/Machine.cpp.obj.requires:

.PHONY : CMakeFiles/assembler.dir/src/Machine.cpp.obj.requires

CMakeFiles/assembler.dir/src/Machine.cpp.obj.provides: CMakeFiles/assembler.dir/src/Machine.cpp.obj.requires
	$(MAKE) -f CMakeFiles\assembler.dir\build.make CMakeFiles/assembler.dir/src/Machine.cpp.obj.provides.build
.PHONY : CMakeFiles/assembler.dir/src/Machine.cpp.obj.provides

CMakeFiles/assembler.dir/src/Machine.cpp.obj.provides.build: CMakeFiles/assembler.dir/src/Machine.cpp.obj


CMakeFiles/assembler.dir/src/OperationTable.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/OperationTable.cpp.obj: ../src/OperationTable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/assembler.dir/src/OperationTable.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\OperationTable.cpp.obj -c "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\OperationTable.cpp"

CMakeFiles/assembler.dir/src/OperationTable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/OperationTable.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\OperationTable.cpp" > CMakeFiles\assembler.dir\src\OperationTable.cpp.i

CMakeFiles/assembler.dir/src/OperationTable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/OperationTable.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\OperationTable.cpp" -o CMakeFiles\assembler.dir\src\OperationTable.cpp.s

CMakeFiles/assembler.dir/src/OperationTable.cpp.obj.requires:

.PHONY : CMakeFiles/assembler.dir/src/OperationTable.cpp.obj.requires

CMakeFiles/assembler.dir/src/OperationTable.cpp.obj.provides: CMakeFiles/assembler.dir/src/OperationTable.cpp.obj.requires
	$(MAKE) -f CMakeFiles\assembler.dir\build.make CMakeFiles/assembler.dir/src/OperationTable.cpp.obj.provides.build
.PHONY : CMakeFiles/assembler.dir/src/OperationTable.cpp.obj.provides

CMakeFiles/assembler.dir/src/OperationTable.cpp.obj.provides.build: CMakeFiles/assembler.dir/src/OperationTable.cpp.obj


CMakeFiles/assembler.dir/src/OpInfo.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/OpInfo.cpp.obj: ../src/OpInfo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/assembler.dir/src/OpInfo.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\OpInfo.cpp.obj -c "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\OpInfo.cpp"

CMakeFiles/assembler.dir/src/OpInfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/OpInfo.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\OpInfo.cpp" > CMakeFiles\assembler.dir\src\OpInfo.cpp.i

CMakeFiles/assembler.dir/src/OpInfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/OpInfo.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\OpInfo.cpp" -o CMakeFiles\assembler.dir\src\OpInfo.cpp.s

CMakeFiles/assembler.dir/src/OpInfo.cpp.obj.requires:

.PHONY : CMakeFiles/assembler.dir/src/OpInfo.cpp.obj.requires

CMakeFiles/assembler.dir/src/OpInfo.cpp.obj.provides: CMakeFiles/assembler.dir/src/OpInfo.cpp.obj.requires
	$(MAKE) -f CMakeFiles\assembler.dir\build.make CMakeFiles/assembler.dir/src/OpInfo.cpp.obj.provides.build
.PHONY : CMakeFiles/assembler.dir/src/OpInfo.cpp.obj.provides

CMakeFiles/assembler.dir/src/OpInfo.cpp.obj.provides.build: CMakeFiles/assembler.dir/src/OpInfo.cpp.obj


CMakeFiles/assembler.dir/src/SymbolTable.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/SymbolTable.cpp.obj: ../src/SymbolTable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/assembler.dir/src/SymbolTable.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\SymbolTable.cpp.obj -c "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\SymbolTable.cpp"

CMakeFiles/assembler.dir/src/SymbolTable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/SymbolTable.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\SymbolTable.cpp" > CMakeFiles\assembler.dir\src\SymbolTable.cpp.i

CMakeFiles/assembler.dir/src/SymbolTable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/SymbolTable.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\SymbolTable.cpp" -o CMakeFiles\assembler.dir\src\SymbolTable.cpp.s

CMakeFiles/assembler.dir/src/SymbolTable.cpp.obj.requires:

.PHONY : CMakeFiles/assembler.dir/src/SymbolTable.cpp.obj.requires

CMakeFiles/assembler.dir/src/SymbolTable.cpp.obj.provides: CMakeFiles/assembler.dir/src/SymbolTable.cpp.obj.requires
	$(MAKE) -f CMakeFiles\assembler.dir\build.make CMakeFiles/assembler.dir/src/SymbolTable.cpp.obj.provides.build
.PHONY : CMakeFiles/assembler.dir/src/SymbolTable.cpp.obj.provides

CMakeFiles/assembler.dir/src/SymbolTable.cpp.obj.provides.build: CMakeFiles/assembler.dir/src/SymbolTable.cpp.obj


CMakeFiles/assembler.dir/src/TextRecord.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/TextRecord.cpp.obj: ../src/TextRecord.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/assembler.dir/src/TextRecord.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\TextRecord.cpp.obj -c "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\TextRecord.cpp"

CMakeFiles/assembler.dir/src/TextRecord.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/TextRecord.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\TextRecord.cpp" > CMakeFiles\assembler.dir\src\TextRecord.cpp.i

CMakeFiles/assembler.dir/src/TextRecord.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/TextRecord.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\TextRecord.cpp" -o CMakeFiles\assembler.dir\src\TextRecord.cpp.s

CMakeFiles/assembler.dir/src/TextRecord.cpp.obj.requires:

.PHONY : CMakeFiles/assembler.dir/src/TextRecord.cpp.obj.requires

CMakeFiles/assembler.dir/src/TextRecord.cpp.obj.provides: CMakeFiles/assembler.dir/src/TextRecord.cpp.obj.requires
	$(MAKE) -f CMakeFiles\assembler.dir\build.make CMakeFiles/assembler.dir/src/TextRecord.cpp.obj.provides.build
.PHONY : CMakeFiles/assembler.dir/src/TextRecord.cpp.obj.provides

CMakeFiles/assembler.dir/src/TextRecord.cpp.obj.provides.build: CMakeFiles/assembler.dir/src/TextRecord.cpp.obj


CMakeFiles/assembler.dir/src/Util.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/Util.cpp.obj: ../src/Util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/assembler.dir/src/Util.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\Util.cpp.obj -c "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Util.cpp"

CMakeFiles/assembler.dir/src/Util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/Util.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Util.cpp" > CMakeFiles\assembler.dir\src\Util.cpp.i

CMakeFiles/assembler.dir/src/Util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/Util.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Util.cpp" -o CMakeFiles\assembler.dir\src\Util.cpp.s

CMakeFiles/assembler.dir/src/Util.cpp.obj.requires:

.PHONY : CMakeFiles/assembler.dir/src/Util.cpp.obj.requires

CMakeFiles/assembler.dir/src/Util.cpp.obj.provides: CMakeFiles/assembler.dir/src/Util.cpp.obj.requires
	$(MAKE) -f CMakeFiles\assembler.dir\build.make CMakeFiles/assembler.dir/src/Util.cpp.obj.provides.build
.PHONY : CMakeFiles/assembler.dir/src/Util.cpp.obj.provides

CMakeFiles/assembler.dir/src/Util.cpp.obj.provides.build: CMakeFiles/assembler.dir/src/Util.cpp.obj


CMakeFiles/assembler.dir/src/Pass1.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/Pass1.cpp.obj: ../src/Pass1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/assembler.dir/src/Pass1.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\Pass1.cpp.obj -c "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Pass1.cpp"

CMakeFiles/assembler.dir/src/Pass1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/Pass1.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Pass1.cpp" > CMakeFiles\assembler.dir\src\Pass1.cpp.i

CMakeFiles/assembler.dir/src/Pass1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/Pass1.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Pass1.cpp" -o CMakeFiles\assembler.dir\src\Pass1.cpp.s

CMakeFiles/assembler.dir/src/Pass1.cpp.obj.requires:

.PHONY : CMakeFiles/assembler.dir/src/Pass1.cpp.obj.requires

CMakeFiles/assembler.dir/src/Pass1.cpp.obj.provides: CMakeFiles/assembler.dir/src/Pass1.cpp.obj.requires
	$(MAKE) -f CMakeFiles\assembler.dir\build.make CMakeFiles/assembler.dir/src/Pass1.cpp.obj.provides.build
.PHONY : CMakeFiles/assembler.dir/src/Pass1.cpp.obj.provides

CMakeFiles/assembler.dir/src/Pass1.cpp.obj.provides.build: CMakeFiles/assembler.dir/src/Pass1.cpp.obj


CMakeFiles/assembler.dir/src/Pass2.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/Pass2.cpp.obj: ../src/Pass2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/assembler.dir/src/Pass2.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\Pass2.cpp.obj -c "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Pass2.cpp"

CMakeFiles/assembler.dir/src/Pass2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/Pass2.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Pass2.cpp" > CMakeFiles\assembler.dir\src\Pass2.cpp.i

CMakeFiles/assembler.dir/src/Pass2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/Pass2.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\Pass2.cpp" -o CMakeFiles\assembler.dir\src\Pass2.cpp.s

CMakeFiles/assembler.dir/src/Pass2.cpp.obj.requires:

.PHONY : CMakeFiles/assembler.dir/src/Pass2.cpp.obj.requires

CMakeFiles/assembler.dir/src/Pass2.cpp.obj.provides: CMakeFiles/assembler.dir/src/Pass2.cpp.obj.requires
	$(MAKE) -f CMakeFiles\assembler.dir\build.make CMakeFiles/assembler.dir/src/Pass2.cpp.obj.provides.build
.PHONY : CMakeFiles/assembler.dir/src/Pass2.cpp.obj.provides

CMakeFiles/assembler.dir/src/Pass2.cpp.obj.provides.build: CMakeFiles/assembler.dir/src/Pass2.cpp.obj


CMakeFiles/assembler.dir/src/LineGS.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/LineGS.cpp.obj: ../src/LineGS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/assembler.dir/src/LineGS.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\LineGS.cpp.obj -c "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\LineGS.cpp"

CMakeFiles/assembler.dir/src/LineGS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/LineGS.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\LineGS.cpp" > CMakeFiles\assembler.dir\src\LineGS.cpp.i

CMakeFiles/assembler.dir/src/LineGS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/LineGS.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\LineGS.cpp" -o CMakeFiles\assembler.dir\src\LineGS.cpp.s

CMakeFiles/assembler.dir/src/LineGS.cpp.obj.requires:

.PHONY : CMakeFiles/assembler.dir/src/LineGS.cpp.obj.requires

CMakeFiles/assembler.dir/src/LineGS.cpp.obj.provides: CMakeFiles/assembler.dir/src/LineGS.cpp.obj.requires
	$(MAKE) -f CMakeFiles\assembler.dir\build.make CMakeFiles/assembler.dir/src/LineGS.cpp.obj.provides.build
.PHONY : CMakeFiles/assembler.dir/src/LineGS.cpp.obj.provides

CMakeFiles/assembler.dir/src/LineGS.cpp.obj.provides.build: CMakeFiles/assembler.dir/src/LineGS.cpp.obj


CMakeFiles/assembler.dir/src/LiteralTable.cpp.obj: CMakeFiles/assembler.dir/flags.make
CMakeFiles/assembler.dir/src/LiteralTable.cpp.obj: ../src/LiteralTable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/assembler.dir/src/LiteralTable.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\assembler.dir\src\LiteralTable.cpp.obj -c "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\LiteralTable.cpp"

CMakeFiles/assembler.dir/src/LiteralTable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assembler.dir/src/LiteralTable.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\LiteralTable.cpp" > CMakeFiles\assembler.dir\src\LiteralTable.cpp.i

CMakeFiles/assembler.dir/src/LiteralTable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assembler.dir/src/LiteralTable.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\src\LiteralTable.cpp" -o CMakeFiles\assembler.dir\src\LiteralTable.cpp.s

CMakeFiles/assembler.dir/src/LiteralTable.cpp.obj.requires:

.PHONY : CMakeFiles/assembler.dir/src/LiteralTable.cpp.obj.requires

CMakeFiles/assembler.dir/src/LiteralTable.cpp.obj.provides: CMakeFiles/assembler.dir/src/LiteralTable.cpp.obj.requires
	$(MAKE) -f CMakeFiles\assembler.dir\build.make CMakeFiles/assembler.dir/src/LiteralTable.cpp.obj.provides.build
.PHONY : CMakeFiles/assembler.dir/src/LiteralTable.cpp.obj.provides

CMakeFiles/assembler.dir/src/LiteralTable.cpp.obj.provides.build: CMakeFiles/assembler.dir/src/LiteralTable.cpp.obj


# Object files for target assembler
assembler_OBJECTS = \
"CMakeFiles/assembler.dir/src/Assembler.cpp.obj" \
"CMakeFiles/assembler.dir/src/Line.cpp.obj" \
"CMakeFiles/assembler.dir/src/Machine.cpp.obj" \
"CMakeFiles/assembler.dir/src/OperationTable.cpp.obj" \
"CMakeFiles/assembler.dir/src/OpInfo.cpp.obj" \
"CMakeFiles/assembler.dir/src/SymbolTable.cpp.obj" \
"CMakeFiles/assembler.dir/src/TextRecord.cpp.obj" \
"CMakeFiles/assembler.dir/src/Util.cpp.obj" \
"CMakeFiles/assembler.dir/src/Pass1.cpp.obj" \
"CMakeFiles/assembler.dir/src/Pass2.cpp.obj" \
"CMakeFiles/assembler.dir/src/LineGS.cpp.obj" \
"CMakeFiles/assembler.dir/src/LiteralTable.cpp.obj"

# External object files for target assembler
assembler_EXTERNAL_OBJECTS =

assembler.exe: CMakeFiles/assembler.dir/src/Assembler.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/src/Line.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/src/Machine.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/src/OperationTable.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/src/OpInfo.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/src/SymbolTable.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/src/TextRecord.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/src/Util.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/src/Pass1.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/src/Pass2.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/src/LineGS.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/src/LiteralTable.cpp.obj
assembler.exe: CMakeFiles/assembler.dir/build.make
assembler.exe: CMakeFiles/assembler.dir/linklibs.rsp
assembler.exe: CMakeFiles/assembler.dir/objects1.rsp
assembler.exe: CMakeFiles/assembler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable assembler.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\assembler.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/assembler.dir/build: assembler.exe

.PHONY : CMakeFiles/assembler.dir/build

CMakeFiles/assembler.dir/requires: CMakeFiles/assembler.dir/src/Assembler.cpp.obj.requires
CMakeFiles/assembler.dir/requires: CMakeFiles/assembler.dir/src/Line.cpp.obj.requires
CMakeFiles/assembler.dir/requires: CMakeFiles/assembler.dir/src/Machine.cpp.obj.requires
CMakeFiles/assembler.dir/requires: CMakeFiles/assembler.dir/src/OperationTable.cpp.obj.requires
CMakeFiles/assembler.dir/requires: CMakeFiles/assembler.dir/src/OpInfo.cpp.obj.requires
CMakeFiles/assembler.dir/requires: CMakeFiles/assembler.dir/src/SymbolTable.cpp.obj.requires
CMakeFiles/assembler.dir/requires: CMakeFiles/assembler.dir/src/TextRecord.cpp.obj.requires
CMakeFiles/assembler.dir/requires: CMakeFiles/assembler.dir/src/Util.cpp.obj.requires
CMakeFiles/assembler.dir/requires: CMakeFiles/assembler.dir/src/Pass1.cpp.obj.requires
CMakeFiles/assembler.dir/requires: CMakeFiles/assembler.dir/src/Pass2.cpp.obj.requires
CMakeFiles/assembler.dir/requires: CMakeFiles/assembler.dir/src/LineGS.cpp.obj.requires
CMakeFiles/assembler.dir/requires: CMakeFiles/assembler.dir/src/LiteralTable.cpp.obj.requires

.PHONY : CMakeFiles/assembler.dir/requires

CMakeFiles/assembler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\assembler.dir\cmake_clean.cmake
.PHONY : CMakeFiles/assembler.dir/clean

CMakeFiles/assembler.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler" "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler" "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug" "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug" "E:\Google Drive\Study\Second_Yead\Second_Semester\Systems Programming\assembler\cmake-build-debug\CMakeFiles\assembler.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/assembler.dir/depend

