#include <console_controller.hpp>

#include <iostream>

#include <console.hpp>
#include <file.hpp>

void console_controller::new_project()
{
    if(!params.size()) {
        log_error("error: missing argument 'project name'");
        return;
    } 

    var project_name = params[0];

    std::filesystem::create_directories(project_name.to_s());

    std::filesystem::path project_root = std::filesystem::absolute(project_name.to_s());
    std::filesystem::create_directories(project_root / "src/controllers");
    std::filesystem::create_directories(project_root / "include/controllers");
    std::filesystem::create_directories(project_root / "config");

    static std::string routes_template =
R"~~~(#include <iostream>
#include <application.hpp>

using namespace uva;
using namespace routing;
using namespace console;

DECLARE_CONSOLE_APPLICATION(
    //Declare your routes above. As good practice, keep then ordered by controler.
    //You can have C++ code here, perfect for init other libraries.
)
)~~~";

    uva::file::write_all_text(project_root / "config" / "routes.cpp", routes_template);

    static std::string cmake_template =
    std::format(
R"~~~(#Require a minimum version
cmake_minimum_required(VERSION 3.10)

project({})

include(${{CONSOLE_ROOT_DIR}}/console.cmake)

add_console_app({})

target_link_libraries({} uva-console uva-core uva-routing)

add_custom_command(TARGET {} 
                   POST_BUILD
                   COMMAND ${{CMAKE_COMMAND}} -E copy $<TARGET_FILE:{}> ${{CMAKE_SOURCE_DIR}}/bin/{})

)~~~", project_name.downcase(), project_name.downcase(), project_name.downcase(), project_name.downcase(), project_name.downcase(), project_name.downcase());

    uva::file::write_all_text(project_root / "CMakeLists.txt", cmake_template);

    if(params.key("--git") != null) {
        std::cout << "Initializing git repository..." << std::endl;
    }
}

void console_controller::controller()
{
    if(params.size() < 1) {
        uva::console::log_error("error: missing param 'controller name'");
        return;        
    }

    std::filesystem::path project_root = std::filesystem::current_path();
    std::filesystem::path controller_include = project_root / "include" / "controllers";
    std::filesystem::path controller_source = project_root / "src" / "controllers";

    if(!std::filesystem::exists(controller_include) || !std::filesystem::exists(controller_source)) {
        uva::console::log_error("error: cannot find controllers folder");
        return;
    }

    std::string controller_name = params[0];

    const char* const controller_header_format =
R"~~~(#include <application.hpp>

using namespace uva;
using namespace routing;
using namespace console;

class {}_controller : public basic_controller
{{
public:
}};
)~~~";

    const char* const controller_source_format =
R"~~~(#include <{}_controller.hpp>

#include <iostream>

#include <console.hpp>
#include <file.hpp>
#include <core.hpp>

)~~~";

    uva::file::write_all_text(controller_include / (controller_name + "_controller.hpp"), std::format(controller_header_format, controller_name));
    uva::file::write_all_text(controller_source  / (controller_name + "_controller.cpp"), std::format(controller_source_format, controller_name));

}