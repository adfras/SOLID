#include "Program.h"
#include <iostream>

Program::Program(ProductManager& pm, CustomerManager& cm, Transaction& transaction,
                 InventoryUI& inventoryUI, PurchaseHistoryFormatter& purchaseHistoryFormatter,
                 ReportGenerator& reportGenerator)
    : productManager(pm), customerManager(cm), transaction(transaction),
      inventoryUI(inventoryUI), purchaseHistoryFormatter(purchaseHistoryFormatter),
      reportGenerator(reportGenerator) {}

void Program::run() {
    std::cout << "\n--- Initializing Program ---\n";
    initializeProducts();
    initializeCustomers();
    initializeDiscounts();

    std::cout << "\n--- Processing Transactions ---\n";
    processTransactions();

    std::cout << "\n--- Displaying Inventory ---\n";
    displayInventory();

    std::cout << "\n--- Displaying Purchase History ---\n";
    displayPurchaseHistory();

    std::cout << "\n--- Generating Reports ---\n";
    reportGenerator.generateReport();

    std::cout << "\n--- Program End ---\n";
}

void Program::initializeProducts() {
    std::cout << "\nInitializing Products...\n";
    
    Category* electronics = new Category(1, "Electronics"); // Create Category first
    Category* accessories = new Category(2, "Accessories");

    Product* laptop = new Product(101, "Laptop", 1500.0, 10, electronics); // Use the Category
    Product* mouse = new Product(102, "Mouse", 25.0, 50, accessories);

    productManager.addProduct(laptop);
    productManager.addProduct(mouse);
}

void Program::initializeCustomers() {
    std::cout << "\nInitializing Customers...\n";
    std::cout << "Adding customers...\n";
    Customer* alice = new Customer(1, "Alice Johnson", "alice.johnson@example.com");
    Customer* bob = new Customer(2, "Bob Smith", "bob.smith@example.com");
    customerManager.addCustomer(alice);
    customerManager.addCustomer(bob);
}

void Program::initializeDiscounts() {
    std::cout << "\nInitializing Discounts...\n";
    std::cout << "Adding discounts...\n";
    Discount percentageDiscount("percentage", 10.0); // 10% discount
    Discount flatDiscount("flat", 5.0); // $5 discount
    productManager.setDiscount(101, percentageDiscount); // Apply to laptop
    productManager.setDiscount(102, flatDiscount);      // Apply to mouse
}

void Program::processTransactions() {
    std::cout << "Processing transactions...\n";
    transaction.processPurchase(1, 101, 2); // Alice buys 2 laptops
    transaction.processPurchase(2, 102, 3); // Bob buys 3 mice
}

void Program::displayInventory() {
    std::cout << "Inventory after transactions:\n";
    inventoryUI.displayInventory(productManager.getAllProducts());
}

void Program::displayPurchaseHistory() {
    std::cout << "\nDisplaying Purchase History...\n";
    std::cout << "Purchase history:\n";
    std::cout << "Alice's history:\n";
    std::string aliceHistory = purchaseHistoryFormatter.formatHistory(customerManager.getPurchaseHistory(1));
    std::cout << aliceHistory;

    std::cout << "Bob's history:\n";
    std::string bobHistory = purchaseHistoryFormatter.formatHistory(customerManager.getPurchaseHistory(2));
    std::cout << bobHistory;
}
