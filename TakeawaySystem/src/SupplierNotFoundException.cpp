
// this is the implementation of the SupplierNotFoundException class.
#include "SupplierNotFoundException.h"

//  CONSTRUCTOR 
// Builds the full error message once, when the exception is thrown.
SupplierNotFoundException::SupplierNotFoundException(int id)
    : message("Supplier not found: no supplier has ID " + std::to_string(id)) {}

const char* SupplierNotFoundException::what() const noexcept {
    return message.c_str();
}