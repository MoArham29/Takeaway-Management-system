// Transaction.cpp
#include "Transaction.h"
#include <iostream>

int Transaction::nextId = 1;

Transaction::Transaction(const std::string& date) : id(nextId++), date(date) {}

Transaction::~Transaction() {}

int Transaction::getId() const { return id; }
std::string Transaction::getDate() const { return date; }

// Shows the part every transaction has: its number and date
void Transaction::Display() const {
    std::cout << "  #" << id << " " << date << " | ";
}