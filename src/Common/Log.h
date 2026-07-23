#pragma once

#include <format>
#include <iostream>
#include <chrono>

#define LOG(tag, fmtString, ...) \
do { \
    auto timePoint = std::chrono::system_clock::now(); \
    auto localTime = std::chrono::zoned_time{std::chrono::current_zone(), timePoint}; \
    auto timeSecs = std::chrono::floor<std::chrono::seconds>(localTime.get_local_time()); \
    std::string formattedMsg = std::format(fmtString, ##__VA_ARGS__); \
    std::cout << std::format("[{:%H:%M:%S}] [{}] {}\n", timeSecs, tag, formattedMsg); \
} while(0)