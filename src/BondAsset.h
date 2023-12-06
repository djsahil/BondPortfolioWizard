#ifndef BONDASSET_H
#define BONDASSET_H

#include "Bond.h"
#include "Security.h"

class BondAsset {
public:
    BondAsset(const Bond bond, int quantity);
    ~BondAsset(); // Destructor to manage dynamic memory

    const Bond getBond() const; // Getter method for Security
    int getQuantity() const;
    double getNotionalValue() const;

   std::string toString() const;

private:
    const Bond bond_;
    int quantity_;
    double notionalValue_;
};

#endif  // BONDASSET_H
