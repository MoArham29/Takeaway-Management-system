// Supplier.cpp
#include "Supplier.h"

int Supplier::nextId = 1;       // the first supplier is number 1

// Each new supplier takes the next number, then the counter goes up by one
Supplier::Supplier(const std::string& name, const std::string& phone)
    : id(nextId++), name(name), phone(phone) {}

Supplier::~Supplier() {
    std::cout << "  [Supplier removed] " << name << std::endl;
}

int Supplier::getId() const { return id; }
std::string Supplier::getName() const { return name; }
std::string Supplier::getPhone() const { return phone; }

void Supplier::Display() const {
    std::cout << "  " << *this << std::endl;
}

bool Supplier::operator==(const Supplier& other) const {
    return id == other.id;
}

// Lets us write: std::cout << supplier;
std::ostream& operator<<(std::ostream& out, const Supplier& s) {
    out << "Supplier " << s.id << ": " << s.name << " (" << s.phone << ")";
    return out;
}