#include <iostream>
#include "Tree.h"
#include "LinkedList.h"
#include "Supplier.h"
#include "MenuItem.h"
#include "Delivery.h"
#include "SupplierNotFoundException.h"
#include "InvalidPaymentException.h"
#include "EmptyReportException.h"

// ----- Functions passed as FUNCTION POINTERS to the data structures -----
void printSupplier(Supplier* s) { std::cout << "  " << *s << std::endl; }
void printDelivery(Delivery* d) { std::cout << "  " << *d << std::endl; }

int main() {
    //Suppliers: created on the heap with 'new', stored in the Tree
    std::cout << "=== 1. Creating suppliers ===" << std::endl;
    Tree<Supplier*> suppliers;
    Supplier* meat = new Supplier("Fresh Meats Ltd", "01494 111222");
    Supplier* buns = new Supplier("Bun Bakery", "01494 333444");
    Supplier* veg  = new Supplier("Veg Direct", "01494 555666");
    suppliers.insert(meat->getId(), meat);
    suppliers.insert(buns->getId(), buns);
    suppliers.insert(veg->getId(), veg);
    std::cout << "Suppliers created (static counter): " << Supplier::getTotalCreated() << std::endl;
    suppliers.inOrder(printSupplier);

    // ----- 2. Operator overloading on Supplier -----
    std::cout << "\n=== 2. Comparing suppliers ===" << std::endl;
    std::cout << "meat < buns? " << (*meat < *buns ? "yes" : "no") << std::endl;
    std::cout << "meat == meat? " << (*meat == *meat ? "yes" : "no") << std::endl;

    // ----- 3. Menu items: three overloaded constructors -----
    std::cout << "\n=== 3. Menu items ===" << std::endl;
    MenuItem blank;                                   // default constructor
    MenuItem chips("Chips", 2.50);                    // name + price
    MenuItem burger("Cheeseburger", 6.99, 2.10);      // name + price + cost
    std::cout << "  " << blank << std::endl;
    std::cout << "  " << chips << std::endl;
    std::cout << "  " << burger << std::endl;

    // ----- 4. Deliveries: point to suppliers, stored in the LinkedList -----
    std::cout << "\n=== 4. Deliveries ===" << std::endl;
    LinkedList<Delivery*> deliveries;
    deliveries.append(new Delivery(meat, "2026-12-01", "20kg beef mince", 145.00));
    deliveries.append(new Delivery(buns, "2026-12-01", "200 brioche buns", 60.00));
    deliveries.append(new Delivery(veg,  "2026-12-02", "Lettuce, tomato, onion", 32.50));
    deliveries.traverse(printDelivery);

    // ----- 5. Exceptions: throw and catch each one -----
    std::cout << "\n=== 5. Exceptions ===" << std::endl;
    try {
        int wanted = 99;
        Supplier* found = suppliers.search(wanted);
        if (found == nullptr) throw SupplierNotFoundException(wanted);
        std::cout << "  Found: " << *found << std::endl;
    } catch (const SupplierNotFoundException& e) {
        std::cout << "  Caught: " << e.what() << std::endl;
    }
    try {
        throw InvalidPaymentException("amount must be more than GBP 0");
    } catch (const std::exception& e) {      // caught through the BASE class
        std::cout << "  Caught: " << e.what() << std::endl;
    }
    try {
        throw EmptyReportException("2026-12-01");
    } catch (const std::exception& e) {
        std::cout << "  Caught: " << e.what() << std::endl;
    }

    // ----- 6. Clean up: every 'new' needs a matching 'delete' -----
    std::cout << "\n=== 6. Cleaning up memory ===" << std::endl;
    for (int i = 0; i < deliveries.size(); i++) delete deliveries.get(i);
    delete meat;
    delete buns;
    delete veg;
    return 0;
}