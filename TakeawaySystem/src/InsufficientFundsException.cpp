// InsufficientFundsException.cpp
#include "InsufficientFundsException.h"

InsufficientFundsException::InsufficientFundsException(double cost, double balance)
    : cost(cost), balance(balance) {}

double InsufficientFundsException::getCost() const { return cost; }
double InsufficientFundsException::getBalance() const { return balance; }

const char* InsufficientFundsException::what() const throw() {
    return "Not enough money in the business for this payment";
}
