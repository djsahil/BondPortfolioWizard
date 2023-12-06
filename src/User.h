#ifndef USER_H
#define USER_H

#include <string>
#include "Portfolio.h"

class User {
private:
    std::string userId;
    std::string password;
    Portfolio userPortfolio;  // Composition: User has a Portfolio

public:
    // Constructor creates a new Portfolio
    User(const std::string& userId, const std::string& password);

    // Getter functions
    std::string getUserId() const;
    std::string getPassword() const;
    Portfolio getPortfolio() const;

    // Setter functions
    void setUserId(const std::string& newUserId);
    void setPassword(const std::string& newPassword);

    // Method to add bonds to the user's portfolio
    void addBondToPortfolio(const Bond& bond, int quantity);

     // Method to replace the user's portfolio with a new one
    void replacePortfolio(const Portfolio& newPortfolio);
};

#endif // USER_H
