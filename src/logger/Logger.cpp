#include "logger/Logger.hpp"
#include <chrono>
#include <string.h>

using namespace game3D;

unsigned short Logger::log_level = 4;

void Logger::out(const std::string& msg, LogLevel LogLevel) {
    std::string prefix;
    switch (LogLevel) {
        case LogLevel::err :
            prefix = "[ERROR]";
            break;
        case LogLevel::warn :
            prefix = "[WARN] ";
            break;
        case LogLevel::info :
            prefix = "[INFO] ";
            break;
        default:
            prefix = "[DEBUG]";
            break;
    }
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::cout << strtok(std::ctime(&now_time), "\n") << " " << prefix << " " << msg << std::endl;
}

void Logger::error(const std::string& msg) {
    if(log_level < (unsigned short) LogLevel::err) {
        return;
    }
    Logger::out(msg,LogLevel::err);

}

void Logger::warn(const std::string& msg) {
    if(log_level < (unsigned short) LogLevel::warn) {
        return;
    }
    Logger::out(msg,LogLevel::warn);
}

void Logger::info(const std::string& msg) {
    if(log_level < (unsigned short) LogLevel::info) {
        return;
    }
    Logger::out(msg,LogLevel::info);
}

void Logger::debug(const std::string& msg) {
    if(log_level < (unsigned short) LogLevel::debug) {
        return;
    }
    Logger::out(msg,LogLevel::debug);
}

void Logger::setLogLevel(LogLevel level) {
    Logger::log_level = level;
}