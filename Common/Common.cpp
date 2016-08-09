#include "Common.hpp"

#include <sstream>

std::string Common::toString(const std::size_t num) {
    std::ostringstream sStream;
    sStream << num;
    return sStream.str();
}

std::int64_t Common::parseInt(const char* string) {
    std::istringstream sStream(string);
    std::int64_t num;
    sStream >> num;
    return num;
}
