

#include "Product.h"
#include <stdexcept>

// Product Class: Manages product properties
// Adheres to SRP: Handles only the properties and state of a single product.
// Adheres to OCP: The class is extended to associate products with categories. New properties
// or features, like associating multiple categories or additional fields, can be added without
// changing existing logic.

// Constructor
Product::Product(int id, const std::string& name, double price, int quantity, Category* category)
    : product_id(id), product_name(name), product_price(price), product_quantity(quantity), category(category) {}

// Getters
int Product::getProductId() const { 
    return product_id; 
}

std::string Product::getName() const { 
    return product_name; 
}

double Product::getPrice() const { 
    return product_price; 
}

int Product::getQuantity() const { 
    return product_quantity; 
}

Category* Product::getCategory() const { 
    return category; 
}

// Setters
void Product::setCategory(Category* newCategory) { 
    category = newCategory; 
}

// Updates
void Product::updatePrice(double newPrice) {
    if (newPrice >= 0) {
        product_price = newPrice;
    } else {
        throw std::invalid_argument("Invalid price.");
    }
}

void Product::updateQuantity(int newQuantity) {
    if (newQuantity >= 0) {
        product_quantity = newQuantity;
    } else {
        throw std::invalid_argument("Invalid quantity.");
    }
}
