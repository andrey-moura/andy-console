#Require a minimum version
cmake_minimum_required(VERSION 3.20)

project(uva-console)

add_library(uva-console
	${CMAKE_CURRENT_LIST_DIR}/src/console.cpp
)

target_link_libraries(uva-console)

include_directories(${CMAKE_CURRENT_LIST_DIR})
