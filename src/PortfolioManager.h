#ifndef PORTFOLIOMANAGER_H
#define PORTFOLIOMANAGER_H

#include "Bond.h"      // Include the Bond header to work with Bond objects
#include "Portfolio.h" // Include the Portfolio header to work with Portfolio objects

class PortfolioManager {
public:
    PortfolioManager(Portfolio& portfolio);

    void addBondToPortfolio(const Bond bond, int quantity);
    void lookupASecurity();
    void enterNewPosition();
    void calculateInterestRateRisk();
    void hedgeInterestRateRisk();
    Portfolio& getPortfolio(); // Accessor for portfolio
    void manage();

private:
    Portfolio& portfolio;
};

#endif
