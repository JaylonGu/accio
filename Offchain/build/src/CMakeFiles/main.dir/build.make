# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jaylon/Workspaces/Blockchain/Accio/Offchain

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build

# Include any dependencies generated for this target.
include src/CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/main.dir/flags.make

src/CMakeFiles/main.dir/main.c.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/main.c.o: /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/main.c
src/CMakeFiles/main.dir/main.c.o: src/CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/main.dir/main.c.o"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/main.dir/main.c.o -MF CMakeFiles/main.dir/main.c.o.d -o CMakeFiles/main.dir/main.c.o -c /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/main.c

src/CMakeFiles/main.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/main.c.i"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/main.c > CMakeFiles/main.dir/main.c.i

src/CMakeFiles/main.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/main.c.s"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/main.c -o CMakeFiles/main.dir/main.c.s

src/CMakeFiles/main.dir/util.c.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/util.c.o: /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/util.c
src/CMakeFiles/main.dir/util.c.o: src/CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/main.dir/util.c.o"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/main.dir/util.c.o -MF CMakeFiles/main.dir/util.c.o.d -o CMakeFiles/main.dir/util.c.o -c /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/util.c

src/CMakeFiles/main.dir/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/util.c.i"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/util.c > CMakeFiles/main.dir/util.c.i

src/CMakeFiles/main.dir/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/util.c.s"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/util.c -o CMakeFiles/main.dir/util.c.s

src/CMakeFiles/main.dir/payee.c.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/payee.c.o: /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/payee.c
src/CMakeFiles/main.dir/payee.c.o: src/CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CMakeFiles/main.dir/payee.c.o"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/main.dir/payee.c.o -MF CMakeFiles/main.dir/payee.c.o.d -o CMakeFiles/main.dir/payee.c.o -c /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/payee.c

src/CMakeFiles/main.dir/payee.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/payee.c.i"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/payee.c > CMakeFiles/main.dir/payee.c.i

src/CMakeFiles/main.dir/payee.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/payee.c.s"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/payee.c -o CMakeFiles/main.dir/payee.c.s

src/CMakeFiles/main.dir/tumbler.c.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/tumbler.c.o: /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/tumbler.c
src/CMakeFiles/main.dir/tumbler.c.o: src/CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/CMakeFiles/main.dir/tumbler.c.o"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/main.dir/tumbler.c.o -MF CMakeFiles/main.dir/tumbler.c.o.d -o CMakeFiles/main.dir/tumbler.c.o -c /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/tumbler.c

src/CMakeFiles/main.dir/tumbler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/tumbler.c.i"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/tumbler.c > CMakeFiles/main.dir/tumbler.c.i

src/CMakeFiles/main.dir/tumbler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/tumbler.c.s"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/tumbler.c -o CMakeFiles/main.dir/tumbler.c.s

src/CMakeFiles/main.dir/payer.c.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/payer.c.o: /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/payer.c
src/CMakeFiles/main.dir/payer.c.o: src/CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/CMakeFiles/main.dir/payer.c.o"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/main.dir/payer.c.o -MF CMakeFiles/main.dir/payer.c.o.d -o CMakeFiles/main.dir/payer.c.o -c /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/payer.c

src/CMakeFiles/main.dir/payer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/payer.c.i"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/payer.c > CMakeFiles/main.dir/payer.c.i

src/CMakeFiles/main.dir/payer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/payer.c.s"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src/payer.c -o CMakeFiles/main.dir/payer.c.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.c.o" \
"CMakeFiles/main.dir/util.c.o" \
"CMakeFiles/main.dir/payee.c.o" \
"CMakeFiles/main.dir/tumbler.c.o" \
"CMakeFiles/main.dir/payer.c.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

/home/jaylon/Workspaces/Blockchain/Accio/Offchain/bin/main: src/CMakeFiles/main.dir/main.c.o
/home/jaylon/Workspaces/Blockchain/Accio/Offchain/bin/main: src/CMakeFiles/main.dir/util.c.o
/home/jaylon/Workspaces/Blockchain/Accio/Offchain/bin/main: src/CMakeFiles/main.dir/payee.c.o
/home/jaylon/Workspaces/Blockchain/Accio/Offchain/bin/main: src/CMakeFiles/main.dir/tumbler.c.o
/home/jaylon/Workspaces/Blockchain/Accio/Offchain/bin/main: src/CMakeFiles/main.dir/payer.c.o
/home/jaylon/Workspaces/Blockchain/Accio/Offchain/bin/main: src/CMakeFiles/main.dir/build.make
/home/jaylon/Workspaces/Blockchain/Accio/Offchain/bin/main: /usr/local/lib/libtomcrypt.so
/home/jaylon/Workspaces/Blockchain/Accio/Offchain/bin/main: /usr/local/lib/libmclbn256.so
/home/jaylon/Workspaces/Blockchain/Accio/Offchain/bin/main: /usr/local/lib/libsecp256k1.so
/home/jaylon/Workspaces/Blockchain/Accio/Offchain/bin/main: src/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable /home/jaylon/Workspaces/Blockchain/Accio/Offchain/bin/main"
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/main.dir/build: /home/jaylon/Workspaces/Blockchain/Accio/Offchain/bin/main
.PHONY : src/CMakeFiles/main.dir/build

src/CMakeFiles/main.dir/clean:
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src && $(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/main.dir/clean

src/CMakeFiles/main.dir/depend:
	cd /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jaylon/Workspaces/Blockchain/Accio/Offchain /home/jaylon/Workspaces/Blockchain/Accio/Offchain/src /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src /home/jaylon/Workspaces/Blockchain/Accio/Offchain/build/src/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/main.dir/depend

