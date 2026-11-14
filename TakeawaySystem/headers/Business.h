// Business.h
// The takeaway itself. It keeps the money balance, the suppliers, the stock
// and a record of every transaction.
#pragma once
#include <string>
#include "BinaryTree.h"
#include "LinkedList.h"
#include "Supplier.h"
#include "StockItem.h"
#include "Transaction.h"
#include "Summary.h"

class Business {
private:
    std::string name;
    double balance;
    BinaryTree<Supplier*> suppliers;            // found by supplier number
    BinaryTree<StockItem*> stock;               // found by item number
    LinkedList<Transaction*> transactions;      // newest first, like a bank statement
    Summary* currentPeriod;                     // the week being recorded (empty if none)
    static int itemsToOrder;                    // used while building the order list

    void addTransaction(Transaction* t);
    void checkCanAfford(double cost) const;
    static void showOrderLine(StockItem* item); // passed to the stock tree as a function pointer

public:
    Business(const std::string& name, double openingBalance);
    ~Business();

    // Suppliers
    Supplier* addSupplier(const std::string& name, const std::string& phone);
    Supplier* findSupplier(int id) const;
    void removeSupplier(int id);
    void printSuppliers() const;

    // Stock
    StockItem* addStockItem(const std::string& name, const std::string& unit, int fullLevel, int supplierId);
    StockItem* findStockItem(int id) const;
    void recordStockCount(int itemId, int count);
    void printStock() const;
    void printOrderList() const;

    // Money
    void recordSales(const std::string& date, double cash, double card);
    void recordSales(const std::string& date, double cash);
    void recordPurchase(const std::string& date, int itemId, int quantity, double cost);
    void recordPurchase(const std::string& date, int supplierId, const std::string& description, double cost);
    void recordExpense(const std::string& date, const std::string& category, double amount);
    void closeDay(const std::string& date);
    double getBalance() const;
    void printStatement() const;

    // Weekly summaries
    void startPeriod(const std::string& label);
    Summary endPeriod();
};