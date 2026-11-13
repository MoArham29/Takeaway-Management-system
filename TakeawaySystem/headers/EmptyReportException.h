// is used when closing a day, or calculating profit, for a report with no sales.
#pragma once

#include <exception>   
#include <string>

// EXCEPTION CLASS
class EmptyReportException : public std::exception {
private:
    std::string message;  

public:
    //  CONSTRUCTOR 
    EmptyReportException(const std::string& date);

    //  POLYMORPHISM
    // We override it to return my own message. 'noexcept' promises this function never throws.
    const char* what() const noexcept override;
};