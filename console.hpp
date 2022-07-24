#include <iostream>
#include <string>
#include <map>

#ifdef _WIN32

    #include <windows.h>
#endif

namespace uva
{
    namespace console
    {
        enum class color_code
        {
            red = 31,
            green = 32,
            yellow = 33,
            blue = 34,
            pink = 35,
            light_blue = 36

        }; 

        struct color
        {
            const size_t code;
            std::ostream* os = nullptr;
            color(const color_code& code)
                : code((const size_t)code)
            {
                
            }

            // Override for std::cout compatibility - that finishs the color code on console
            friend std::ostream& operator << (const color& color, const std::string& str)
            {
                std::ostream& os = *color.os;

                for(const char& c : str) {

                    os << c;

                    if(c == '\n') {
                        color.end_color();
                        color.begin_color();
                    }

                }

                color.end_color();

                return os;
            }

            std::string begin_color() const
            {
                *os << "\033[" << (size_t)code << "m";
            }

            std::string end_color() const 
            {
                *os << "\033[0m";
            }

            // Override for std::cout compatibility - that starts color code on console
            friend std::ostream& operator << (std::ostream& os, const color& c)
            {
                color* pColor = (color*)&c;
                pColor->os = &os;

                c.begin_color();
                return os;
            }
        };

    };
};