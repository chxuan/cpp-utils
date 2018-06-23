set(OUTPUTNAME PublisherTest)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/PubSub")

aux_source_directory(. DIR_SRCS)

include_directories(${PROJECT_SOURCE_DIR}/tests/MessageDef)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories($ENV{RCF_INCLUDE_PATH})
include_directories($ENV{BOOST_INCLUDE_PATH})

link_directories($ENV{RCF_LIB_PATH})
link_directories($ENV{BOOST_LIB_PATH})

add_executable(${OUTPUTNAME} ${DIR_SRCS})

target_link_libraries(${OUTPUTNAME} RcfDll)
target_link_libraries(${OUTPUTNAME} boost_thread)
target_link_libraries(${OUTPUTNAME} boost_system)
