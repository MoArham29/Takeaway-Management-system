// Purchase.h
// Stock bought from a supplier. It takes money off the balance.
#pragma once
#include <string>
#include "Transaction.h"
#include "Supplier.h"
#include "StockItem.h"

class Purchase : public Transaction {
private:
    Supplier* supplier;
    StockItem* item;            // the stock item bought (empty for things we don't count, e.g. cleaning products)
    int quantity;
    std::string description;
    double cost;

public:
    Purchase(const std::string& date, Supplier* supplier, StockItem* item, int quantity, double cost);
    Purchase(const std::string& date, Supplier* supplier, const std::string& description, double cost);

    Supplier* getSupplier() const;
    StockItem* getItem() const;
    int getQuantity() const;
    double getCost() const;

    double getEffect() const override;
    void Display() const override;
};
