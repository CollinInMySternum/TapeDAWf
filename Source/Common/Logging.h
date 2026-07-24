#pragma once

#include <format>
#include <iostream>
#include <chrono>

namespace Tapedawf {
    template<typename... Args>
    inline void LOG(std::string_view tag, std::format_string<Args...> fmt, Args&&... args) {
        auto now = std::chrono::system_clock::now();
        auto local = std::chrono::zoned_time{std::chrono::current_zone(), now};
        auto secs = std::chrono::floor<std::chrono::seconds>(local.get_local_time());

        std::cout << std::format(
            "[{:%H:%M:%S}] [{}] {}\n",
            secs,
            tag,
            std::format(fmt, std::forward<Args>(args)...));
    }
}