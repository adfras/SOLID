#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <sstream>


// Category Class: Represents a product category
// Adheres to OCP: Categories are managed independently, allowing new properties or methods (e.g., description) 
// to be added without altering the rest of the system.
class Category {
private:
    int category_id;
    std::string category_name;

public:
    Category(int id, const std::string& name) : category_id(id), category_name(name) {}

    int getCategoryId() const { return category_id; }
    std::string getName() const { return category_name; }
};

// Product Class: Manages product properties
// Adheres to SRP: Handles only the properties and state of a single product.
// Adheres to OCP: The class is extended to associate products with categories. New properties
// or features, like associating multiple categories or additional fields, can be added without
// changing existing logic.
class Product {
private:
    int product_id;
    std::string product_name;
    double product_price;
    int product_quantity;
    Category* category; // Associated category

public:
    // Constructor with category parameter
    // OCP Application: The constructor allows products to be associated with a category at creation. 
    // This setup enables the addition of category-related functionality (e.g., filtering, grouping) 
    // without modifying the core product logic.
    Product(int id, const std::string& name, double price, int quantity, Category* category = nullptr)
        : product_id(id), product_name(name), product_price(price), product_quantity(quantity), category(category) {}

    // Getters
    // OCP Application: Getters expose properties of the product in a controlled way, 
    // allowing extensions (e.g., additional calculations or formatting) without altering the core logic.
    int getProductId() const { return product_id; }
    std::string getName() const { return product_name; }
    double getPrice() const { return product_price; }
    int getQuantity() const { return product_quantity; }
    Category* getCategory() const { return category; }

    // Setters
    // OCP Application: Setters like `setCategory` allow new associations with external objects (e.g., 
    // linking a product to a new or additional category) without modifying the rest of the product class.
    void setCategory(Category* newCategory) { category = newCategory; }

    // Updates
    // OCP Application: The `updatePrice` and `updateQuantity` methods are designed to handle updates 
    // without changing how prices or quantities are stored. If additional business rules are needed 
    // (e.g., logging changes or notifying observers), these methods can be extended without altering 
    // the underlying data members or existing functionality.
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

// Discount Class
// Adheres to OCP: Encapsulates discount logic, enabling extension to new discount types 
// (e.g., seasonal, bundled discounts) without modifying existing functionality.
class Discount {
private: 
std::string type; // flat or percentage
double value; //Discount value in dollars or percentage

public:
    // Default constructor required for std::map in productManager
    Discount() : type("none"), value(0.0) {}

    // Constructor with parameters
    Discount(const std::string& discountType, double discountValue)
        : type(discountType), value(discountValue) {}

    // Applies discount
    double applyDiscount(double originalPrice) const {
        if (type == "flat") {
            return std::max(0.0, originalPrice - value);
        } else if (type == "percentage") {
            return std::max(0.0, originalPrice * (1 - value / 100));
        } else {
            throw std::invalid_argument("Invalid discount type");
        } 
    }
};

// ProductManager Class: Handles product operations
// Adheres to SRP: Focuses only on managing a collection of products (add, update, fetch).
// Adheres to OCP: Discount management extended keeping core product functionality unchanged. Now applies discounts dynamically without modifying original product and price logic
// Adheres to OCP: Also extended by filtering by category to allow further functionality to be added without modifying existing methods.
class ProductManager {
private:
    std::map<int, Product*> products; // maps product IDs to products
    std::map<int, Discount> productDiscounts; // maps product IDs to apply dynamic discounts when needed

public:
    // Add a product to the manager
    // OCP Application: The `addProduct` method allows adding new products dynamically. 
    // Future extensions, such as validating product categories or notifying observers upon addition, 
    // can be implemented without changing this method's core functionality.
    void addProduct(Product* product) {
        if (products.find(product->getProductId()) != products.end()) {
            throw std::invalid_argument("Product with this ID already exists.");
        }
        products[product->getProductId()] = product;
    }

    //Retrieved a product for ID
    // OCP Application: This method encapsulates the logic for accessing a product. 
    // Future extensions, such as logging retrievals or adding caching, can be introduced 
    // without altering the core behavior.
    Product* getProduct(int product_id) {
        if (products.find(product_id) == products.end()) {
            throw std::invalid_argument("Product not found with ID: " + std::to_string(product_id));
        }
        return products[product_id];
    }

    // Retrieves all products
    // OCP Application: This method provides access to all products, enabling extensions 
    // such as filtering or sorting before returning the list without changing its core logic.
    std::vector<Product*> getAllProducts() const {
        std::vector<Product*> productList;
        for (const auto& pair : products) {
            productList.push_back(pair.second);
        }
        return productList;
    }

