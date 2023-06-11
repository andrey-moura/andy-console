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

std::map<std::string, std::string>& uva::console::get_named_args()
{
    static std::map<std::string, std::string> named_args;

    return named_args;
}


void uva::console::init_args(const int argc, char** argv)
{
    auto& args = get_args();
    auto& named_args = get_named_args();

    args.reserve(argc);

    for(size_t i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];
        args.push_back(std::string(arg));

        if(arg.starts_with("--")) {
            std::string key;
            std::string val;

            size_t to_reserve = 128;
            key.reserve(to_reserve);
            val.reserve(to_reserve);

            arg.remove_prefix(2);

            while(arg.size() && !arg.starts_with('=')) {
                key.push_back(arg.front());
                arg.remove_prefix(1);
            }

            if(arg.size()) {
                arg.remove_prefix(1);

                while(arg.size()) {
                    val.push_back(arg.front());
                    arg.remove_prefix(1);
                }
            }

            named_args.insert({key,val});
        }

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