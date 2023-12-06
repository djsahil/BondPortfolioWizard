#include <cmath>
#include <sstream>
#include "Bond.h"
#include "csviostream.h"

    
#define TREASURYBOND_COUPONFREQUENCY 2

// Implement the constructor
Bond::Bond(
    const std::string& description,
    const std::string& symbol,
    double faceValue,
    double couponRate,
    double yield,
    double maturityYears
) : Security("Bond", symbol, description),
    faceValue_(faceValue),
    couponRate_(couponRate),
    yield_(yield),
    maturityYears_(maturityYears) {

        calculateDV01();
        calculateMacaulaysDurationInYears();
        calculateModifiedDurationInYears();
        calculateConvexity();

    }

double Bond::calculatePriceFromYield(double y) const {

    double cashFlow = 0;
    double discountFactor;
    double weightedCashFlow = 0;
    double PVOfCashFlowsSum = 0;
    for(int i = 1; i <= maturityYears_ * TREASURYBOND_COUPONFREQUENCY; i++) {

       cashFlow = (couponRate_ * faceValue_) / 2;
       if(i == maturityYears_ * TREASURYBOND_COUPONFREQUENCY) {
        cashFlow = cashFlow + faceValue_;
       }

        discountFactor = pow(((1 + (yield_ / TREASURYBOND_COUPONFREQUENCY))),i);
        weightedCashFlow = cashFlow / discountFactor;
        PVOfCashFlowsSum = PVOfCashFlowsSum + weightedCashFlow;

    }
    return PVOfCashFlowsSum;
}

// Implement the calculateValue() function
double Bond::calculateValue() const {
    double cashFlow = 0;
    double discountFactor;
    double weightedCashFlow = 0;
    double PVOfCashFlowsSum = 0;
    for(int i = 1; i <= maturityYears_ * TREASURYBOND_COUPONFREQUENCY; i++) {

       cashFlow = (couponRate_ * faceValue_) / 2;
       if(i == maturityYears_ * TREASURYBOND_COUPONFREQUENCY) {
        cashFlow = cashFlow + faceValue_;
       }


        discountFactor = pow(((1 + (getSpotRate(i/2.0) / TREASURYBOND_COUPONFREQUENCY))),i);
        weightedCashFlow = cashFlow / discountFactor;
        PVOfCashFlowsSum = PVOfCashFlowsSum + weightedCashFlow;

    }
    return PVOfCashFlowsSum;
}

double Bond::calculateDV01() const{
    return calculatePriceFromYield(yield_) - calculatePriceFromYield(yield_ + 0.0001);
}

double Bond::calculateMacaulaysDurationInYears() const{

    double cashFlow = 0;
    double discountFactor;
    double weightedCashFlow = 0;
    double PVOfCashFlowsSum = 0;
    double tTimesPVOfCashFlowsSum;
    for(int i = 1; i <= maturityYears_ * TREASURYBOND_COUPONFREQUENCY; i++) {

       cashFlow = (couponRate_ * faceValue_) / TREASURYBOND_COUPONFREQUENCY;
       if(i == maturityYears_ * TREASURYBOND_COUPONFREQUENCY) {
        cashFlow = cashFlow + faceValue_;
       }

        discountFactor = pow(((1 + (yield_ / TREASURYBOND_COUPONFREQUENCY))),i);
        weightedCashFlow = cashFlow / discountFactor;
        PVOfCashFlowsSum = PVOfCashFlowsSum + weightedCashFlow;
        tTimesPVOfCashFlowsSum = tTimesPVOfCashFlowsSum + (weightedCashFlow * i);

    }

    double macaulaysDurationInHalfYears = tTimesPVOfCashFlowsSum / PVOfCashFlowsSum;
    return macaulaysDurationInHalfYears/2;
}

double Bond::calculateModifiedDurationInYears() const{
    return calculateMacaulaysDurationInYears() / (1.0+yield_);
} 

double Bond::calculateConvexity() const{

    double PVOfCashFlowsSum = 0;
    double discountFactor;
    double tTimesPVOfCashFlowsSum;
    double cashFlow = 0;
    double weightedCashFlow = 0;

    for(int i = 1; i <= maturityYears_ * TREASURYBOND_COUPONFREQUENCY; i++) {

        cashFlow = (couponRate_ * faceValue_) / TREASURYBOND_COUPONFREQUENCY;
        if(i == maturityYears_ * TREASURYBOND_COUPONFREQUENCY) {
            cashFlow = cashFlow + faceValue_;
        }

        discountFactor = pow(((1 + (yield_ / TREASURYBOND_COUPONFREQUENCY))),i);
        weightedCashFlow = cashFlow / discountFactor;
        PVOfCashFlowsSum = PVOfCashFlowsSum + weightedCashFlow;
        tTimesPVOfCashFlowsSum = tTimesPVOfCashFlowsSum + (weightedCashFlow * (i * (i + 1)));
    }

   return tTimesPVOfCashFlowsSum / (PVOfCashFlowsSum * pow(1 + (yield_ / TREASURYBOND_COUPONFREQUENCY),2));

}


double Bond::getFaceValue() const {
    return faceValue_;
}

double Bond::getCouponRate() const {
    return couponRate_;
}

double Bond::getYield() const {
    return yield_;
}

double Bond::getMaturityYears() const {
    return maturityYears_;
}

std::string Bond::toString() const {
    std::ostringstream oss;
    oss << getDescription() << " " << "(" << 100*couponRate_ << "% Coupon/ $" << calculateValue() << " Fair Price) - Trading at " 
        << 100*yield_ << "% Yield to Maturity ($" << calculatePriceFromYield(yield_) << ")" << std::endl;
    
    return oss.str();
}

