#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

// Product Class: Manages product properties
// Adheres to SRP: Handles only the properties and state of a single product.
class Product {
private:
    int product_id;
    std::string product_name;
    double product_price;
    int product_quantity;

public:
    Product(int id, std::string name, double price, int quantity)
        : product_id(id), product_name(name), product_price(price), product_quantity(quantity) {}

    int getProductId() const { return product_id; }
    std::string getName() const { return product_name; }
    double getPrice() const { return product_price; }
    int getQuantity() const { return product_quantity; }

    void updatePrice(double newPrice) {
        if (newPrice >= 0) {
            product_price = newPrice;
        } else {
            throw std::invalid_argument("Invalid price.");
        }
    }

    void updateQuantity(int newQuantity) {
        if (newQuantity >= 0) {
            product_quantity = newQuantity;
        } else {
            throw std::invalid_argument("Invalid quantity.");
        }
    }
};

// ProductManager Class: Handles product operations
// Adheres to SRP: Focuses only on managing a collection of products (add, update, fetch).
class ProductManager {
private:
    std::map<int, Product*> products;

public:
    void addProduct(Product* product) {
        if (products.find(product->getProductId()) != products.end()) {
            throw std::invalid_argument("Product with this ID already exists.");
        }
        products[product->getProductId()] = product;
    }

    Product* getProduct(int product_id) {
        if (products.find(product_id) == products.end()) {
            throw std::invalid_argument("Product not found with ID: " + std::to_string(product_id));
        }
        return products[product_id];
    }

    std::vector<Product*> getAllProducts() const {
        std::vector<Product*> productList;
        for (const auto& pair : products) {
            productList.push_back(pair.second);
        }
        return productList;
    }
};

// Customer Class: Manages customer properties
// Adheres to SRP: Handles only the properties and state of a single customer.
class Customer {
private:
    int customer_id;
    std::string customer_name;
    std::string customer_email;

public:
    Customer(int id, std::string name, std::string email)
        : customer_id(id), customer_name(name), customer_email(email) {}

    int getCustomerId() const { return customer_id; }
    std::string getName() const { return customer_name; }
    std::string getEmail() const { return customer_email; }
};

// PurchaseHistory Class: Tracks purchases for a customer
// Adheres to SRP: Manages only the storage and retrieval of purchase records.
class PurchaseHistory {
public: // Make the struct accessible outside the class
    struct Purchase {
        std::string product_name;
        int quantity;
        double total_cost;
    };

private:
    std::vector<Purchase> history;

public:
    void addPurchase(const std::string& product_name, int quantity, double total_cost) {
        history.push_back({product_name, quantity, total_cost});
    }

    const std::vector<Purchase>& getHistory() const {
        return history;
    }
};

// CustomerManager Class: Handles customer operations
// Adheres to SRP: Focuses only on managing customers and their purchase histories.
class CustomerManager {
private:
    std::map<int, Customer*> customers;
    std::map<int, PurchaseHistory> customerPurchases;

public:
    void addCustomer(Customer* customer) {
        if (customers.find(customer->getCustomerId()) != customers.end()) {
            throw std::invalid_argument("Customer with this ID already exists.");
        }
        customers[customer->getCustomerId()] = customer;
    }

    Customer* getCustomer(int customer_id) {
        if (customers.find(customer_id) == customers.end()) {
            throw std::invalid_argument("Customer not found.");
        }
        return customers[customer_id];
    }

    void addPurchase(int customer_id, const std::string& product_name, int quantity, double total_cost) {
        customerPurchases[customer_id].addPurchase(product_name, quantity, total_cost);
    }

    const std::vector<PurchaseHistory::Purchase>& getPurchaseHistory(int customer_id) {
        return customerPurchases[customer_id].getHistory();
    }
};

// ReceiptPrinter Class: Handles receipt generation
// Adheres to SRP: Focuses only on generating and printing receipts.
class ReceiptPrinter {
public:
    static void printReceipt(const Customer* customer, const Product* product, int quantity, double total_cost) {
        std::cout << "\n--- Receipt ---\n";
        std::cout << "Customer: " << customer->getName() << "\n";
        std::cout << "Product: " << product->getName() << "\n";
        std::cout << "Quantity: " << quantity << "\n";
        std::cout << "Total Cost: $" << std::fixed << std::setprecision(2) << total_cost << "\n";
        std::cout << "-----------------\n\n";
    }
};

