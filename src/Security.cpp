#include <sstream>
#include "Security.h"

Security::Security(const std::string& secType, const std::string& symbol, const std::string& description)
    : secType_(secType), symbol_(symbol), description_(description) {}

std::string Security::getSecType() const {
    return secType_;
}

std::string Security::getSymbol() const {
    return symbol_;
}

std::string Security::getDescription() const {
    return description_;
}

double calculateValue() {
    return 0;
}


