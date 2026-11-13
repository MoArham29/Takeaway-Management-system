
// Happens when a payment can't be processed (zero/negative amount, or card declined).
#pragma once

#include <exception>   
#include <string>

// EXCEPTION CLASS
class InvalidPaymentException : public std::exception {
private:
    std::string message;   

public:
    // ----- CONSTRUCTOR -----
    InvalidPaymentException(const std::string& reason);

    // POLYMORPHISM 
    // In this section polymorphism is used to override the what() method from the std::exception class.
    const char* what() const noexcept override;
};
