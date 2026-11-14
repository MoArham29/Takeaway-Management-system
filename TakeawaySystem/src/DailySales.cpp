// DailySales.cpp
#include "DailySales.h"
#include <iostream>
#include <iomanip>

const double DailySales::CARD_FEE_RATE = 0.0175;     // 1.75%

// ": Transaction(date)" runs the parent's constructor first, which gives this sale its number
DailySales::DailySales(const std::string& date, double cash, double card)
    : Transaction(date), cash(cash), card(card) {}

// Cash-only day: card is set to 0
DailySales::DailySales(const std::string& date, double cash)
    : Transaction(date), cash(cash), card(0.0) {}

double DailySales::getCash() const { return cash; }
double DailySales::getCard() const { return card; }
double DailySales::getCardFee() const { return card * CARD_FEE_RATE; }

// Money in: cash plus card, minus the card fee
double DailySales::getEffect() const {
    return cash + card - getCardFee();
}

void DailySales::Display() const {
    Transaction::Display();     // number and date first
    std::cout << std::fixed << std::setprecision(2)
              << "SALES     cash GBP " << cash << ", card GBP " << card
              << " (fee GBP " << getCardFee() << ")  +" << getEffect() << std::endl;
}