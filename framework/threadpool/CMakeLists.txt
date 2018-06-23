cmake_minimum_required(VERSION 2.8)

project(threadpool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -O2 -std=c++11")

aux_source_directory(. SRC_LIST)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

