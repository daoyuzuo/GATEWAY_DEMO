# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/build

# Include any dependencies generated for this target.
include CMakeFiles/GATEWAY_DEMO.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GATEWAY_DEMO.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GATEWAY_DEMO.dir/flags.make

CMakeFiles/GATEWAY_DEMO.dir/src/main.c.o: CMakeFiles/GATEWAY_DEMO.dir/flags.make
CMakeFiles/GATEWAY_DEMO.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/GATEWAY_DEMO.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/GATEWAY_DEMO.dir/src/main.c.o -c /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/main.c

CMakeFiles/GATEWAY_DEMO.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GATEWAY_DEMO.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/main.c > CMakeFiles/GATEWAY_DEMO.dir/src/main.c.i

CMakeFiles/GATEWAY_DEMO.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GATEWAY_DEMO.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/main.c -o CMakeFiles/GATEWAY_DEMO.dir/src/main.c.s

CMakeFiles/GATEWAY_DEMO.dir/src/raw_socket_ipv6.c.o: CMakeFiles/GATEWAY_DEMO.dir/flags.make
CMakeFiles/GATEWAY_DEMO.dir/src/raw_socket_ipv6.c.o: ../src/raw_socket_ipv6.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/GATEWAY_DEMO.dir/src/raw_socket_ipv6.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/GATEWAY_DEMO.dir/src/raw_socket_ipv6.c.o -c /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/raw_socket_ipv6.c

CMakeFiles/GATEWAY_DEMO.dir/src/raw_socket_ipv6.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GATEWAY_DEMO.dir/src/raw_socket_ipv6.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/raw_socket_ipv6.c > CMakeFiles/GATEWAY_DEMO.dir/src/raw_socket_ipv6.c.i

CMakeFiles/GATEWAY_DEMO.dir/src/raw_socket_ipv6.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GATEWAY_DEMO.dir/src/raw_socket_ipv6.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/raw_socket_ipv6.c -o CMakeFiles/GATEWAY_DEMO.dir/src/raw_socket_ipv6.c.s

CMakeFiles/GATEWAY_DEMO.dir/src/socket_can.c.o: CMakeFiles/GATEWAY_DEMO.dir/flags.make
CMakeFiles/GATEWAY_DEMO.dir/src/socket_can.c.o: ../src/socket_can.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/GATEWAY_DEMO.dir/src/socket_can.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/GATEWAY_DEMO.dir/src/socket_can.c.o -c /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/socket_can.c

CMakeFiles/GATEWAY_DEMO.dir/src/socket_can.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GATEWAY_DEMO.dir/src/socket_can.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/socket_can.c > CMakeFiles/GATEWAY_DEMO.dir/src/socket_can.c.i

CMakeFiles/GATEWAY_DEMO.dir/src/socket_can.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GATEWAY_DEMO.dir/src/socket_can.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/socket_can.c -o CMakeFiles/GATEWAY_DEMO.dir/src/socket_can.c.s

CMakeFiles/GATEWAY_DEMO.dir/src/protocol_convert.c.o: CMakeFiles/GATEWAY_DEMO.dir/flags.make
CMakeFiles/GATEWAY_DEMO.dir/src/protocol_convert.c.o: ../src/protocol_convert.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/GATEWAY_DEMO.dir/src/protocol_convert.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/GATEWAY_DEMO.dir/src/protocol_convert.c.o -c /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/protocol_convert.c

CMakeFiles/GATEWAY_DEMO.dir/src/protocol_convert.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GATEWAY_DEMO.dir/src/protocol_convert.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/protocol_convert.c > CMakeFiles/GATEWAY_DEMO.dir/src/protocol_convert.c.i

CMakeFiles/GATEWAY_DEMO.dir/src/protocol_convert.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GATEWAY_DEMO.dir/src/protocol_convert.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/protocol_convert.c -o CMakeFiles/GATEWAY_DEMO.dir/src/protocol_convert.c.s

CMakeFiles/GATEWAY_DEMO.dir/src/protocol_translate.c.o: CMakeFiles/GATEWAY_DEMO.dir/flags.make
CMakeFiles/GATEWAY_DEMO.dir/src/protocol_translate.c.o: ../src/protocol_translate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/GATEWAY_DEMO.dir/src/protocol_translate.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/GATEWAY_DEMO.dir/src/protocol_translate.c.o -c /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/protocol_translate.c

CMakeFiles/GATEWAY_DEMO.dir/src/protocol_translate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GATEWAY_DEMO.dir/src/protocol_translate.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/protocol_translate.c > CMakeFiles/GATEWAY_DEMO.dir/src/protocol_translate.c.i

CMakeFiles/GATEWAY_DEMO.dir/src/protocol_translate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GATEWAY_DEMO.dir/src/protocol_translate.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/protocol_translate.c -o CMakeFiles/GATEWAY_DEMO.dir/src/protocol_translate.c.s

CMakeFiles/GATEWAY_DEMO.dir/src/priority.c.o: CMakeFiles/GATEWAY_DEMO.dir/flags.make
CMakeFiles/GATEWAY_DEMO.dir/src/priority.c.o: ../src/priority.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/GATEWAY_DEMO.dir/src/priority.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/GATEWAY_DEMO.dir/src/priority.c.o -c /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/priority.c

