set(SHAREDLIBNAME cac)

aux_source_directory(. DIR_SRCS)

add_library(${SHAREDLIBNAME} SHARED ${DIR_SRCS})

