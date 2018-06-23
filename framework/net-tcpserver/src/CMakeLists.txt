set(STATICLIBNAME tcpserver_wrapper)
set(SHAREDLIBNAME tcpserver_wrapper_so)
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

aux_source_directory(. DIR_SRCS)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories($ENV{BOOST_INCLUDE_PATH})

link_directories($ENV{BOOST_LIB_PATH})

add_library(${STATICLIBNAME} STATIC ${DIR_SRCS})
add_library(${SHAREDLIBNAME} SHARED ${DIR_SRCS})

set_target_properties(${SHAREDLIBNAME} PROPERTIES OUTPUT_NAME ${STATICLIBNAME})
set_target_properties(${SHAREDLIBNAME} PROPERTIES VERSION 1.1.0 SOVERSION 1)

target_link_libraries(${SHAREDLIBNAME} -Wl,--whole-archive -lboost_serialization -lboost_system -Wl,--no-whole-archive)

install(TARGETS ${STATICLIBNAME} ARCHIVE DESTINATION /usr/local/framework/net-tcpserver/lib)
install(TARGETS ${SHAREDLIBNAME} LIBRARY DESTINATION /usr/local/framework/net-tcpserver/lib)
install(FILES ${PROJECT_SOURCE_DIR}/include/CJob.h DESTINATION /usr/local/framework/net-tcpserver/include/net-tcpserver)
install(FILES ${PROJECT_SOURCE_DIR}/include/CRealJob.h DESTINATION /usr/local/framework/net-tcpserver/include/net-tcpserver)
install(FILES ${PROJECT_SOURCE_DIR}/include/CThread.h DESTINATION /usr/local/framework/net-tcpserver/include/net-tcpserver)
install(FILES ${PROJECT_SOURCE_DIR}/include/CThreadManage.h DESTINATION /usr/local/framework/net-tcpserver/include/net-tcpserver)
install(FILES ${PROJECT_SOURCE_DIR}/include/CThreadPool.h DESTINATION /usr/local/framework/net-tcpserver/include/net-tcpserver)
install(FILES ${PROJECT_SOURCE_DIR}/include/CWorkerThread.h DESTINATION /usr/local/framework/net-tcpserver/include/net-tcpserver)
install(FILES ${PROJECT_SOURCE_DIR}/include/Message.h DESTINATION /usr/local/framework/net-tcpserver/include/net-tcpserver)
install(FILES ${PROJECT_SOURCE_DIR}/include/TcpClientImpl.h DESTINATION /usr/local/framework/net-tcpserver/include/net-tcpserver)
install(FILES ${PROJECT_SOURCE_DIR}/include/TcpClientWrapper.h DESTINATION /usr/local/framework/net-tcpserver/include/net-tcpserver)
install(FILES ${PROJECT_SOURCE_DIR}/include/TcpServerImpl.h DESTINATION /usr/local/framework/net-tcpserver/include/net-tcpserver)
install(FILES ${PROJECT_SOURCE_DIR}/include/TcpServerWrapper.h DESTINATION /usr/local/framework/net-tcpserver/include/net-tcpserver)
install(FILES ${PROJECT_SOURCE_DIR}/include/TcpSession.h DESTINATION /usr/local/framework/net-tcpserver/include/net-tcpserver)
