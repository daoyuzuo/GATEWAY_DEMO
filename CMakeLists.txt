# 指定最低版本要求
project(GATEWAY_DEMO)
#SET(CMAKE_C_COMPILER /usr/bin/gcc)
#SET(CMAKE_CXX_COMPILER /usr/bin/g++)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")
cmake_minimum_required(VERSION 3.0)

# 指定项目名称

# 指定生成的可执行文件的名字 源文件
include_directories(include)
add_executable(GATEWAY_DEMO src/main.c src/raw_socket_ipv6.c src/socket_can.c 
src/protocol_convert.c src/protocol_translate.c src/priority.c src/redundancy_transmit.c src/C_queue.c)
target_link_libraries(GATEWAY_DEMO pthread)