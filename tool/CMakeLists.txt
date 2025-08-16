#Require a minimum version
cmake_minimum_required(VERSION 3.10)

project(console)

include(${CONSOLE_ROOT_DIR}/console.cmake)

add_console_app(console)

target_link_libraries(console andy-console andy-core andy-routing andy-file)

add_custom_command(TARGET console 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:console> ${CMAKE_SOURCE_DIR}/bin/console)