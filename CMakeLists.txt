#Require a minimum version
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project(andy-console)

set(CMAKE_CXX_STANDARD 20)

add_library(andy-console OBJECT
	${CMAKE_CURRENT_LIST_DIR}/src/console.cpp
)
# ${CMAKE_CURRENT_LIST_DIR}/src/application.cpp

set(CONSOLE_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR} )

include(${CONSOLE_ROOT_DIR}/console.cmake)

target_link_libraries(andy-console)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if(UVA_CONSOLE_IS_TOP_LEVEL)
	message(STATUS "Including console tool")
	include("${CMAKE_CURRENT_LIST_DIR}/tool/CMakeLists.txt")
endif()

# install(TARGETS andy-console EXPORT andy-consoleTargets)
# install(EXPORT andy-consoleTargets
#     FILE andy-consoleTargets.cmake
#     DESTINATION lib/cmake/andy-console
# )
# install(TARGETS andy-console DESTINATION lib)
# install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/andy DESTINATION include)