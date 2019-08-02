cmake_minimum_required( VERSION 3.7 )

project( Snake )

set( TARGET Snake )

include( FindPkgConfig )

pkg_search_module( SDL2 REQUIRED sdl2 )
pkg_search_module( SDL2IMAGE REQUIRED SDL2_image>=2.0.0 )

include_directories( inc )
include_directories( ${SDL2_INCLUDE_DIRS} )
include_directories( ${SDL2IMAGE_INCLUDE_DIRS} )

file( GLOB SOURCES "src/*.c" )

add_executable( ${TARGET} ${SOURCES} )

target_link_libraries( ${TARGET} ${SDL2_LIBRARIES} )
target_link_libraries( ${TARGET} ${SDL2IMAGE_LIBRARIES} )
target_link_libraries( ${TARGET} m )