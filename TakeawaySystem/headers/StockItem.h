// StockItem.h
// Something the takeaway keeps in stock, such as boxes of chicken.
// Each item has a "full level": how many we want after a delivery.
// Stock items are kept in a BinaryTree.
#pragma once
#include <iostream>
#include <string>
#include "Supplier.h"

class StockItem {
private:
    int id;
    std::string name;
    std::string unit;           // e.g. "boxes", "bags"
    int quantity;               // how many we have now
    int fullLevel;              // how many we want after a delivery
    Supplier* supplier;         // who we buy it from (points to a supplier in the tree)
    static int nextId;

public:
    StockItem(const std::string& name, const std::string& unit, int fullLevel, Supplier* supplier);
    ~StockItem();

    int getId() const;
    std::string getName() const;
    std::string getUnit() const;
    int getQuantity() const;
    Supplier* getSupplier() const;

    void setQuantity(int count);      // used for the nightly stock count
    int amountToOrder() const;        // how many to order to get back to the full level
    void Display() const;

    StockItem& operator+=(int delivered);     // adds a delivery: chicken += 11;
    friend std::ostream& operator<<(std::ostream& out, const StockItem& item);
};