#include <console.hpp>
#include <filesystem>
#include <fstream>

void uva::console::put_on_cout(const std::string & msg)
{
    std::cout << msg << std::endl;
}

std::ofstream& get_log()
{
    static std::ofstream* stream = nullptr;

    if(!stream) {
        std::filesystem::path logs_folder = std::filesystem::absolute("logs");
        if(!std::filesystem::exists(logs_folder)) {
            if(!std::filesystem::create_directories(logs_folder)) {
                throw std::runtime_error("error: cannot create directory");
            }
        }
        stream = new std::ofstream(logs_folder / "log.txt");
    }
    return *stream;
}

void uva::console::log(const std::string &msg)
{
    std::ofstream& stream = get_log();
    stream << msg << "\r\n";
    stream.flush();
}

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

std::vector<std::string>& uva::console::get_args()
{
    static std::vector<std::string> args;

    return args;
}

void uva::console::init_args(const int argc, char** argv)
{
    auto& args = get_args();

    for(size_t i = 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }
}

size_t uva::console::args_count()
{
    return get_args().size();
}

bool uva::console::has_args()
{
    return args_count();
}

std::string uva::console::front_arg()
{
    if(!has_args()) {
        throw std::out_of_range("front_arg error: there is no arguments");
    }

    auto& args = get_args();

    std::string arg = std::move(args.front());

    args.erase(args.begin());

    return arg;
}