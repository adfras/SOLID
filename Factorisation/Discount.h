

#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <string>
#include <stdexcept>

class Discount {
private:
    std::string type; // "flat" or "percentage"
    double value;     // Discount value in dollars or percentage

public:
    // Constructors
    Discount();
    Discount(const std::string& discountType, double discountValue);

    // Apply discount to a price
    double applyDiscount(double originalPrice) const;
};

#endif // DISCOUNT_H
