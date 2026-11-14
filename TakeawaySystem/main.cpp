// main.cpp
// Runs through two weeks of the takeaway's back office to show every part of the system.
#include <iostream>
#include "Business.h"
#include "ReportCalculator.h"
#include "NotFoundException.h"
#include "InsufficientFundsException.h"
#include "InvalidAmountException.h"

// Records tonight's stock count for all six items, in item-number order
void countStock(Business& shop, int chicken, int beef, int buns, int lettuce, int chips, int oil) {
    shop.recordStockCount(1, chicken);
    shop.recordStockCount(2, beef);
    shop.recordStockCount(3, buns);
    shop.recordStockCount(4, lettuce);
    shop.recordStockCount(5, chips);
    shop.recordStockCount(6, oil);
}

int main() {
    std::cout << "========== SETUP ==========" << std::endl;
    Business shop("Arham's Takeaway", 3000.00);

    shop.addSupplier("Fresh Meats Ltd", "01494 111222");    // supplier 1
    shop.addSupplier("Bun Bakery", "01494 333444");         // supplier 2
    shop.addSupplier("Veg Direct", "01494 555666");         // supplier 3
    shop.addSupplier("Clean & Pack Ltd", "01494 777888");   // supplier 4
    shop.addSupplier("Old Oils Ltd", "01494 999000");       // supplier 5 (removed later)
    shop.printSuppliers();

    shop.addStockItem("Chicken", "boxes", 15, 1);           // item 1
    shop.addStockItem("Beef mince", "boxes", 8, 1);         // item 2
    shop.addStockItem("Burger buns", "packs", 20, 2);       // item 3
    shop.addStockItem("Lettuce", "boxes", 5, 3);            // item 4
    shop.addStockItem("Chips", "bags", 12, 3);              // item 5
    shop.addStockItem("Cooking oil", "drums", 4, 3);        // item 6
    shop.printStock();

    std::cout << "\n========== WEEK 1 ==========" << std::endl;
    shop.startPeriod("Week 1");

    std::cout << "\n--- Mon 07 Dec ---" << std::endl;
    shop.recordSales("Mon 07 Dec", 420.50, 680.25);
    countStock(shop, 10, 6, 14, 4, 9, 3);
    shop.closeDay("Mon 07 Dec");

    std::cout << "\n--- Tue 08 Dec ---" << std::endl;
    shop.recordSales("Tue 08 Dec", 390.00, 710.80);
    countStock(shop, 4, 3, 9, 2, 5, 3);
    shop.closeDay("Tue 08 Dec");

    std::cout << "\n--- Wed 09 Dec (delivery day) ---" << std::endl;
    shop.printOrderList();
    shop.recordPurchase("Wed 09 Dec", 1, 11, 330.00);       // 11 boxes chicken
    shop.recordPurchase("Wed 09 Dec", 2, 5, 120.00);        // 5 boxes beef
    shop.recordPurchase("Wed 09 Dec", 3, 11, 44.00);        // 11 packs buns
    shop.recordPurchase("Wed 09 Dec", 4, 3, 27.00);         // 3 boxes lettuce
    shop.recordPurchase("Wed 09 Dec", 5, 7, 63.00);         // 7 bags chips
    shop.recordPurchase("Wed 09 Dec", 6, 1, 38.00);         // 1 drum oil
    shop.recordPurchase("Wed 09 Dec", 4, "Cleaning products", 35.00);
    shop.printOrderList();
    shop.recordSales("Wed 09 Dec", 515.00);                 // card machine broken: cash only
    countStock(shop, 11, 6, 15, 4, 9, 4);
    shop.closeDay("Wed 09 Dec");

    std::cout << "\n--- Thu 10 Dec ---" << std::endl;
    shop.recordSales("Thu 10 Dec", 365.40, 820.10);
    shop.recordExpense("Thu 10 Dec", "Staff wages", 650.00);
    countStock(shop, 6, 4, 10, 3, 6, 3);
    shop.closeDay("Thu 10 Dec");

    std::cout << "\n--- Things that go wrong ---" << std::endl;
    try {
        shop.recordPurchase("Thu 10 Dec", 1, 50, 9999.00);
    } catch (InsufficientFundsException& e) {
        std::cout << "Error: " << e.what() << " (cost GBP " << e.getCost()
                  << ", balance GBP " << e.getBalance() << ")" << std::endl;
    }
    try {
        shop.findSupplier(99);
    } catch (NotFoundException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    try {
        shop.recordStockCount(1, -3);
    } catch (InvalidAmountException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    try {
        shop.recordSales("Thu 10 Dec", -50.00, 0);
    } catch (std::exception& e) {                           // catches any of our exceptions
        std::cout << "Error: " << e.what() << std::endl;
    }

    Summary week1 = shop.endPeriod();
    std::cout << "\n" << week1 << std::endl;

    std::cout << "\n========== WEEK 2 ==========" << std::endl;
    shop.startPeriod("Week 2");

    std::cout << "\n--- Fri 11 Dec ---" << std::endl;
    shop.recordSales("Fri 11 Dec", 610.00, 1150.75);
    shop.recordExpense("Fri 11 Dec", "Rent", 1200.00);
    countStock(shop, 2, 2, 5, 1, 3, 2);
    shop.closeDay("Fri 11 Dec");

    std::cout << "\n--- Sat 12 Dec (delivery day) ---" << std::endl;
    shop.printOrderList();
    shop.recordPurchase("Sat 12 Dec", 1, 13, 390.00);
    shop.recordPurchase("Sat 12 Dec", 3, 15, 60.00);
    shop.recordSales("Sat 12 Dec", 720.30, 1305.60);
    shop.recordExpense("Sat 12 Dec", "Electricity", 180.00);
    countStock(shop, 8, 1, 12, 1, 2, 2);
    shop.closeDay("Sat 12 Dec");

    Summary week2 = shop.endPeriod();
    std::cout << "\n" << week2 << std::endl;

    std::cout << "\n========== REPORTS ==========" << std::endl;
    Summary bothWeeks = week1 + week2;                      // uses Summary's overloaded +
    std::cout << bothWeeks << std::endl;

    // An array of function pointers: each one points to a different calculation
    Calculation calculations[4] = {
        ReportCalculator::profit,
        ReportCalculator::averageDailyTakings,
        ReportCalculator::lowestBalance,
        ReportCalculator::highestBalance
    };
    std::string titles[4] = { "Profit", "Average daily takings", "Lowest balance", "Highest balance" };
    for (int i = 0; i < 4; i++) {
        ReportCalculator::show(titles[i], calculations[i], bothWeeks);
    }

    std::cout << std::endl;
    shop.printStatement();

    std::cout << std::endl;
    shop.printStock();
    shop.printOrderList();

    std::cout << "\n========== SUPPLIERS ==========" << std::endl;
    Supplier* a = shop.findSupplier(1);
    Supplier* b = shop.findSupplier(2);
    std::cout << "Supplier 1 == Supplier 2? " << (*a == *b ? "yes" : "no") << std::endl;
    std::cout << "Removing supplier 5 (no longer used)" << std::endl;
    shop.removeSupplier(5);
    shop.printSuppliers();

    std::cout << "\n========== END ==========" << std::endl;
    return 0;
}