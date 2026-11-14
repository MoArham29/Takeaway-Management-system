// Summary.cpp
#include "Summary.h"
#include <iomanip>

// Starts with room for 7 days
Summary::Summary(const std::string& label)
    : label(label), totalIn(0), totalOut(0), days(0), capacity(7) {
    closingBalances = new double[capacity];
}

// Copy: make a NEW array and copy the numbers across (a "deep copy"),
// so the two summaries never share the same array.
Summary::Summary(const Summary& other)
    : label(other.label), totalIn(other.totalIn), totalOut(other.totalOut),
      days(other.days), capacity(other.capacity) {
    closingBalances = new double[capacity];
    for (int i = 0; i < days; i++) {
        closingBalances[i] = other.closingBalances[i];
    }
}

// Assignment: throw away our old array, then deep copy the other one
Summary& Summary::operator=(const Summary& other) {
    if (this != &other) {               // do nothing if assigning to itself
        delete[] closingBalances;
        label = other.label;
        totalIn = other.totalIn;
        totalOut = other.totalOut;
        days = other.days;
        capacity = other.capacity;
        closingBalances = new double[capacity];
        for (int i = 0; i < days; i++) {
            closingBalances[i] = other.closingBalances[i];
        }
    }
    return *this;
}

Summary::~Summary() {
    delete[] closingBalances;
}

void Summary::addMoneyIn(double amount) { totalIn += amount; }
void Summary::addMoneyOut(double amount) { totalOut += amount; }

// If the array is full, make one twice as big, copy everything over, and free the old one
void Summary::addClosingBalance(double balance) {
    if (days == capacity) {
        capacity = capacity * 2;
        double* bigger = new double[capacity];
        for (int i = 0; i < days; i++) {
            bigger[i] = closingBalances[i];
        }
        delete[] closingBalances;
        closingBalances = bigger;
    }
    closingBalances[days] = balance;
    days++;
}

std::string Summary::getLabel() const { return label; }
int Summary::getDays() const { return days; }

// Adds two periods together: totals are added and the daily balances are joined
Summary Summary::operator+(const Summary& other) const {
    Summary result(label + " + " + other.label);
    result.totalIn = totalIn + other.totalIn;
    result.totalOut = totalOut + other.totalOut;
    for (int i = 0; i < days; i++) {
        result.addClosingBalance(closingBalances[i]);
    }
    for (int i = 0; i < other.days; i++) {
        result.addClosingBalance(other.closingBalances[i]);
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const Summary& s) {
    out << std::fixed << std::setprecision(2)
        << "--- " << s.label << " (" << s.days << " days) ---\n"
        << "  Money in:  GBP " << s.totalIn << "\n"
        << "  Money out: GBP " << s.totalOut << "\n"
        << "  Closing balance each day:";
    for (int i = 0; i < s.days; i++) {
        out << " " << s.closingBalances[i];
    }
    return out;
}