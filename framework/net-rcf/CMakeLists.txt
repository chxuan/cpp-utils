cmake_minimum_required(VERSION 2.8)

project(Net-rcf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-local-typedefs -g -O2")
#set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/tests)

install(FILES ${PROJECT_SOURCE_DIR}/include/RCFServerWrapper.hpp DESTINATION /usr/local/framework/net-rcf/include/net-rcf)
install(FILES ${PROJECT_SOURCE_DIR}/include/RCFServerImpl.hpp DESTINATION /usr/local/framework/net-rcf/include/net-rcf)
install(FILES ${PROJECT_SOURCE_DIR}/include/RCFClientWrapper.hpp DESTINATION /usr/local/framework/net-rcf/include/net-rcf)
install(FILES ${PROJECT_SOURCE_DIR}/include/RCFClientImpl.hpp DESTINATION /usr/local/framework/net-rcf/include/net-rcf)

install(FILES ${PROJECT_SOURCE_DIR}/include/RCFPublisherWrapper.hpp DESTINATION /usr/local/framework/net-rcf/include/net-rcf)
install(FILES ${PROJECT_SOURCE_DIR}/include/RCFPublisherImpl.hpp DESTINATION /usr/local/framework/net-rcf/include/net-rcf)
install(FILES ${PROJECT_SOURCE_DIR}/include/RCFSubscriberWrapper.hpp DESTINATION /usr/local/framework/net-rcf/include/net-rcf)
install(FILES ${PROJECT_SOURCE_DIR}/include/RCFSubscriberImpl.hpp DESTINATION /usr/local/framework/net-rcf/include/net-rcf)


