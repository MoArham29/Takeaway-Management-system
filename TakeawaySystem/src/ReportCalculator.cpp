// ReportCalculator.cpp
// These functions read Summary's private data, which is allowed because
// Summary has declared ReportCalculator as a friend.
#include "ReportCalculator.h"
#include <iostream>
#include <iomanip>

double ReportCalculator::profit(const Summary& s) {
    return s.totalIn - s.totalOut;
}

double ReportCalculator::averageDailyTakings(const Summary& s) {
    if (s.days == 0) return 0;
    return s.totalIn / s.days;
}

double ReportCalculator::lowestBalance(const Summary& s) {
    if (s.days == 0) return 0;
    double lowest = s.closingBalances[0];
    for (int i = 1; i < s.days; i++) {
        if (s.closingBalances[i] < lowest) lowest = s.closingBalances[i];
    }
    return lowest;
}

double ReportCalculator::highestBalance(const Summary& s) {
    if (s.days == 0) return 0;
    double highest = s.closingBalances[0];
    for (int i = 1; i < s.days; i++) {
        if (s.closingBalances[i] > highest) highest = s.closingBalances[i];
    }
    return highest;
}

// calc(s) runs whichever function the pointer is pointing to
void ReportCalculator::show(const std::string& title, Calculation calc, const Summary& s) {
    std::cout << std::fixed << std::setprecision(2)
              << "  " << title << ": GBP " << calc(s) << std::endl;
}