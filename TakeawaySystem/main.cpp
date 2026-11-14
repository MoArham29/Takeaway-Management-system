// main.cpp
// Step 5 test: weekly summaries, adding two weeks together, and reports chosen by function pointer.
#include <iostream>
#include <string>
#include "Summary.h"
#include "ReportCalculator.h"

int main() {
    std::cout << "=== Week 1 ===" << std::endl;
    Summary week1("Week 1");
    week1.addMoneyIn(1088.85);    week1.addClosingBalance(4088.85);
    week1.addMoneyIn(1088.36);    week1.addClosingBalance(5177.21);
    week1.addMoneyOut(657.00);    week1.addMoneyIn(515.00);   week1.addClosingBalance(5035.21);
    week1.addMoneyIn(1171.15);    week1.addMoneyOut(650.00);  week1.addClosingBalance(5556.35);
    std::cout << week1 << std::endl;

    std::cout << "\n=== Week 2 ===" << std::endl;
    Summary week2("Week 2");
    week2.addMoneyIn(1740.61);    week2.addMoneyOut(1200.00); week2.addClosingBalance(6096.97);
    week2.addMoneyIn(2003.05);    week2.addMoneyOut(630.00);  week2.addClosingBalance(7470.02);
    std::cout << week2 << std::endl;

    std::cout << "\n=== Copy (deep copy test) ===" << std::endl;
    Summary copyOfWeek1 = week1;              // copy constructor makes its own array
    copyOfWeek1.addClosingBalance(9999.99);   // changing the copy...
    std::cout << "Copy has " << copyOfWeek1.getDays() << " days, original still has "
              << week1.getDays() << " days" << std::endl;   // ...does not change the original

    std::cout << "\n=== Week 1 + Week 2 ===" << std::endl;
    Summary bothWeeks = week1 + week2;        // overloaded +
    std::cout << bothWeeks << std::endl;

    std::cout << "\n=== Reports (each picked with a function pointer) ===" << std::endl;
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
    return 0;
}