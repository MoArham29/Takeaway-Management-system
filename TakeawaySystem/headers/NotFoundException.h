// NotFoundException.h
// Thrown when a supplier or stock item number doesn't exist.
#pragma once
#include <exception>
#include <string>

class NotFoundException : public std::exception {
private:
    std::string message;

public:
    NotFoundException(const std::string& what, int id);
    virtual const char* what() const throw() override;   // gives back the error message
};