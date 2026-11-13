// MenuItem.cpp
// Implementation of the MenuItem class.
#include "MenuItem.h"
#include <iomanip>   // for std::fixed and std::setprecision (show money with 2 decimals)

// ----- CONSTRUCTOR 1: default -----
// Used when no details are given, e.g.  MenuItem blank;
MenuItem::MenuItem() : name("Unnamed item"), price(0.0), costToMake(0.0) {}

// ----- CONSTRUCTOR 2: name and price -----
// Cost isn't known, so we estimate it at 35% of the price.
MenuItem::MenuItem(const std::string& name, double price)
    : name(name), price(price), costToMake(price * 0.35) {}

// ----- CONSTRUCTOR 3: name, price and cost -----
MenuItem::MenuItem(const std::string& name, double price, double costToMake)
    : name(name), price(price), costToMake(costToMake) {}

// ----- Getters -----
std::string MenuItem::getName() const { return name; }
double MenuItem::getPrice() const { return price; }
double MenuItem::getCostToMake() const { return costToMake; }

// ----- Margin: profit per item -----
double MenuItem::getMargin() const { return price - costToMake; }

// ----- Output operator (friend) -----
std::ostream& operator<<(std::ostream& out, const MenuItem& item) {
    out << std::fixed << std::setprecision(2)
        << item.name << " - price GBP " << item.price
        << ", cost GBP " << item.costToMake
        << ", margin GBP " << item.getMargin();
    return out;
}