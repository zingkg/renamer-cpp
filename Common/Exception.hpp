#ifndef EXCEPTION_HPP
#define	EXCEPTION_HPP

#include "Common.hpp"

#include <exception>
#include <string>

class Exception: public std::exception {
public:
    Exception(const std::string &exception) noexcept;

    Exception(
        const std::string &exception,
        const std::string &fileName,
        const std::uint32_t lineNumber
    ) noexcept;

    ~Exception() noexcept override;

    operator std::string();

    const char* what() const noexcept override;

private:
    std::string exception;
};

#endif // EXCEPTION_HPP
