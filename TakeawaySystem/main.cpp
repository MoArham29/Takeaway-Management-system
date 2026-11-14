// main.cpp
// Step 4 test: the three kinds of transaction, stored together in one linked list.
#include <iostream>
#include <iomanip>
#include "LinkedList.h"
#include "Supplier.h"
#include "StockItem.h"
#include "Transaction.h"
#include "DailySales.h"
#include "Purchase.h"
#include "Expense.h"

int main() {
    std::cout << std::fixed << std::setprecision(2);

    Supplier* meat = new Supplier("Fresh Meats Ltd", "01494 111222");
    Supplier* cleaning = new Supplier("Clean & Pack Ltd", "01494 777888");
    StockItem* chicken = new StockItem("Chicken", "boxes", 15, meat);

    std::cout << "=== Recording transactions ===" << std::endl;
    LinkedList<Transaction*>* statement = new LinkedList<Transaction*>();
    double balance = 3000.00;
    std::cout << "Starting balance: GBP " << balance << std::endl;

    // Each one is stored as a Transaction*, but is really a DailySales, Purchase or Expense
    Transaction* t1 = new DailySales("Mon 07 Dec", 420.50, 680.25);
    Transaction* t2 = new DailySales("Tue 08 Dec", 515.00);                       // cash only
    Transaction* t3 = new Purchase("Wed 09 Dec", meat, chicken, 11, 330.00);
    Transaction* t4 = new Purchase("Wed 09 Dec", cleaning, "Cleaning products", 35.00);
    Transaction* t5 = new Expense("Thu 10 Dec", "Staff wages", 650.00);

    Transaction* all[5] = { t1, t2, t3, t4, t5 };
    for (int i = 0; i < 5; i++) {
        // getEffect() runs the right version for each type: + for sales, - for purchases and expenses
        balance += all[i]->getEffect();
        statement->Insert(new Link<Transaction*>(all[i]->getId(), all[i]));
        std::cout << "  Transaction " << all[i]->getId() << " -> balance GBP " << balance << std::endl;
    }

    std::cout << "\n=== Statement (newest first) ===" << std::endl;
    statement->Display();       // each transaction shows itself in its own way

    std::cout << "\n=== Cleaning up ===" << std::endl;
    delete statement;           // deletes all five transactions
    delete chicken;
    delete cleaning;
    delete meat;
    return 0;
}