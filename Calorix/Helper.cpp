#include "Helper.h"
#include <chrono>

bool Helper::isToday(const time_t& entryTimeStamp) {
    auto current_zone = std::chrono::current_zone();

    auto current_day = current_zone->to_local(std::chrono::system_clock::now());
    auto entry_day = current_zone->to_local(std::chrono::system_clock::from_time_t(entryTimeStamp));

    return std::chrono::floor<std::chrono::days>(current_day) ==
        std::chrono::floor<std::chrono::days>(entry_day);
}