// Delivery.cpp
// Implementation of the Delivery class.
#include "Delivery.h"
#include <iomanip>

// CONSTRUCTOR 
Delivery::Delivery(Supplier* supplier, const std::string& date,
                   const std::string& description, double cost)
    : supplier(supplier), date(date), description(description), cost(cost) {}

// DESTRUCTOR 
// Prints a message only. It does NOT delete 'supplier', because the Delivery doesn't own it (Takeaway does).

Delivery::~Delivery() {
    std::cout << "  [Delivery destroyed] " << date << " " << description << std::endl;
}

Supplier* Delivery::getSupplier() const { return supplier; }
std::string Delivery::getDate() const { return date; }
std::string Delivery::getDescription() const { return description; }
double Delivery::getCost() const { return cost; }

//  Output operator (friend) 
// supplier->getName() uses the arrow operator because 'supplier' is a pointer.
std::ostream& operator<<(std::ostream& out, const Delivery& d) {
    out << std::fixed << std::setprecision(2)
        << d.date << " | " << d.description
        << " from " << d.supplier->getName()
        << " | GBP " << d.cost;
    return out;
}
