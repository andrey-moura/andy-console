#include <application.hpp>

#include <iostream>

using namespace uva;
using namespace routing;
using namespace console;

void application::init(int argc, const char **argv)
{
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