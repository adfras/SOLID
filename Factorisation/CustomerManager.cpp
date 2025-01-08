#include "CustomerManager.h"

// CustomerManager Class: Handles customer operations
// Adheres to SRP: Focuses only on managing customers and their purchase histories.

// Destructor to clean up allocated memory
CustomerManager::~CustomerManager() {
    for (auto& pair : customers) {
        delete pair.second;
    }
}

// Add a new customer
void CustomerManager::addCustomer(Customer* customer) {
    if (customers.find(customer->getCustomerId()) != customers.end()) {
        throw std::invalid_argument("Customer with this ID already exists.");
    }
    customers[customer->getCustomerId()] = customer;
}

// Retrieve a customer by ID
Customer* CustomerManager::getCustomer(int customer_id) const {
    auto it = customers.find(customer_id);
    if (it == customers.end()) {
        throw std::invalid_argument("Customer not found.");
    }
    return it->second;
}

// Add a purchase record for a customer
void CustomerManager::addPurchase(int customer_id, const std::string& product_name, int quantity, double total_cost) {
    if (customers.find(customer_id) == customers.end()) {
        throw std::invalid_argument("Cannot add purchase: Customer not found.");
    }
    customerPurchases[customer_id].addPurchase(product_name, quantity, total_cost);
}

// Retrieve the purchase history of a customer
const std::vector<PurchaseHistory::Purchase>& CustomerManager::getPurchaseHistory(int customer_id) const {
    if (customerPurchases.find(customer_id) == customerPurchases.end()) {
        throw std::invalid_argument("No purchase history found for this customer.");
    }
    return customerPurchases.at(customer_id).getHistory();
}

// Retrieve all customers
const std::map<int, Customer*>& CustomerManager::getAllCustomers() const {
    return customers;
}
