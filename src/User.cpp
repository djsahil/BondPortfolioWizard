#include "BondAsset.h"
#include "Bond.h"
#include "User.h"
#include "Portfolio.h"
#include <string>
#include "prettyprintutils.h"
#include <iostream>


// Constructor creates a new Portfolio
User::User(const std::string& userId, const std::string& password)
    : userId(userId), 
    password(password), 
    userPortfolio() {}

// Getter functions
std::string User::getUserId() const {
    return userId;
}

std::string User::getPassword() const {
    return password;
}

Portfolio User::getPortfolio() const {
    return userPortfolio;
}

// Setter functions
void User::setUserId(const std::string& newUserId) {
    userId = newUserId;
}

void User::setPassword(const std::string& newPassword) {
    password = newPassword;
}

// Method to add bonds to the user's portfolio
void User::addBondToPortfolio(const Bond& bond, int quantity) {
    userPortfolio.addBond(bond, quantity);
}

// Method to replace the user's portfolio with a new one
void User::replacePortfolio(const Portfolio& newPortfolio) {
    //userPortfolio = newPortfolio;
}
