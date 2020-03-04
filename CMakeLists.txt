cmake_minimum_required( VERSION 3.16 )
set( CMAKE_CXX_STANDARD 14 )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin )

project( GameEngine2D )

add_subdirectory( Engine )
add_subdirectory( Application )