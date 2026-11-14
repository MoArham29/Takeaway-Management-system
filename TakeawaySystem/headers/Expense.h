// Expense.h
// A bill that isn't stock, such as rent, wages or electricity. It takes money off the balance.
#pragma once
#include <string>
#include "Transaction.h"

class Expense : public Transaction {
private:
    std::string category;
    double amount;

public:
    Expense(const std::string& date, const std::string& category, double amount);

    double getEffect() const override;
    void Display() const override;
};