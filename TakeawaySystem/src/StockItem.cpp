// StockItem.cpp
#include "StockItem.h"
#include "InvalidAmountException.h"

int StockItem::nextId = 1;

// A new item starts fully stocked
StockItem::StockItem(const std::string& name, const std::string& unit, int fullLevel, Supplier* supplier)
    : id(nextId++), name(name), unit(unit), quantity(fullLevel), fullLevel(fullLevel), supplier(supplier) {}

StockItem::~StockItem() {
    std::cout << "  [Stock item removed] " << name << std::endl;
}

int StockItem::getId() const { return id; }
std::string StockItem::getName() const { return name; }
std::string StockItem::getUnit() const { return unit; }
int StockItem::getQuantity() const { return quantity; }
Supplier* StockItem::getSupplier() const { return supplier; }

// A stock count can't be negative
void StockItem::setQuantity(int count) {
    if (count < 0) {
        throw InvalidAmountException("stock count for " + name + " can't be negative");
    }
    quantity = count;
}

// If we are below the full level, order the difference. Otherwise order nothing.
int StockItem::amountToOrder() const {
    if (quantity < fullLevel) {
        return fullLevel - quantity;
    }
    return 0;
}

void StockItem::Display() const {
    std::cout << "  " << *this << std::endl;
}

// Adds delivered stock. Returns the item itself so it can be used again straight away.
StockItem& StockItem::operator+=(int delivered) {
    if (delivered <= 0) {
        throw InvalidAmountException("delivery quantity must be more than 0");
    }
    quantity += delivered;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const StockItem& item) {
    out << "Item " << item.id << ": " << item.name << " - " << item.quantity
        << " of " << item.fullLevel << " " << item.unit
        << " (from " << item.supplier->getName() << ")";
    return out;
}