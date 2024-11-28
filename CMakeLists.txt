#Require a minimum version
cmake_minimum_required(VERSION 3.10)

project(uva-console)

add_library(uva-console
	${CMAKE_CURRENT_LIST_DIR}/src/console.cpp
)
# ${CMAKE_CURRENT_LIST_DIR}/src/application.cpp

set(CONSOLE_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR} )

include(${CONSOLE_ROOT_DIR}/console.cmake)

target_link_libraries(uva-console uva-core)

include_directories(${CMAKE_CURRENT_LIST_DIR})

if(UVA_CONSOLE_IS_TOP_LEVEL)
	message(STATUS "Including console tool")
	include("${CMAKE_CURRENT_LIST_DIR}/tool/CMakeLists.txt")
endif()