CMakeFiles/GATEWAY_DEMO.dir/src/priority.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GATEWAY_DEMO.dir/src/priority.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/priority.c > CMakeFiles/GATEWAY_DEMO.dir/src/priority.c.i

CMakeFiles/GATEWAY_DEMO.dir/src/priority.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GATEWAY_DEMO.dir/src/priority.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/priority.c -o CMakeFiles/GATEWAY_DEMO.dir/src/priority.c.s

CMakeFiles/GATEWAY_DEMO.dir/src/redundancy_transmit.c.o: CMakeFiles/GATEWAY_DEMO.dir/flags.make
CMakeFiles/GATEWAY_DEMO.dir/src/redundancy_transmit.c.o: ../src/redundancy_transmit.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/GATEWAY_DEMO.dir/src/redundancy_transmit.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/GATEWAY_DEMO.dir/src/redundancy_transmit.c.o -c /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/redundancy_transmit.c

CMakeFiles/GATEWAY_DEMO.dir/src/redundancy_transmit.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GATEWAY_DEMO.dir/src/redundancy_transmit.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/redundancy_transmit.c > CMakeFiles/GATEWAY_DEMO.dir/src/redundancy_transmit.c.i

CMakeFiles/GATEWAY_DEMO.dir/src/redundancy_transmit.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GATEWAY_DEMO.dir/src/redundancy_transmit.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/redundancy_transmit.c -o CMakeFiles/GATEWAY_DEMO.dir/src/redundancy_transmit.c.s

CMakeFiles/GATEWAY_DEMO.dir/src/C_queue.c.o: CMakeFiles/GATEWAY_DEMO.dir/flags.make
CMakeFiles/GATEWAY_DEMO.dir/src/C_queue.c.o: ../src/C_queue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/GATEWAY_DEMO.dir/src/C_queue.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/GATEWAY_DEMO.dir/src/C_queue.c.o -c /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/C_queue.c

CMakeFiles/GATEWAY_DEMO.dir/src/C_queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GATEWAY_DEMO.dir/src/C_queue.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/C_queue.c > CMakeFiles/GATEWAY_DEMO.dir/src/C_queue.c.i

CMakeFiles/GATEWAY_DEMO.dir/src/C_queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GATEWAY_DEMO.dir/src/C_queue.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/src/C_queue.c -o CMakeFiles/GATEWAY_DEMO.dir/src/C_queue.c.s

# Object files for target GATEWAY_DEMO
GATEWAY_DEMO_OBJECTS = \
"CMakeFiles/GATEWAY_DEMO.dir/src/main.c.o" \
"CMakeFiles/GATEWAY_DEMO.dir/src/raw_socket_ipv6.c.o" \
"CMakeFiles/GATEWAY_DEMO.dir/src/socket_can.c.o" \
"CMakeFiles/GATEWAY_DEMO.dir/src/protocol_convert.c.o" \
"CMakeFiles/GATEWAY_DEMO.dir/src/protocol_translate.c.o" \
"CMakeFiles/GATEWAY_DEMO.dir/src/priority.c.o" \
"CMakeFiles/GATEWAY_DEMO.dir/src/redundancy_transmit.c.o" \
"CMakeFiles/GATEWAY_DEMO.dir/src/C_queue.c.o"

# External object files for target GATEWAY_DEMO
GATEWAY_DEMO_EXTERNAL_OBJECTS =

GATEWAY_DEMO: CMakeFiles/GATEWAY_DEMO.dir/src/main.c.o
GATEWAY_DEMO: CMakeFiles/GATEWAY_DEMO.dir/src/raw_socket_ipv6.c.o
GATEWAY_DEMO: CMakeFiles/GATEWAY_DEMO.dir/src/socket_can.c.o
GATEWAY_DEMO: CMakeFiles/GATEWAY_DEMO.dir/src/protocol_convert.c.o
GATEWAY_DEMO: CMakeFiles/GATEWAY_DEMO.dir/src/protocol_translate.c.o
GATEWAY_DEMO: CMakeFiles/GATEWAY_DEMO.dir/src/priority.c.o
GATEWAY_DEMO: CMakeFiles/GATEWAY_DEMO.dir/src/redundancy_transmit.c.o
GATEWAY_DEMO: CMakeFiles/GATEWAY_DEMO.dir/src/C_queue.c.o
GATEWAY_DEMO: CMakeFiles/GATEWAY_DEMO.dir/build.make
GATEWAY_DEMO: CMakeFiles/GATEWAY_DEMO.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable GATEWAY_DEMO"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GATEWAY_DEMO.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GATEWAY_DEMO.dir/build: GATEWAY_DEMO

.PHONY : CMakeFiles/GATEWAY_DEMO.dir/build

CMakeFiles/GATEWAY_DEMO.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GATEWAY_DEMO.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GATEWAY_DEMO.dir/clean

CMakeFiles/GATEWAY_DEMO.dir/depend:
	cd /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/build /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/build /home/book/GATEWAY_project/TEST_RECV/GATEWAY_DEMO/build/CMakeFiles/GATEWAY_DEMO.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GATEWAY_DEMO.dir/depend

