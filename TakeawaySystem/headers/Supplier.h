// A company the takeaway buys stock from (meat, buns, vegetables, oil...).
// Suppliers are stored in the Tree, using their ID as the key.
#pragma once
#include <iostream>
#include <string>    

class Supplier {
private:
    
    int id;                 // unique ID, given out automatically
    std::string name;       // company name
    std::string phone;      // contact number

    // Counter for unique Id generatiion
    static int nextId;

public:
    //CONSTRUCTOR
    Supplier(const std::string& name, const std::string& phone);
    //DESTRUCTOR
    ~Supplier();

    int getId() const;
    std::string getName() const;
    std::string getPhone() const;

    static int getTotalCreated();

    bool operator<(const Supplier& other) const;
    bool operator==(const Supplier& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Supplier& s);
};