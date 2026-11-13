// Implementation of the EmptyReportException class.
#include "EmptyReportException.h"

// CONSTRUCTOR
EmptyReportException::EmptyReportException(const std::string& date)
    : message("Daily report for " + date + " has no sales") {}

    const char* EmptyReportException::what() const noexcept {
    return message.c_str();
}