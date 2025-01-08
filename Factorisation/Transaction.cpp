
#include "Transaction.h"
#include <stdexcept>
#include <iostream>

// Constructor
Transaction::Transaction(ProductManager& pm, CustomerManager& cm, const ReceiptFormat& rf)
    : productManager(pm), customerManager(cm), receiptFormat(rf) {}

// Process a purchase
void Transaction::processPurchase(int customer_id, int product_id, int quantity) {
    if (quantity <= 0) {
        throw std::invalid_argument("Quantity must be greater than zero.");
    }

    Product* product = productManager.getProduct(product_id);
    if (product == nullptr) {
        throw std::invalid_argument("Product not found.");
    }

    Customer* customer = customerManager.getCustomer(customer_id);
    if (customer == nullptr) {
        throw std::invalid_argument("Customer not found.");
    }

    if (quantity > product->getQuantity()) {
        throw std::invalid_argument("Insufficient product quantity.");
    }

    double discountedPrice = productManager.getDiscountPrice(product_id);
    double totalCost = discountedPrice * quantity;

    product->updateQuantity(product->getQuantity() - quantity);
    customerManager.addPurchase(customer_id, product->getName(), quantity, totalCost);

    // More descriptive output
    std::cout << "\nTransaction Details:\n";
    std::cout << "  Customer: " << customer->getName() << " (ID: " << customer_id << ")\n";
    std::cout << "  Product: " << product->getName() << " (ID: " << product_id << ")\n";
    std::cout << "  Original Price: $" << std::fixed << std::setprecision(2) << product->getPrice() << "\n"; // Use product->getPrice()
    std::cout << "  Discounted Price: $" << std::fixed << std::setprecision(2) << discountedPrice << "\n";
    std::cout << "  Quantity: " << quantity << "\n";
    std::cout << "  Total Cost: $" << std::fixed << std::setprecision(2) << totalCost << "\n";

    std::cout << receiptFormat.generateReceipt(customer->getName(), product->getName(), quantity, totalCost);
}
