#include <exception>
#include <string>
#pragma once

class Error : public std::exception {
protected:
    std::string message;
public:
    Error(const std::string message) : message(message) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
    virtual ~Error() = default;
};
class RepositoryError : public Error {
public:
    RepositoryError(const std::string& message) : Error(message) {};
};

class ValidationError : public Error {
public:
    ValidationError(const std::string &message) : Error(message) {};
};