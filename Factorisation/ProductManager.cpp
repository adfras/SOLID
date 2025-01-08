

#include "ProductManager.h"
#include <stdexcept>
#include <algorithm> // For std::find

// ProductManager Class: Handles product operations
// Adheres to SRP: Focuses only on managing a collection of products (add, update, fetch).
// Adheres to OCP: Discount management extended keeping core product functionality unchanged. Now applies discounts dynamically without modifying original product and price logic
// Adheres to OCP: Also extended by filtering by category to allow further functionality to be added without modifying existing methods.

// Add a product to the manager
void ProductManager::addProduct(Product* product) {
    if (products.find(product->getProductId()) != products.end()) {
        throw std::invalid_argument("Product with this ID already exists.");
    }
    products[product->getProductId()] = product;
}

// Retrieve a product by ID
Product* ProductManager::getProduct(int product_id) {
    auto it = products.find(product_id);
    if (it == products.end()) {
        throw std::invalid_argument("Product not found with ID: " + std::to_string(product_id));
    }
    return it->second;
}

// Retrieve all products
std::vector<Product*> ProductManager::getAllProducts() const {
    std::vector<Product*> productList;
    for (const auto& pair : products) {
        productList.push_back(pair.second);
    }
    return productList;
}

// Set a discount for a product
void ProductManager::setDiscount(int product_id, const Discount& discount) {
    if (products.find(product_id) == products.end()) {
        throw std::invalid_argument("Cannot apply discount: Product not found.");
    }
    productDiscounts[product_id] = discount;
}

// Get the price of a product after applying its discount
double ProductManager::getDiscountPrice(int product_id) const {
    auto productIter = products.find(product_id);
    if (productIter == products.end()) {
        throw std::invalid_argument("Product not found with ID " + std::to_string(product_id));
    }

    const Product* product = productIter->second;
    auto discountIter = productDiscounts.find(product_id);
    if (discountIter != productDiscounts.end()) {
        return discountIter->second.applyDiscount(product->getPrice());
    }
    return product->getPrice(); // No discount
}

// Get products by category
std::vector<Product*> ProductManager::getProductsByCategory(int category_id) const {
    std::vector<Product*> filteredProducts;
    for (const auto& pair : products) {
        if (pair.second->getCategory() && pair.second->getCategory()->getCategoryId() == category_id) {
            filteredProducts.push_back(pair.second);
        }
    }
    return filteredProducts;
}

// Destructor to clean up allocated memory
ProductManager::~ProductManager() {
    for (auto& pair : products) {
        delete pair.second;
    }
}
