cmake_minimum_required (VERSION 2.8)
set( APPNAME app )
project( ${APPNAME} )
if( DEBUG )
    add_definitions( "-Wall -g" )
endif()
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )

aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/src DIR_SRCS)
add_executable( ${APPNAME} ${DIR_SRCS} )
target_link_libraries( ${APPNAME} pthread )
#set(CMAKE_C_FLAGS_DEBUG "${CUSTOM_FLAGS_WITH_SPACE} -g -ggdb -O0 -Wall  -fsanitize=address" )

foreach(f IN LISTS DIR_SRCS )
  get_filename_component(b ${f} NAME)
  set_source_files_properties(${f} PROPERTIES
    COMPILE_DEFINITIONS "__FILENAME__=\"${b}\"")
endforeach()
