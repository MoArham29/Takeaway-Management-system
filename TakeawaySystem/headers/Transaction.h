// Transaction.h
// Any movement of money in or out of the business.
// This is an abstract class: you can only create DailySales, Purchase or Expense.
#pragma once
#include <string>

class Transaction {
protected:
    int id;
    std::string date;
    static int nextId;

public:
    Transaction(const std::string& date);
    virtual ~Transaction();

    int getId() const;
    std::string getDate() const;

    // How this transaction changes the balance: positive = money in, negative = money out.
    // "= 0" means each type of transaction must write its own version.
    virtual double getEffect() const = 0;

    // Shows the transaction. Each type adds its own details.
    virtual void Display() const;
};