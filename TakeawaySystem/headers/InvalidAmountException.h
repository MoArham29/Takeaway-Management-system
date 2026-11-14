// InvalidAmountException.h
// Thrown when a number makes no sense, such as a negative sale or stock count.
#pragma once
#include <exception>
#include <string>

class InvalidAmountException : public std::exception {
private:
    std::string message;

public:
    InvalidAmountException(const std::string& reason);
    virtual const char* what() const throw() override;
};