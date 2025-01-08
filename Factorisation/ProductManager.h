

#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include <map>
#include <vector>
#include "Product.h"
#include "Discount.h"

class ProductManager {
private:
    std::map<int, Product*> products;         // Maps product IDs to products
    std::map<int, Discount> productDiscounts; // Maps product IDs to discounts

public:
    // Add a product to the manager
    void addProduct(Product* product);

    // Retrieve a product by ID
    Product* getProduct(int product_id);

    // Retrieve all products
    std::vector<Product*> getAllProducts() const;

    // Set a discount for a product
    void setDiscount(int product_id, const Discount& discount);

    // Get the price of a product after applying its discount
    double getDiscountPrice(int product_id) const;

    // Get products by category
    std::vector<Product*> getProductsByCategory(int category_id) const;

    // Destructor to clean up allocated memory
    ~ProductManager();
};

#endif // PRODUCT_MANAGER_H
