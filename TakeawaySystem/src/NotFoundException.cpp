// NotFoundException.cpp
#include "NotFoundException.h"

// Builds a message such as "Supplier 99 not found"
NotFoundException::NotFoundException(const std::string& what, int id)
    : message(what + " " + std::to_string(id) + " not found") {}

const char* NotFoundException::what() const throw() {
    return message.c_str();
}