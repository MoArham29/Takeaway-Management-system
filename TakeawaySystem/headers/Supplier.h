// Supplier.h
// A company the takeaway buys stock from. Suppliers are kept in a BinaryTree.
#pragma once
#include <iostream>
#include <string>

class Supplier {
private:
    int id;
    std::string name;
    std::string phone;
    static int nextId;          // shared by all suppliers, so each new one gets the next number

public:
    Supplier(const std::string& name, const std::string& phone);
    ~Supplier();

    int getId() const;
    std::string getName() const;
    std::string getPhone() const;
    void Display() const;

    bool operator==(const Supplier& other) const;     // two suppliers are the same if their numbers match
    friend std::ostream& operator<<(std::ostream& out, const Supplier& s);
};
