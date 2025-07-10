

#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <string>
#include <stdexcept>
#include <algorithm>
#include <memory>

// Base strategy interface
class DiscountStrategy {
public:
    virtual ~DiscountStrategy() = default;
    virtual double apply(double originalPrice) const = 0;
};

// No discount strategy
class NoDiscount : public DiscountStrategy {
public:
    double apply(double originalPrice) const override { return originalPrice; }
};

// Flat amount discount
class FlatDiscount : public DiscountStrategy {
    double amount;
public:
    explicit FlatDiscount(double amount) : amount(amount) {}
    double apply(double originalPrice) const override {
        return std::max(0.0, originalPrice - amount);
    }
};

// Percentage based discount
class PercentageDiscount : public DiscountStrategy {
    double percentage;
public:
    explicit PercentageDiscount(double pct) : percentage(pct) {}
    double apply(double originalPrice) const override {
        return std::max(0.0, originalPrice * (1 - percentage / 100));
    }
};

#endif // DISCOUNT_H