    // Associates a discount with a product using ID
    // OCP Application: Discounts are managed independently of product logic. 
    // Adding new discount types (e.g., time-based discounts or bundled discounts) 
    // can be done by modifying the `Discount` class without altering this method.
    void setDiscount(int product_id, const Discount& discount) {
        if (products.find(product_id) == products.end()) {
            throw std::invalid_argument("Cannot apply discount: Product not found.");
        }
        productDiscounts[product_id] = discount;
    }

    // Gets the price of a product after applying its discount
    // OCP Application: The `getDiscountPrice` method calculates discounts dynamically. 
    // New discounting mechanisms can be added without modifying this method, as the logic 
    // is encapsulated within the `Discount` class.
    double getDiscountPrice(int product_id) const {
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

    // Retrieves products by category
    std::vector<Product*> getProductsByCategory(int category_id) const {
        std::vector<Product*> filteredProducts;
        for (const auto& pair : products) {
            if (pair.second->getCategory() && pair.second->getCategory()->getCategoryId() == category_id) {
                filteredProducts.push_back(pair.second);
            }
        }
        return filteredProducts;
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

// ReceiptFormat interface
// Adhered to OCP: Defines a blueprint for receipt formatting. New formats can be added by creating classes that implement this interface, without modifying existing functionality.
class ReceiptFormat {
    public:
        virtual std::string generateReceipt(const std::string& customerName, const std::string& productName, int quantity, double totalCost) const = 0;
        virtual ~ReceiptFormat() = default; // Virtual destructor for interface
};

// TextReceiptFormat Class
// Adheres to OCP: Implements the ReceiptFormat interface to generate plain text receipts.
class TextReceiptFormat : public ReceiptFormat {
public:
    std::string generateReceipt(const std::string& customerName, 
                                 const std::string& productName, 
                                 int quantity, 
                                 double totalCost) const override {
        std::ostringstream receipt;
        receipt << "\n--- Receipt ---\n";
        receipt << "Customer: " << customerName << "\n";
        receipt << "Product: " << productName << "\n";
        receipt << "Quantity: " << quantity << "\n";
        receipt << "Total Cost: $" << std::fixed << std::setprecision(2) << totalCost << "\n";
        receipt << "-----------------\n\n";
        return receipt.str();
    }
};

// HTMLReceiptFormat Class
// Adheres to OCP: Implements the ReceiptFormat interface to generate HTML receipts.
class HTMLReceiptFormat : public ReceiptFormat {
public:
    std::string generateReceipt(const std::string& customerName, 
                                 const std::string& productName, 
                                 int quantity, 
                                 double totalCost) const override {
        std::ostringstream receipt;
        receipt << "<html>\n<head><title>Receipt</title></head>\n<body>\n";
        receipt << "<h1>Receipt</h1>\n";
        receipt << "<p><strong>Customer:</strong> " << customerName << "</p>\n";
        receipt << "<p><strong>Product:</strong> " << productName << "</p>\n";
        receipt << "<p><strong>Quantity:</strong> " << quantity << "</p>\n";
        receipt << "<p><strong>Total Cost:</strong> $" << std::fixed << std::setprecision(2) << totalCost << "</p>\n";
        receipt << "</body>\n</html>\n";
        return receipt.str();
    }
};

// ReceiptPrinter Class: Handles receipt generation
// Adheres to SRP: Focuses only on generating and printing receipts.
// Adheres to OCP: Refactored to use dependency injection for receipt formatting. Now new receipt formats can be added without modifying this class.
class ReceiptPrinter {
private:
    const ReceiptFormat& receiptFormat; // Dependency injected receipt format

public:
    // Constructor accepts a ReceiptFormat implementation
    ReceiptPrinter(const ReceiptFormat& format) : receiptFormat(format) {}

    // Prints a receipt using the provided ReceiptFormat
    void printReceipt(const Customer* customer, const Product* product, int quantity, double totalCost) const {
        std::string receipt = receiptFormat.generateReceipt(customer->getName(), product->getName(), quantity, totalCost);
        std::cout << receipt;
    }
};

// Transaction Class: Orchestrates transactions
// Adheres to SRP: Focuses only on coordinating product purchases between customers and products.
// Adheres to OCP: Updated to get discounted princes dynamically in ProductManager without altering existing logic for handling quantities or purchases.
// Refactored to use an instance of ReceiptPrinter for receipt generation
class Transaction {
private:
    ProductManager& productManager;
    CustomerManager& customerManager;
    const ReceiptPrinter& receiptPrinter; // Dependency injection for receipt formatting

public:
    // Constructor accepts ReceiptPrinter
    Transaction(ProductManager& pm, CustomerManager& cm, const ReceiptPrinter& rp)
        : productManager(pm), customerManager(cm), receiptPrinter(rp) {}

    // Processes a purchase
    void processPurchase(int customer_id, int product_id, int quantity) {
        if (quantity <= 0) {
            throw std::invalid_argument("Quantity must be greater than zero.");
        }

        Product* product = productManager.getProduct(product_id);
        Customer* customer = customerManager.getCustomer(customer_id);

        if (quantity > product->getQuantity()) {
            throw std::invalid_argument("Insufficient product quantity.");
        }

        double discountedPrice = productManager.getDiscountPrice(product_id);
        double total_cost = discountedPrice * quantity;

        product->updateQuantity(product->getQuantity() - quantity);
        customerManager.addPurchase(customer_id, product->getName(), quantity, total_cost);

        // Print the receipt using the ReceiptPrinter instance
        receiptPrinter.printReceipt(customer, product, quantity, total_cost);
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
// Adheres to OCP: Dynamic assignment of discounts to products via ProductManager without altering the product or transaction logic. 
// Adheres to OCP: Categories are also added as independent objects to allow new categories or features without modifying the product or product manager classes.
// Main Function with Manual Unit Tests
int main() {
    // Step 1: Prompt user to select receipt format
    std::cout << "Select Receipt Format:\n1. Text\n2. HTML\nEnter choice: ";
    int choice;
    std::cin >> choice;

    // Step 2: Create the appropriate receipt format
    ReceiptFormat* selectedFormat;
    if (choice == 2) {
        selectedFormat = new HTMLReceiptFormat();
    } else {
        selectedFormat = new TextReceiptFormat(); // Default to Text
    }

    // Step 3: Create ReceiptPrinter with selected format
    ReceiptPrinter receiptPrinter(*selectedFormat);

    // Step 4: Create managers
    ProductManager productManager;
    CustomerManager customerManager;

    // Step 5: Create Transaction with ReceiptPrinter
    Transaction transaction(productManager, customerManager, receiptPrinter);

    // Step 6: Create categories
    Category electronics(1, "Electronics");
    Category accessories(2, "Accessories");

    // Step 7: Create and register products with categories
    Product laptop(101, "Laptop", 1500.00, 5, &electronics);
    Product mouse(102, "Mouse", 25.00, 50, &accessories);
    productManager.addProduct(&laptop);
    productManager.addProduct(&mouse);

    // Step 8: Create and assign discounts
    Discount flatDiscount("flat", 200.0);              // $200 off
    Discount percentageDiscount("percentage", 15.0);   // 15% off
    productManager.setDiscount(101, flatDiscount);      // Assign to Laptop
    productManager.setDiscount(102, percentageDiscount); // Assign to Mouse

    // Step 9: Create and register customers
    Customer alice(1, "Alice Johnson", "alice.johnson@example.com");
    Customer bob(2, "Bob Smith", "bob.smith@example.com");
    customerManager.addCustomer(&alice);
    customerManager.addCustomer(&bob);

    // Step 10: Display current stock before purchases
    std::cout << "\n--- Current Stock (Before Purchases) ---\n";
    InventoryUI::displayInventory(productManager.getAllProducts());

    // Step 11: Process transactions
    try {
        std::cout << "\n--- Processing Purchases ---\n";
        transaction.processPurchase(1, 101, 1); // Alice buys 1 Laptop
        transaction.processPurchase(2, 102, 5); // Bob buys 5 Mice
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Step 12: Display current stock after purchases
    std::cout << "\n--- Current Stock (After Purchases) ---\n";
    InventoryUI::displayInventory(productManager.getAllProducts());

    // Step 13: Display receipts with discounted prices
    std::cout << "\n--- Discounted Receipts ---\n";
    for (const auto& product : productManager.getAllProducts()) {
        int productId = product->getProductId();
        double discountedPrice = productManager.getDiscountPrice(productId);

        std::ostringstream receipt;
        receipt << "Product: " << product->getName()
                << ", Original Price: $" << std::fixed << std::setprecision(2) << product->getPrice()
                << ", Discounted Price: $" << discountedPrice;

        std::cout << receipt.str() << "\n";
    }

    // Cleanup
    delete selectedFormat;

    return 0;
}
