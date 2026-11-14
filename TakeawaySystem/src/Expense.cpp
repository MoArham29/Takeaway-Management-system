// Expense.cpp
#include "Expense.h"
#include <iostream>
#include <iomanip>

Expense::Expense(const std::string& date, const std::string& category, double amount)
    : Transaction(date), category(category), amount(amount) {}

// Money out
double Expense::getEffect() const {
    return -amount;
}

void Expense::Display() const {
    Transaction::Display();
    std::cout << std::fixed << std::setprecision(2)
              << "EXPENSE   " << category << "  -" << amount << std::endl;
}