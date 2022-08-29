#pragma once

#include <iostream>
#include <string>
#include <map>
#include <format>

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

            void begin_color() const
            {
                *os << "\033[" << (size_t)code << "m";
            }

            void end_color() const 
            {
                *os << "\033[0m";
            }

            // Override for std::cout compatibility - that starts color code on console
            friend const color& operator << (std::ostream& os, const color& c)
            {
                color* pColor = (color*)&c;
                pColor->os = &os;

                c.begin_color();
                return c;
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
        };

        void log_error(const std::string& msg);

        template<class... Args>
        void log_error(const std::string& fmt, Args... args)
        {
            #ifdef USE_FMT_FORMT
                std::string msg = vformat(fmt, std::make_format_args(args...));
            #else
                std::string msg = std::format(fmt, std::forward<Args>(args)...);
            #endif

            log_error(msg);
        }

        void log_success(const std::string& msg);

        template<class... Args>
        void log_success(const std::string& fmt, Args... args)
        {
            #ifdef USE_FMT_FORMT
                std::string msg = vformat(fmt, std::make_format_args(args...));
            #else
                std::string msg = std::format(fmt, std::forward<Args>(args)...);
            #endif

            log_success(msg);
        }

        void log_warning(const std::string& msg);

        template<class... Args>
        void log_warning(const std::string& fmt, Args... args)
        {
            #ifdef USE_FMT_FORMT
                std::string msg = vformat(fmt, std::make_format_args(args...));
            #else
                std::string msg = std::format(fmt, std::forward<Args>(args)...);
            #endif

            log_warning(msg);
        }
    };
};