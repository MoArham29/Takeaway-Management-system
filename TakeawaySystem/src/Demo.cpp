// Demo.cpp
// Runs two weeks of a sample takeaway using its own separate Business.
#include <iostream>
#include "Demo.h"
#include "Business.h"
#include "ReportCalculator.h"
#include "NotFoundException.h"
#include "InsufficientFundsException.h"
#include "InvalidAmountException.h"

// Records tonight's count for every item (the numbers are given in the same order as items[])
void countStock(Business& shop, int items[], int counts[], int howMany) {
    for (int i = 0; i < howMany; i++) {
        shop.recordStockCount(items[i], counts[i]);
    }
}

void runDemo() {
    std::cout << "\n========== DEMO: SETUP ==========" << std::endl;
    Business shop("Demo Takeaway", 3000.00);

    // Keep the numbers the system gives each supplier and item
    int meat     = shop.addSupplier("Fresh Meats Ltd", "01494 111222")->getId();
    int bakery   = shop.addSupplier("Bun Bakery", "01494 333444")->getId();
    int veg      = shop.addSupplier("Veg Direct", "01494 555666")->getId();
    int cleaning = shop.addSupplier("Clean & Pack Ltd", "01494 777888")->getId();
    int oldOils  = shop.addSupplier("Old Oils Ltd", "01494 999000")->getId();
    shop.printSuppliers();

    int items[6];
    items[0] = shop.addStockItem("Chicken", "boxes", 15, meat)->getId();
    items[1] = shop.addStockItem("Beef mince", "boxes", 8, meat)->getId();
    items[2] = shop.addStockItem("Burger buns", "packs", 20, bakery)->getId();
    items[3] = shop.addStockItem("Lettuce", "boxes", 5, veg)->getId();
    items[4] = shop.addStockItem("Chips", "bags", 12, veg)->getId();
    items[5] = shop.addStockItem("Cooking oil", "drums", 4, veg)->getId();
    shop.printStock();

    std::cout << "\n========== WEEK 1 ==========" << std::endl;
    shop.startPeriod("Week 1");

    std::cout << "\n--- Mon 07 Dec ---" << std::endl;
    shop.recordSales("Mon 07 Dec", 420.50, 680.25);
    int mon[6] = { 10, 6, 14, 4, 9, 3 };
    countStock(shop, items, mon, 6);
    shop.closeDay("Mon 07 Dec");

    std::cout << "\n--- Tue 08 Dec ---" << std::endl;
    shop.recordSales("Tue 08 Dec", 390.00, 710.80);
    int tue[6] = { 4, 3, 9, 2, 5, 3 };
    countStock(shop, items, tue, 6);
    shop.closeDay("Tue 08 Dec");

    std::cout << "\n--- Wed 09 Dec (delivery day) ---" << std::endl;
    shop.printOrderList();
    shop.recordPurchase("Wed 09 Dec", items[0], 11, 330.00);
    shop.recordPurchase("Wed 09 Dec", items[1], 5, 120.00);
    shop.recordPurchase("Wed 09 Dec", items[2], 11, 44.00);
    shop.recordPurchase("Wed 09 Dec", items[3], 3, 27.00);
    shop.recordPurchase("Wed 09 Dec", items[4], 7, 63.00);
    shop.recordPurchase("Wed 09 Dec", items[5], 1, 38.00);
    shop.recordPurchase("Wed 09 Dec", cleaning, "Cleaning products", 35.00);
    shop.printOrderList();
    shop.recordSales("Wed 09 Dec", 515.00);                 // card machine broken: cash only
    int wed[6] = { 11, 6, 15, 4, 9, 4 };
    countStock(shop, items, wed, 6);
    shop.closeDay("Wed 09 Dec");

    std::cout << "\n--- Thu 10 Dec ---" << std::endl;
    shop.recordSales("Thu 10 Dec", 365.40, 820.10);
    shop.recordExpense("Thu 10 Dec", "Staff wages", 650.00);
    int thu[6] = { 6, 4, 10, 3, 6, 3 };
    countStock(shop, items, thu, 6);
    shop.closeDay("Thu 10 Dec");

    std::cout << "\n--- Things that go wrong ---" << std::endl;
    try {
        shop.recordPurchase("Thu 10 Dec", items[0], 50, 9999.00);
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
        shop.recordStockCount(items[0], -3);
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
    int fri[6] = { 2, 2, 5, 1, 3, 2 };
    countStock(shop, items, fri, 6);
    shop.closeDay("Fri 11 Dec");

    std::cout << "\n--- Sat 12 Dec (delivery day) ---" << std::endl;
    shop.printOrderList();
    shop.recordPurchase("Sat 12 Dec", items[0], 13, 390.00);
    shop.recordPurchase("Sat 12 Dec", items[2], 15, 60.00);

    // A typing mistake: 60 boxes of beef instead of 6. Find it, undo it, then enter it correctly.
    int mistake = shop.recordPurchase("Sat 12 Dec", items[1], 60, 1440.00);
    std::cout << "Oops, typed 60 instead of 6:" << std::endl;
    shop.findTransaction(mistake);
    shop.undoTransaction(mistake);
    shop.recordPurchase("Sat 12 Dec", items[1], 6, 144.00);
    shop.recordSales("Sat 12 Dec", 720.30, 1305.60);
    shop.recordExpense("Sat 12 Dec", "Electricity", 180.00);
    int sat[6] = { 8, 7, 12, 1, 2, 2 };
    countStock(shop, items, sat, 6);
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
    Supplier* a = shop.findSupplier(meat);
    Supplier* b = shop.findSupplier(bakery);
    std::cout << "Fresh Meats == Bun Bakery? " << (*a == *b ? "yes" : "no") << std::endl;
    std::cout << "Removing Old Oils Ltd (no longer used)" << std::endl;
    shop.removeSupplier(oldOils);
    shop.printSuppliers();

    std::cout << "\n========== END OF DEMO ==========" << std::endl;
}   // the demo Business is destroyed here, so its clean-up messages appear
