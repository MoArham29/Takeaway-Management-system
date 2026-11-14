// main.cpp
// Step 6 test: the Business class ties everything together.
#include <iostream>
#include "Business.h"
#include "NotFoundException.h"
#include "InsufficientFundsException.h"

int main() {
    Business shop("Arham's Takeaway", 1000.00);

    shop.addSupplier("Fresh Meats Ltd", "01494 111222");      // supplier 1
    shop.addSupplier("Clean & Pack Ltd", "01494 777888");     // supplier 2
    shop.addStockItem("Chicken", "boxes", 15, 1);             // item 1
    shop.addStockItem("Beef mince", "boxes", 8, 1);           // item 2
    shop.printSuppliers();
    shop.printStock();

    shop.startPeriod("Test week");

    std::cout << "\n--- Day 1 ---" << std::endl;
    shop.recordSales("Mon 07 Dec", 400.00, 600.00);
    shop.recordStockCount(1, 4);
    shop.recordStockCount(2, 8);
    shop.closeDay("Mon 07 Dec");

    std::cout << "\n--- Day 2 (delivery) ---" << std::endl;
    shop.printOrderList();
    shop.recordPurchase("Tue 08 Dec", 1, 11, 330.00);         // 11 boxes chicken
    shop.recordPurchase("Tue 08 Dec", 2, "Cleaning products", 35.00);
    shop.recordExpense("Tue 08 Dec", "Staff wages", 500.00);
    shop.printOrderList();
    shop.closeDay("Tue 08 Dec");

    std::cout << "\n--- Errors ---" << std::endl;
    try {
        shop.recordExpense("Tue 08 Dec", "Rent", 5000.00);
    } catch (InsufficientFundsException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    try {
        shop.findStockItem(42);
    } catch (NotFoundException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl;
    Summary week = shop.endPeriod();
    std::cout << week << std::endl;

    std::cout << std::endl;
    shop.printStatement();
    std::cout << std::endl;
    return 0;
}
