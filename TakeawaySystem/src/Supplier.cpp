#include "Supplier.h"

// Starts at 1 so the first supplier gets ID 1.
int Supplier::nextId = 1;

//CONSTRUCTOR 
Supplier::Supplier(const std::string& name, const std::string& phone)
    : id(nextId++), name(name), phone(phone) {
    std::cout << "  [Supplier created] #" << id << " " << this->name << std::endl;
}

// DESTRUCTOR for Deletion
Supplier::~Supplier() {
    std::cout << "  [Supplier destroyed] #" << id << " " << name << std::endl;
}

int Supplier::getId() const { return id; }
std::string Supplier::getName() const { return name; }
std::string Supplier::getPhone() const { return phone; }
int Supplier::getTotalCreated() { return nextId - 1; }
bool Supplier::operator<(const Supplier& other) const { return id < other.id; }
bool Supplier::operator==(const Supplier& other) const { return id == other.id; }

std::ostream& operator<<(std::ostream& out, const Supplier& s) {
    out << "Supplier #" << s.id << ": " << s.name << " (tel " << s.phone << ")";
    return out;
}
