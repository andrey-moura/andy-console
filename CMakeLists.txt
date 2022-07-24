message(STATUS ${CMAKE_CURRENT_LIST_DIR})
add_library(uva-console
	${CMAKE_CURRENT_LIST_DIR}/src/console.cpp
)

target_link_libraries(uva-console)

include_directories(${CMAKE_CURRENT_LIST_DIR})
