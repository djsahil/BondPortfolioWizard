#include <iostream> 
#include <sstream>
#include <string>
#include "BondAsset.h"
#include "Bond.h"

using namespace std;

BondAsset::BondAsset(const Bond bond, int quantity)
    : bond_(bond), quantity_(quantity) {}

BondAsset::~BondAsset() {
    //delete security_; // Clean up the dynamically allocated Security object
}

const Bond BondAsset::getBond() const {
    return bond_;
}

int BondAsset::getQuantity() const {
    return quantity_;
}

double BondAsset::getNotionalValue() const {
    // Calculate and return the notional value based on the quantity and security value
    return bond_.calculateValue() * quantity_;
}


string BondAsset::toString() const {
    return bond_.toString();
}

