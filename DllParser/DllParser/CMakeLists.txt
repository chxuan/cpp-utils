project(DllParser)

set(OUTPUTNAME DllParser)

aux_source_directory(. DIR_SRCS)
add_executable(${OUTPUTNAME} ${DIR_SRCS})

target_link_libraries(${OUTPUTNAME} dl)

