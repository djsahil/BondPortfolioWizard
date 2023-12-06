#include <iostream>
#include <sstream>
#include <string>
#include "Bond.h"
#include "csviostream.h"
#include "PortfolioManager.h"
#include "Portfolio.h"
#include "prettyprintutils.h"


using namespace std;

PortfolioManager::PortfolioManager(Portfolio& portfolio) : portfolio(portfolio) {}

void PortfolioManager::addBondToPortfolio(const Bond bond, int quantity) {
    portfolio.addBond(bond, quantity);
    printToConsole("*** New Bonds Added to Portfolio! ***");
}

void PortfolioManager::lookupASecurity() {

    string cusip;
    cout << "Enter a Cusip: ";
    cin.ignore();
    getline(cin,cusip);

    if(isInBondsMap(cusip)) {

        int quantity;
        cout << "Long Quantity: ";
        cin >> quantity; 

        addBondToPortfolio(getBondFromCatalog(cusip), quantity);
    } else if(isInZeroCurve(cusip)) {

        int quantity;
        cout << "Long Quantity: ";
        cin >> quantity; 

        addBondToPortfolio(getBondFromZeroCurve(cusip), quantity);
    } else {
        cout << cusip << " - Not a Valid Bond Cusip!\n\n";
    }
}

void PortfolioManager::enterNewPosition() {
    
    int mode{0};
    while(mode != 3) {
        printNewPositionMenu();

        cin >> mode;
        switch(mode) {
            case 1: {
                lookupASecurity();
                break;
            }
            case 2: {

                    double faceValue;
                    double couponRate;
                    double yield;
                    double maturityYears;
                    int quantity;
                    string description;

                    printToConsole("Face Value($): ");
                    cin >> faceValue;
                    printToConsole("Coupon Rate(decimal): ");
                    cin >> couponRate;
                    printToConsole("YTM(decimal): ");
                    cin >> yield;
                    printToConsole("Years to Maturity: ");
                    cin >> maturityYears;
                    printToConsole("Quantity: ");
                    cin >> quantity; 
                    printToConsole("Asset Description: ");
                    cin.ignore();
                    getline(cin,description);

                    // Create a BOND Security
                    Bond bond(description, "N/A", faceValue, couponRate, yield, maturityYears);
                    addBondToPortfolio(bond, quantity);
                    printToConsole(portfolio.toString());

                    break;
            }
            default: {
                break;
            }
        }
    }
}

void PortfolioManager::calculateInterestRateRisk() {

vector<BondAsset> bonds = portfolio.getBonds();

double DV01Sum = 0;
double NotionalSum = 0;
ostringstream oss;
for (BondAsset bond : bonds) {

    double dv01OfThisBond = bond.getBond().calculateDV01();
    DV01Sum += dv01OfThisBond;
    NotionalSum += bond.getQuantity() * bond.getBond().calculateValue();

    //Give overview of interest rate risk exposure on a per-bond basis
    oss << bond.getQuantity() << " X " << bond.getBond().getDescription();
    oss << " - [DV01: " << dv01OfThisBond;
    oss << ", Modified Duration: " << bond.getBond().calculateModifiedDurationInYears();
    oss << ", Convexity: " << bond.getBond().calculateConvexity() << "]\n";
}

double portfolioDuration = 0;
double portfolioConvexity = 0;
for (BondAsset bond : bonds) {

    double thisBondsWeight = bond.getQuantity() * bond.getBond().calculateValue();
    double weightFactor = thisBondsWeight/NotionalSum;

    portfolioDuration += weightFactor * bond.getBond().calculateModifiedDurationInYears();
    portfolioConvexity += weightFactor * bond.getBond().calculateConvexity();
}

//Give overview of interest rate risk exposure for the portfolio as a whole
oss << "\nOverall Interest Rate Risk Exposure - [DV01: " << DV01Sum;
oss << ", Modified Duration: " << portfolioDuration;
oss << ", Convexity: " << portfolioConvexity << "]\n";

printToConsole(oss.str());

}

Portfolio& PortfolioManager::getPortfolio() {
    return portfolio;
}

void PortfolioManager::hedgeInterestRateRisk() {
    printToConsole("\nThe only strategy available for hedging risk right now is Duration Matching.\n");
    printToConsole("AVAILABLE BENCHMARKS FOR HEDGING:\n");
    printToConsole("10-Year Zero-Coupon Bond");
}

 
void PortfolioManager::manage() {

    int mode{0};
    while(mode != 6) {
        printPortfolioManagerMenu();

        cin >> mode;
        switch(mode) {
            case 1: { //VIEW MY PORTFOLIO
                printToConsole(getPortfolio().toString()); break;
            }
            case 2: { //ASSESS INTEREST RATE RISK
                calculateInterestRateRisk(); break;
            }
            case 3: { //HEDGE AGAINST INTEREST RATE MOVEMENTS
                hedgeInterestRateRisk(); break;
            }
            case 4: { //LOOKUP A BOND
                displayBondMap(); break;
            }
            case 5: { //ENTER A POSITION
                enterNewPosition(); break;
            }
            case 6: { //EXIT
                return;
            }
            default: {
                return;
            }
        }
    }
}
