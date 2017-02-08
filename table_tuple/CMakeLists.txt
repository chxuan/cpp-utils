cmake_minimum_required(VERSION 2.8)

project(table_tuple)

set(OUTPUTNAME table_tuple)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -O3 -std=c++11")

aux_source_directory(. DIR_SRCS)
add_executable(${OUTPUTNAME} ${DIR_SRCS})

