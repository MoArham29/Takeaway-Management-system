// ReportCalculator.h
// Works out figures from a Summary, such as profit or average daily sales.
// Each calculation is a separate function, so we can pick one using a function pointer.
#pragma once
#include <string>
#include "Summary.h"

// "Calculation" is a short name for: a pointer to a function that takes a Summary and gives back a number
typedef double (*Calculation)(const Summary&);

class ReportCalculator {
public:
    static double profit(const Summary& s);
    static double averageDailyTakings(const Summary& s);
    static double lowestBalance(const Summary& s);
    static double highestBalance(const Summary& s);

    // Runs whichever calculation it is given and prints the answer
    static void show(const std::string& title, Calculation calc, const Summary& s);
};