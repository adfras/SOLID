

#include "Discount.h"
#include <algorithm> // For std::max

// Adheres to OCP: Encapsulates discount logic, enabling extension to new discount types 
// (e.g., seasonal, bundled discounts) without modifying existing functionality.

// Default constructor
Discount::Discount() : type("none"), value(0.0) {}

// Constructor with parameters
Discount::Discount(const std::string& discountType, double discountValue)
    : type(discountType), value(discountValue) {}

// Apply discount to a price
double Discount::applyDiscount(double originalPrice) const {
    if (type == "flat") {
        return std::max(0.0, originalPrice - value); // Ensure price doesn't go below zero
    } else if (type == "percentage") {
        return std::max(0.0, originalPrice * (1 - value / 100)); // Apply percentage discount
    } else if (type == "none") {
        return originalPrice; // No discount applied
    } else {
        throw std::invalid_argument("Invalid discount type"); // Invalid type
    }
}
