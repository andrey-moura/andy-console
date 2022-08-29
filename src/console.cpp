#include <console.hpp>

void uva::console::log_error(const std::string& msg)
{
    std::cerr << uva::console::color(uva::console::color_code::red) << msg << std::endl;
}

void uva::console::log_success(const std::string& msg)
{
    std::cout << uva::console::color(uva::console::color_code::green) << msg << std::endl;
}

void uva::console::log_warning(const std::string& msg)
{
    std::cout << uva::console::color(uva::console::color_code::yellow) << msg << std::endl;
}