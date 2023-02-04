#include <application.hpp>

#include <iostream>

using namespace uva;
using namespace routing;
using namespace console;

void application::init(int argc, const char **argv)
{
#if 0
	const char* debug_arguments[]{ argv[0], "init", "C:\\Moonslate\\UserTracking\\user-tracking-api\\config\\routes.cpp", "484" };

    const size_t argument_count = sizeof(debug_arguments) / sizeof(const char*);
	argc = argument_count;
	argv = debug_arguments;

#endif
    //starts a new connection. 
    std::shared_ptr<basic_connection> connection = std::make_shared<basic_connection>();
    var params = empty_map;

    std::string cwd = argv[0];

    std::string action;

    if(argc > 1) {
        action = argv[1];
    }

    std::string arg;

    if(argc > 2) {
        for(size_t i = 0; i < argc-2; ++i)
        {
            arg = argv[i+2];
            params[i] = arg;
        }
    }

    basic_action_target target = find_dispatch_target(action, connection);

    if(target.controller) {
        target.controller->params = params;
        dispatch(target, connection);
    } else {
        //help
    }
}