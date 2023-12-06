#ifndef BOND_H
#define BOND_H

#include "Security.h"  // Include the base class header

class Bond : public Security {

public:
    Bond(const std::string& description, const std::string& symbol, double faceValue, double couponRate, double yield, double maturityYears);

    double calculateValue() const override;     // Implement the virtual function from Security: Fair Value of a Bond
    double calculatePriceFromYield(double y) const;
    double calculateDV01() const;
    double calculateMacaulaysDurationInYears() const;
    double calculateModifiedDurationInYears() const;
    double calculateConvexity() const;

    std::string toString() const;
    double getFaceValue() const;         // Getter for faceValue_
    double getCouponRate() const;        // Getter for couponRate_
    double getYield() const;             // Getter for yield_
    double getMaturityYears() const;     // Getter for maturityYears_


private:

    double faceValue_;
    double couponRate_;
    double yield_;
    double maturityYears_;

};

#endif
