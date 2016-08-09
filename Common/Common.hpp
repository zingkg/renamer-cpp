#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstdint>
#include <string>

class Common {
public:
    static std::string toString(const std::size_t num);

    static std::int64_t parseInt(const char* string);
};

#endif // COMMON_HPP_
