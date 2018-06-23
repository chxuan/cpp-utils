cmake_minimum_required(VERSION 2.8)

project(Framework)

add_subdirectory(${PROJECT_SOURCE_DIR}/utils)
add_subdirectory(${PROJECT_SOURCE_DIR}/clog)
add_subdirectory(${PROJECT_SOURCE_DIR}/net-thrift)
add_subdirectory(${PROJECT_SOURCE_DIR}/net-rcf)
add_subdirectory(${PROJECT_SOURCE_DIR}/net-tcpserver)
add_subdirectory(${PROJECT_SOURCE_DIR}/threadpool)