// Transaction Class: Orchestrates transactions
// Adheres to SRP: Focuses only on coordinating product purchases between customers and products.
class Transaction {
private:
    ProductManager& productManager;
    CustomerManager& customerManager;

public:
    Transaction(ProductManager& pm, CustomerManager& cm) : productManager(pm), customerManager(cm) {}

    void processPurchase(int customer_id, int product_id, int quantity) {
        if (quantity <= 0) {
            throw std::invalid_argument("Quantity must be greater than zero.");
        }

        Product* product = productManager.getProduct(product_id);
        Customer* customer = customerManager.getCustomer(customer_id);

        if (quantity > product->getQuantity()) {
            throw std::invalid_argument("Insufficient product quantity.");
        }

        double total_cost = product->getPrice() * quantity;
        product->updateQuantity(product->getQuantity() - quantity);
        customerManager.addPurchase(customer_id, product->getName(), quantity, total_cost);

        ReceiptPrinter::printReceipt(customer, product, quantity, total_cost);
    }
};

// InventoryUI Class: Displays inventory
// Adheres to SRP: Focuses only on displaying product inventory.
class InventoryUI {
public:
    static void displayInventory(const std::vector<Product*>& products) {
        std::cout << "--- Current Inventory ---\n";
        for (const auto& product : products) {
            std::cout << "Product: " << product->getName()
                      << ", Price: $" << std::fixed << std::setprecision(2) << product->getPrice()
                      << ", Quantity: " << product->getQuantity() << "\n";
        }
        std::cout << "--------------------------\n";
    }
};

// Main Function
// Demonstrates the use of SRP-compliant classes.
int main() {
    // Create managers to handle products and customers
    ProductManager productManager;   // Handles all product-related tasks
    CustomerManager customerManager; // Handles all customer-related tasks
    Transaction transaction(productManager, customerManager); // Manages transactions

    // Create and register products
    Product laptop(101, "Laptop", 1500.00, 5);  // Individual product responsibility
    Product mouse(102, "Mouse", 25.00, 50);     // Individual product responsibility
    productManager.addProduct(&laptop);
    productManager.addProduct(&mouse);

    // Create and register customers
    Customer alice(1, "Alice Johnson", "alice.johnson@example.com"); // Individual customer responsibility
    Customer bob(2, "Bob Smith", "bob.smith@example.com");           // Individual customer responsibility
    customerManager.addCustomer(&alice);
    customerManager.addCustomer(&bob);

    try {
        // Process transactions
        transaction.processPurchase(1, 101, 1); // Alice buys 1 Laptop
        transaction.processPurchase(2, 102, 5); // Bob buys 5 Mice
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // New try-catch block to handle invalid product ID
    try {
        std::cout << "\nAttempting to process a purchase with an invalid product ID...\n";
        transaction.processPurchase(1, 999, 1); // Invalid product ID
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

        // Attempt to purchase more than available stock
    try {
        std::cout << "\nAttempting to purchase more than available stock...\n";
        transaction.processPurchase(1, 101, 10); // Alice tries to buy 10 Laptops
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Attempt to process purchase with zero quantity
    try {
        std::cout << "\nAttempting to process purchase with zero quantity...\n";
        transaction.processPurchase(1, 102, 0); // Zero quantity
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Display inventory (handled by InventoryUI)
    std::cout << "\nDisplaying inventory:\n";
    InventoryUI::displayInventory(productManager.getAllProducts()); // Separates display logic

    // View purchase history for each customer
    std::cout << "\nViewing purchase histories:\n";
    const auto& aliceHistory = customerManager.getPurchaseHistory(1); // Managed by CustomerManager
    const auto& bobHistory = customerManager.getPurchaseHistory(2);   // Managed by CustomerManager

    // Display Alice's purchase history
    std::cout << "Alice's Purchases:\n";
    for (const auto& purchase : aliceHistory) {
        std::cout << "- Product: " << purchase.product_name
                  << ", Quantity: " << purchase.quantity
                  << ", Total Cost: $" << std::fixed << std::setprecision(2) << purchase.total_cost << "\n";
    }

    // Display Bob's purchase history
    std::cout << "Bob's Purchases:\n";
    for (const auto& purchase : bobHistory) {
        std::cout << "- Product: " << purchase.product_name
                  << ", Quantity: " << purchase.quantity
                  << ", Total Cost: $" << std::fixed << std::setprecision(2) << purchase.total_cost << "\n";
    }

    return 0;
}
