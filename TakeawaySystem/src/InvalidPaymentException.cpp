// Implementation of the InvalidPaymentException class.
#include "InvalidPaymentException.h"

// CONSTRUCTOR
// Builds the full error message once, when the exception is happens.
InvalidPaymentException::InvalidPaymentException(const std::string& reason)
    : message("Invalid payment: " + reason) {}

const char* InvalidPaymentException::what() const noexcept {
    return message.c_str();
}