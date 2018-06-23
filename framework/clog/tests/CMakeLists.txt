set(OUTPUTNAME LogTest)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

aux_source_directory(. DIR_SRCS)

include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(${PROJECT_SOURCE_DIR}/../utils/lib)
link_directories($ENV{LOG4CPP_LIB_PATH})
link_directories($ENV{UUID_LIB_PATH})
link_directories($ENV{OPENSSL_LIB_PATH})

add_executable(${OUTPUTNAME} ${DIR_SRCS})

target_link_libraries(${OUTPUTNAME} liblog_wrapper.a)
target_link_libraries(${OUTPUTNAME} liblog4cpp.a)
target_link_libraries(${OUTPUTNAME} libutils_wrapper.a)
target_link_libraries(${OUTPUTNAME} libuuid.a)
target_link_libraries(${OUTPUTNAME} libcrypto.a)
target_link_libraries(${OUTPUTNAME} libpthread.so)
