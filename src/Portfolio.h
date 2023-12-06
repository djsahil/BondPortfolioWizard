#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <string>
#include <vector>
#include "BondAsset.h"
#include "Bond.h"

class Portfolio {
public:
    void addBond(const Bond bond, int quantity);
    std::string toString();
    std::vector<BondAsset> getBonds();

private:
    std::vector<BondAsset> bonds;
};

#endif
