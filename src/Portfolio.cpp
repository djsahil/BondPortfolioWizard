#include <iostream>
#include <sstream>
#include <string>
#include "BondAsset.h"
#include "Portfolio.h"
#include "prettyprintutils.h"
#include "Security.h"

using namespace std;

void Portfolio::addBond(const Bond bond, int quantity) {

    //Construct 'BondAsset' Object using Bond
    BondAsset newAsset(bond, quantity);

    //Add to portfolio's vector of BondAssets
    bonds.push_back(newAsset);

}

string Portfolio::toString() {

    if(bonds.empty()) {
        return "No Assets to display at this time! Enter a position to build your Portfolio!\n\n";
    }

    ostringstream oss;
    for (BondAsset bond : bonds) {
        oss << "LONG " << bond.getQuantity() << " X " << bond.getBond().toString();
    }
    return oss.str();
}

vector<BondAsset> Portfolio::getBonds() {
    return bonds;    
}

