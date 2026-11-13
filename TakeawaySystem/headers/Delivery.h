// One stock delivery from a supplier (what arrived, when, and how much it cost).
// Deliveries are stored in a LinkedList in the order they arrive.
#pragma once

#include <iostream>
#include <string>
#include "Supplier.h"

class Delivery {
private:
    // Data members 
    Supplier* supplier;
    std::string date;         
    std::string description;  
    double cost;              
public:
    // CONSTRUCTOR
    Delivery(Supplier* supplier, const std::string& date,
             const std::string& description, double cost);

    // DESTRUCTOR
    ~Delivery();

    Supplier* getSupplier() const;
    std::string getDate() const;
    std::string getDescription() const;
    double getCost() const;
// FRIENDSHIP + OPERATOR OVERLOADING
    friend std::ostream& operator<<(std::ostream& out, const Delivery& d);
};