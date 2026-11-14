// DailySales.h
// One day's takings, recorded at closing time. Cash and card are kept separate.
// Card payments lose a small fee to the card company.
#pragma once
#include "Transaction.h"

class DailySales : public Transaction {
private:
    double cash;
    double card;
    static const double CARD_FEE_RATE;      // the same fee for every day's card takings

public:
    DailySales(const std::string& date, double cash, double card);
    DailySales(const std::string& date, double cash);      // for a cash-only day

    double getCash() const;
    double getCard() const;
    double getCardFee() const;

    double getEffect() const override;
    void Display() const override;
};