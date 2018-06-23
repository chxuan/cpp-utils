set(STATICLIBNAME utils_wrapper)
set(SHAREDLIBNAME utils_wrapper_so)
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

aux_source_directory(. DIR_SRCS)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories($ENV{UUID_INCLUDE_PATH})
include_directories($ENV{OPENSSL_INCLUDE_PATH})

link_directories($ENV{UUID_LIB_PATH})
link_directories($ENV{OPENSSL_LIB_PATH})

add_library(${STATICLIBNAME} STATIC ${DIR_SRCS})
add_library(${SHAREDLIBNAME} SHARED ${DIR_SRCS})

set_target_properties(${SHAREDLIBNAME} PROPERTIES OUTPUT_NAME ${STATICLIBNAME})
set_target_properties(${SHAREDLIBNAME} PROPERTIES VERSION 1.1.0 SOVERSION 1)

target_link_libraries(${SHAREDLIBNAME} -Wl,--whole-archive -luuid -lcrypto -Wl,--no-whole-archive)

install(TARGETS ${STATICLIBNAME} ARCHIVE DESTINATION /usr/local/framework/utils/lib)
install(TARGETS ${SHAREDLIBNAME} LIBRARY DESTINATION /usr/local/framework/utils/lib)
install(FILES ${PROJECT_SOURCE_DIR}/include/Utils.h DESTINATION /usr/local/framework/utils/include/utils)
install(FILES ${PROJECT_SOURCE_DIR}/include/String.h DESTINATION /usr/local/framework/utils/include/utils)
install(FILES ${PROJECT_SOURCE_DIR}/include/FileSystem.h DESTINATION /usr/local/framework/utils/include/utils)
install(FILES ${PROJECT_SOURCE_DIR}/include/System.h DESTINATION /usr/local/framework/utils/include/utils)
