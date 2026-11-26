// main.cpp
// The interactive back-office system: a menu where you type in suppliers, stock,
// sales, purchases and expenses, and the system keeps track of the balance and stock.
#include <iostream>
#include <string>
#include "Business.h"
#include "ReportCalculator.h"
#include "InsufficientFundsException.h"
#include "Demo.h"

// ---------- Helpers for reading what the user types ----------

// Keeps asking until a whole number is typed
int readInt(const std::string& question) {
    int value;
    while (true) {
        std::cout << question;
        if (std::cin >> value) {
            std::cin.ignore(10000, '\n');       // throw away the rest of the line
            return value;
        }
        std::cout << "  Please type a whole number." << std::endl;
        std::cin.clear();                       // clear the error...
        std::cin.ignore(10000, '\n');           // ...and throw away what was typed
    }
}

// Keeps asking until a number (with or without pence) is typed
double readMoney(const std::string& question) {
    double value;
    while (true) {
        std::cout << question;
        if (std::cin >> value) {
            std::cin.ignore(10000, '\n');
            return value;
        }
        std::cout << "  Please type an amount, e.g. 420.50" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

// Reads a whole line of text, e.g. a name with spaces in it
std::string readText(const std::string& question) {
    std::cout << question;
    std::string text;
    std::getline(std::cin, text);
    return text;
}

// ---------- The menu ----------

void showMenu(const std::string& today, double balance) {
    std::cout << "\n=========================================" << std::endl;
    std::cout << " Today: " << today << "    Balance: GBP " << balance << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << " SUPPLIERS   1. Add supplier" << std::endl;
    std::cout << "             2. List suppliers" << std::endl;
    std::cout << "             3. Remove supplier" << std::endl;
    std::cout << " STOCK       4. Add stock item" << std::endl;
    std::cout << "             5. Record tonight's stock count" << std::endl;
    std::cout << "             6. Show stock" << std::endl;
    std::cout << "             7. Show order list" << std::endl;
    std::cout << " MONEY       8. Record a delivery (stock purchase)" << std::endl;
    std::cout << "             9. Record another purchase" << std::endl;
    std::cout << "            10. Record today's sales" << std::endl;
    std::cout << "            11. Record an expense (rent, wages...)" << std::endl;
    std::cout << "            12. Show statement" << std::endl;
    std::cout << "            13. Find a transaction" << std::endl;
    std::cout << "            14. Undo a transaction (entered by mistake)" << std::endl;
    std::cout << " DAY/WEEK   15. Close the day" << std::endl;
    std::cout << "            16. End the week and show reports" << std::endl;
    std::cout << " OTHER      17. Run the full demo" << std::endl;
    std::cout << "             0. Exit" << std::endl;
}

// Prints the four reports for a summary, choosing each calculation with a function pointer
void showReports(const Summary& s) {
    Calculation calculations[4] = {
        ReportCalculator::profit,
        ReportCalculator::averageDailyTakings,
        ReportCalculator::lowestBalance,
        ReportCalculator::highestBalance
    };
    std::string titles[4] = { "Profit", "Average daily takings", "Lowest balance", "Highest balance" };
    for (int i = 0; i < 4; i++) {
        ReportCalculator::show(titles[i], calculations[i], s);
    }
}

int main() {
    std::cout << "===== TAKEAWAY BACK OFFICE =====" << std::endl;
    // The system is set up for one takeaway: its name and the money it starts with
    Business shop("Arham's Takeaway", 3000.00);
    std::string today = readText("Today's date (e.g. Mon 07 Dec): ");
    int weekNumber = 1;
    shop.startPeriod("Week 1");
    Summary allWeeks("All weeks");      // every finished week is added onto this

    int choice = -1;
    while (choice != 0) {
        showMenu(today, shop.getBalance());
        choice = readInt("Choose an option: ");
        std::cout << std::endl;

        // Any mistake (unknown number, not enough money, negative amount...) is caught below
        try {
            switch (choice) {
            case 1: {
                std::string supplierName = readText("Supplier name: ");
                std::string phone = readText("Phone number: ");
                Supplier* s = shop.addSupplier(supplierName, phone);
                std::cout << "Added: " << *s << std::endl;
                break;
            }
            case 2:
                shop.printSuppliers();
                break;
            case 3: {
                shop.printSuppliers();
                int id = readInt("Supplier number to remove: ");
                if (shop.removeSupplier(id)) {
                    std::cout << "Supplier removed." << std::endl;
                }
                break;
            }
            case 4: {
                shop.printSuppliers();
                std::string itemName = readText("Item name (e.g. Chicken): ");
                std::string unit = readText("Counted in (e.g. boxes): ");
                int full = readInt("Full level after a delivery: ");
                int supplierId = readInt("Supplier number: ");
                StockItem* item = shop.addStockItem(itemName, unit, full, supplierId);
                std::cout << "Added: " << *item << std::endl;
                break;
            }
            case 5: {
                shop.printStock();
                std::cout << "Type each item number and how many are left. Type 0 when finished." << std::endl;
                int id = readInt("Item number: ");
                while (id != 0) {
                    int count = readInt("How many left: ");
                    shop.recordStockCount(id, count);
                    id = readInt("Item number (0 to finish): ");
                }
                std::cout << "Stock count saved." << std::endl;
                break;
            }
            case 6:
                shop.printStock();
                break;
            case 7:
                shop.printOrderList();
                break;
            case 8: {
                shop.printOrderList();
                int id = readInt("Item number delivered: ");
                int quantity = readInt("Quantity delivered: ");
                double cost = readMoney("Total cost (GBP): ");
                int number = shop.recordPurchase(today, id, quantity, cost);
                std::cout << "Delivery saved as transaction #" << number << ". Stock and balance updated." << std::endl;
                break;
            }
            case 9: {
                shop.printSuppliers();
                int supplierId = readInt("Supplier number: ");
                std::string description = readText("What was bought: ");
                double cost = readMoney("Cost (GBP): ");
                int number = shop.recordPurchase(today, supplierId, description, cost);
                std::cout << "Purchase saved as transaction #" << number << "." << std::endl;
                break;
            }
            case 10: {
                double cash = readMoney("Cash takings (GBP): ");
                double card = readMoney("Card takings (GBP, 0 if none): ");
                int number;
                if (card == 0) number = shop.recordSales(today, cash);       // cash-only day
                else number = shop.recordSales(today, cash, card);
                std::cout << "Sales saved as transaction #" << number << "." << std::endl;
                break;
            }
            case 11: {
                std::string category = readText("What is it for (e.g. Rent): ");
                double amount = readMoney("Amount (GBP): ");
                int number = shop.recordExpense(today, category, amount);
                std::cout << "Expense saved as transaction #" << number << "." << std::endl;
                break;
            }
            case 12:
                shop.printStatement();
                break;
            case 13: {
                int id = readInt("Transaction number: ");
                shop.findTransaction(id);
                break;
            }
            case 14: {
                shop.printStatement();
                int id = readInt("Transaction number to undo: ");
                shop.undoTransaction(id);
                break;
            }
            case 15:
                shop.closeDay(today);
                today = readText("Next day's date: ");
                break;
            case 16: {
                Summary week = shop.endPeriod();
                std::cout << week << std::endl;
                showReports(week);
                allWeeks = allWeeks + week;            // uses overloaded + and =
                allWeeks.setLabel("All weeks so far");
                std::cout << "\n" << allWeeks << std::endl;
                showReports(allWeeks);
                weekNumber++;
                shop.startPeriod("Week " + std::to_string(weekNumber));
                break;
            }
            case 17:
                runDemo();
                break;
            case 0:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Please choose a number from the menu." << std::endl;
            }
        } catch (InsufficientFundsException& e) {
            std::cout << "Error: " << e.what() << " (cost GBP " << e.getCost()
                      << ", balance GBP " << e.getBalance() << ")" << std::endl;
        } catch (std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}