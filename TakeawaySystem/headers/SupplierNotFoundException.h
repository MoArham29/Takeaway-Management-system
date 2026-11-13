
// this  comes when searching for, or removing, a supplier ID that isn't in the Tree.
#pragma once

#include <exception>   
#include <string>

// EXCEPTION CLASS


class SupplierNotFoundException : public std::exception {
private:
    std::string message;   
public:
    // CONSTRUCTOR 
    SupplierNotFoundException(int id);

    // POLYMORPHISM
    const char* what() const noexcept override;
};