// InsufficientFundsException.h
// Thrown when a purchase or expense costs more than the business has.
// It also stores the cost and the balance, so the catch block can show them.
#pragma once
#include <exception>

class InsufficientFundsException : public std::exception {
private:
    double cost;
    double balance;

public:
    InsufficientFundsException(double cost, double balance);
    double getCost() const;
    double getBalance() const;
    virtual const char* what() const throw() override;
};