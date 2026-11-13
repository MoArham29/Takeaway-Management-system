// MenuItem.h
// Something the takeaway sells, e.g. "Cheeseburger", with its sale price
// and what it costs the business to make.
#pragma once

#include <iostream>
#include <string>

class MenuItem {
private:
    // ----- Data members -----
    std::string name;     // item name shown to customers
    double price;         // what the customer pays (GBP)
    double costToMake;    // what the ingredients cost the business (GBP)

public:
    // ----- CONSTRUCTOR OVERLOADING -----
    // Three constructors with the same name but different parameters.
    // The compiler picks the right one from the arguments you pass.
    MenuItem();                                                          // default: placeholder item
    MenuItem(const std::string& name, double price);                    // cost estimated as 35% of price
    MenuItem(const std::string& name, double price, double costToMake); // everything given

    // ----- Getters -----
    std::string getName() const;
    double getPrice() const;
    double getCostToMake() const;

    // Profit made on one sale of this item (price minus cost)
    double getMargin() const;

    // ----- FRIENDSHIP + OPERATOR OVERLOADING -----
    // Lets us write:  std::cout << burger;
    friend std::ostream& operator<<(std::ostream& out, const MenuItem& item);
};