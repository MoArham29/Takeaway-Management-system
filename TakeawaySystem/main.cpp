// main.cpp
// Step 3 test: suppliers and stock items stored in trees, plus the three exceptions.
#include <iostream>
#include "BinaryTree.h"
#include "Supplier.h"
#include "StockItem.h"
#include "NotFoundException.h"
#include "InsufficientFundsException.h"
#include "InvalidAmountException.h"

// Passed to the stock tree as a function pointer: prints a line if the item needs ordering
void showIfLow(StockItem* item) {
    if (item->amountToOrder() > 0) {
        std::cout << "  " << item->getName() << ": order " << item->amountToOrder()
                  << " " << item->getUnit() << std::endl;
    }
}

int main() {
    std::cout << "=== Suppliers ===" << std::endl;
    BinaryTree<Supplier*>* suppliers = new BinaryTree<Supplier*>();
    Supplier* meat = new Supplier("Fresh Meats Ltd", "01494 111222");
    Supplier* buns = new Supplier("Bun Bakery", "01494 333444");
    suppliers->Insert(meat->getId(), meat);
    suppliers->Insert(buns->getId(), buns);
    suppliers->DisplayInOrder();
    std::cout << "Supplier 1 == Supplier 2? " << (*meat == *buns ? "yes" : "no") << std::endl;

    std::cout << "\n=== Stock (each item starts full) ===" << std::endl;
    BinaryTree<StockItem*>* stock = new BinaryTree<StockItem*>();
    StockItem* chicken = new StockItem("Chicken", "boxes", 15, meat);
    StockItem* rolls = new StockItem("Burger buns", "packs", 20, buns);
    stock->Insert(chicken->getId(), chicken);
    stock->Insert(rolls->getId(), rolls);
    stock->DisplayInOrder();

    std::cout << "\n=== Nightly count, then the order list ===" << std::endl;
    chicken->setQuantity(4);
    rolls->setQuantity(18);
    stock->DisplayInOrder();
    std::cout << "Order list:" << std::endl;
    stock->InOrder(showIfLow);

    std::cout << "\n=== Delivery arrives: chicken += 11 ===" << std::endl;
    *chicken += 11;
    chicken->Display();

    std::cout << "\n=== Exceptions ===" << std::endl;
    try {
        chicken->setQuantity(-2);
    } catch (InvalidAmountException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    try {
        if (suppliers->Find(99) == nullptr) throw NotFoundException("Supplier", 99);
    } catch (NotFoundException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    try {
        throw InsufficientFundsException(5000.00, 1200.50);
    } catch (InsufficientFundsException& e) {
        std::cout << "Error: " << e.what() << " (cost " << e.getCost()
                  << ", balance " << e.getBalance() << ")" << std::endl;
    }

    std::cout << "\n=== Cleaning up ===" << std::endl;
    delete stock;          // stock first, because each item points to a supplier
    delete suppliers;
    return 0;
}// main.cpp
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