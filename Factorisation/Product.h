

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include "Category.h" // Include Category for association

class Product {
private:
    int product_id;
    std::string product_name;
    double product_price;
    int product_quantity;
    Category* category; // Associated category

public:
    // Constructor
    Product(int id, const std::string& name, double price, int quantity, Category* category = nullptr);

    // Getters
    int getProductId() const;
    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;
    Category* getCategory() const;

    // Setters
    void setCategory(Category* newCategory);

    // Updates
    void updatePrice(double newPrice);
    void updateQuantity(int newQuantity);
};

#endif // PRODUCT_H
