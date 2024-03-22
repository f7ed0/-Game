#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <sstream>

namespace game3D {
    enum LogLevel : unsigned short {
        err = 0,
        warn = 2,
        info = 4,
        debug = 8,
    };

    class Logger {
        private :

            static unsigned short log_level;

            static void out(const std::string&, LogLevel LogLevel );

        public :
            static void error(const std::string& msg);
            static void warn(const std::string& msg);
            static void info(const std::string& msg);
            static void debug(const std::string& msg);

            static void setLogLevel(LogLevel level);
    };
}

#endif