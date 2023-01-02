#include <routing.hpp>

#define DECLARE_CONSOLE_APPLICATION(...) \
int main(int argc, const char **argv)\
{\
    __VA_ARGS__\
    application::init(argc, argv);\
    return 0;\
}\

namespace uva
{
    namespace console
    {
        namespace application
        {
            void init(int argc, const char **argv);
        }; // namespace application
        
    }; // namespace console
     
}; // namespace console