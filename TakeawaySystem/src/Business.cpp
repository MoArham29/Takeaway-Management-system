// Business.cpp
#include "Business.h"
#include "DailySales.h"
#include "Purchase.h"
#include "Expense.h"
#include "NotFoundException.h"
#include "InsufficientFundsException.h"
#include "InvalidAmountException.h"
#include <iostream>
#include <iomanip>

int Business::itemsToOrder = 0;

Business::Business(const std::string& name, double openingBalance)
    : name(name), balance(openingBalance), currentPeriod(nullptr) {
    std::cout << std::fixed << std::setprecision(2)
              << name << " opened with a balance of GBP " << balance << std::endl;
}

// The trees and the list delete their own items automatically when the Business is destroyed
Business::~Business() {
    std::cout << "Closing " << name << "..." << std::endl;
    delete currentPeriod;
}

// ---------- Suppliers ----------

Supplier* Business::addSupplier(const std::string& name, const std::string& phone) {
    Supplier* s = new Supplier(name, phone);
    suppliers.Insert(s->getId(), s);
    return s;
}

Supplier* Business::findSupplier(int id) const {
    Supplier* s = suppliers.Find(id);
    if (s == nullptr) {
        throw NotFoundException("Supplier", id);
    }
    return s;
}

// Note: only remove a supplier that no stock item uses
void Business::removeSupplier(int id) {
    if (!suppliers.Delete(id)) {
        throw NotFoundException("Supplier", id);
    }
}

void Business::printSuppliers() const {
    std::cout << "Suppliers (" << suppliers.Count() << "):" << std::endl;
    suppliers.DisplayInOrder();
}

// ---------- Stock ----------

StockItem* Business::addStockItem(const std::string& name, const std::string& unit, int fullLevel, int supplierId) {
    Supplier* s = findSupplier(supplierId);         // throws if the supplier doesn't exist
    StockItem* item = new StockItem(name, unit, fullLevel, s);
    stock.Insert(item->getId(), item);
    return item;
}

StockItem* Business::findStockItem(int id) const {
    StockItem* item = stock.Find(id);
    if (item == nullptr) {
        throw NotFoundException("Stock item", id);
    }
    return item;
}

// The nightly count, done before closing
void Business::recordStockCount(int itemId, int count) {
    findStockItem(itemId)->setQuantity(count);
}

void Business::printStock() const {
    std::cout << "Stock:" << std::endl;
    stock.DisplayInOrder();
}

// Called once for every stock item. Prints a line only if the item needs ordering.
void Business::showOrderLine(StockItem* item) {
    int needed = item->amountToOrder();
    if (needed > 0) {
        std::cout << "  " << item->getName() << ": have " << item->getQuantity()
                  << ", order " << needed << " " << item->getUnit()
                  << " from " << item->getSupplier()->getName() << std::endl;
        itemsToOrder++;
    }
}

// Walks through every stock item, passing showOrderLine in as a function pointer
void Business::printOrderList() const {
    std::cout << "ORDER LIST:" << std::endl;
    itemsToOrder = 0;
    stock.InOrder(showOrderLine);
    if (itemsToOrder == 0) {
        std::cout << "  Nothing to order - all stock is full." << std::endl;
    }
}

// ---------- Money ----------

// Every transaction changes the balance and is added to the statement.
// getEffect() runs the version that belongs to the real type (sales, purchase or expense).
void Business::addTransaction(Transaction* t) {
    double effect = t->getEffect();
    balance += effect;
    transactions.Insert(new Link<Transaction*>(t->getId(), t));
    if (currentPeriod != nullptr) {
        if (effect >= 0) currentPeriod->addMoneyIn(effect);
        else currentPeriod->addMoneyOut(-effect);
    }
}

void Business::checkCanAfford(double cost) const {
    if (cost <= 0) {
        throw InvalidAmountException("a payment must be more than 0");
    }
    if (cost > balance) {
        throw InsufficientFundsException(cost, balance);
    }
}

void Business::recordSales(const std::string& date, double cash, double card) {
    if (cash < 0 || card < 0) {
        throw InvalidAmountException("sales can't be negative");
    }
    addTransaction(new DailySales(date, cash, card));
}

// Cash-only day
void Business::recordSales(const std::string& date, double cash) {
    if (cash < 0) {
        throw InvalidAmountException("sales can't be negative");
    }
    addTransaction(new DailySales(date, cash));
}

// A delivery of stock: money goes down, stock goes up
void Business::recordPurchase(const std::string& date, int itemId, int quantity, double cost) {
    StockItem* item = findStockItem(itemId);
    checkCanAfford(cost);
    *item += quantity;                                  // uses StockItem's overloaded +=
    addTransaction(new Purchase(date, item->getSupplier(), item, quantity, cost));
}

// Something we don't keep count of, e.g. cleaning products
void Business::recordPurchase(const std::string& date, int supplierId, const std::string& description, double cost) {
    Supplier* s = findSupplier(supplierId);
    checkCanAfford(cost);
    addTransaction(new Purchase(date, s, description, cost));
}

void Business::recordExpense(const std::string& date, const std::string& category, double amount) {
    checkCanAfford(amount);
    addTransaction(new Expense(date, category, amount));
}

void Business::closeDay(const std::string& date) {
    std::cout << std::fixed << std::setprecision(2)
              << "Closed " << date << " - balance GBP " << balance << std::endl;
    if (currentPeriod != nullptr) {
        currentPeriod->addClosingBalance(balance);
    }
}

double Business::getBalance() const {
    return balance;
}

void Business::printStatement() const {
    std::cout << "STATEMENT (newest first, " << transactions.Count() << " transactions):" << std::endl;
    transactions.Display();
}

// ---------- Weekly summaries ----------

void Business::startPeriod(const std::string& label) {
    delete currentPeriod;                       // throw away any unfinished period
    currentPeriod = new Summary(label);
}

// Gives back a copy of the finished period, then frees the original
Summary Business::endPeriod() {
    if (currentPeriod == nullptr) {
        throw InvalidAmountException("no period has been started");
    }
    Summary finished = *currentPeriod;          // uses Summary's copy constructor
    delete currentPeriod;
    currentPeriod = nullptr;
    return finished;
}