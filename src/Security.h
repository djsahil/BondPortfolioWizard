#ifndef SECURITY_H
#define SECURITY_H

#include <string>

class Security {
public:
    Security(const std::string& secType, const std::string& symbol, const std::string& description);

    // Declare the pure virtual function - REPRESENTS THE FAIR VALUE OF A SECURITY
    virtual double calculateValue() const = 0;

    std::string getSecType() const;
    std::string getSymbol() const;
    std::string getDescription() const;

private:
    std::string secType_;
    std::string symbol_; //Cusip or Ticker
    std::string description_;
};

#endif
