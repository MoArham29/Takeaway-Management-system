// InvalidAmountException.cpp
#include "InvalidAmountException.h"

InvalidAmountException::InvalidAmountException(const std::string& reason)
    : message("Invalid amount: " + reason) {}

const char* InvalidAmountException::what() const throw() {
    return message.c_str();
}