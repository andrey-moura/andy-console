#Require a minimum version
cmake_minimum_required(VERSION 3.10)

project(uva-console)

add_library(uva-console
	${CMAKE_CURRENT_LIST_DIR}/src/console.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/application.cpp
)

set(CONSOLE_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR} )

include(${CONSOLE_ROOT_DIR}/console.cmake)

target_link_libraries(uva-console)

include_directories(${CMAKE_CURRENT_LIST_DIR})

include("${CMAKE_CURRENT_LIST_DIR}/tool/CMakeLists.txt")
