// Summary.h
// Totals for a period (for example one week): money in, money out,
// and the closing balance of each day.
// The daily balances are kept in an array that is made bigger when it fills up.
#pragma once
#include <iostream>
#include <string>

class Summary {
private:
    std::string label;          // e.g. "Week 1"
    double totalIn;
    double totalOut;
    double* closingBalances;    // array made with new[], so we must delete[] it ourselves
    int days;                   // how many days are stored
    int capacity;               // how many days fit before the array must grow

public:
    Summary(const std::string& label);
    Summary(const Summary& other);                  // copy constructor: makes its own array
    Summary& operator=(const Summary& other);       // assignment: also makes its own array
    ~Summary();                                     // frees the array

    void addMoneyIn(double amount);
    void addMoneyOut(double amount);
    void addClosingBalance(double balance);

    std::string getLabel() const;
    int getDays() const;

    Summary operator+(const Summary& other) const;  // week1 + week2 gives one combined summary

    friend class ReportCalculator;                  // ReportCalculator can read the private totals
    friend std::ostream& operator<<(std::ostream& out, const Summary& s);
};