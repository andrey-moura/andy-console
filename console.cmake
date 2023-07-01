function(add_console_app name)

    message(STATUS "Add console app for folder ${CMAKE_CURRENT_LIST_DIR}")

    file(GLOB_RECURSE source_files CONFIGURE_DEPENDS 
        "${CMAKE_CURRENT_LIST_DIR}/include/controllers/*_controller.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/controllers/*_controller.cpp"
    )

    SET(source_files
        ${source_files}
        "${CMAKE_CURRENT_LIST_DIR}/config/routes.cpp")

    message(STATUS "Get these files: ${source_files}")

    add_executable(
        # The name of your game
        ${name}

        ${source_files}
    )

    target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include/controllers")
    target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include/")

    if(WIN32)
        target_link_options(${name} PUBLIC /SAFESEH:NO)
    endif()

endfunction(add_console_app)