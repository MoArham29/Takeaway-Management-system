// Purchase.cpp
#include "Purchase.h"
#include <iostream>
#include <iomanip>

// Buying a stock item we count (e.g. 11 boxes of chicken)
Purchase::Purchase(const std::string& date, Supplier* supplier, StockItem* item, int quantity, double cost)
    : Transaction(date), supplier(supplier), item(item), quantity(quantity),
      description(std::to_string(quantity) + " " + item->getUnit() + " " + item->getName()), cost(cost) {}

// Buying something we don't count (e.g. cleaning products)
Purchase::Purchase(const std::string& date, Supplier* supplier, const std::string& description, double cost)
    : Transaction(date), supplier(supplier), item(nullptr), quantity(0), description(description), cost(cost) {}

Supplier* Purchase::getSupplier() const { return supplier; }
StockItem* Purchase::getItem() const { return item; }
int Purchase::getQuantity() const { return quantity; }
double Purchase::getCost() const { return cost; }

// Money out
double Purchase::getEffect() const {
    return -cost;
}

void Purchase::Display() const {
    Transaction::Display();
    std::cout << std::fixed << std::setprecision(2)
              << "PURCHASE  " << description << " from " << supplier->getName()
              << "  -" << cost << std::endl;
}