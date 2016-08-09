#include "Exception.hpp"

Exception::Exception(const std::string &exception) noexcept
    : exception(exception) {
}

Exception::Exception(
    const std::string &exception,
    const std::string &fileName,
    const std::uint32_t lineNumber
) noexcept {
    this->exception = exception + " occurred in " + fileName + " on line " + Common::toString(lineNumber);
}

Exception::~Exception() noexcept
{}

Exception::operator std::string() {
    return exception;
}

const char* Exception::what() const noexcept {
    return exception.c_str();
}
