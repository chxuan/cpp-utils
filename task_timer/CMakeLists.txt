cmake_minimum_required(VERSION 2.8)

project(task_timer)

set(OUTPUTNAME task_timer)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-variable -g -O2 -std=c++11")

include_directories(/usr/local/include)

link_directories(/usr/local/lib)

aux_source_directory(. DIR_SRCS)
add_executable(${OUTPUTNAME} ${DIR_SRCS})

target_link_libraries(${OUTPUTNAME} boost_system-mt)
target_link_libraries(${OUTPUTNAME} pthread)
