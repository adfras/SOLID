#ifndef CUSTOMER_MANAGER_H
#define CUSTOMER_MANAGER_H

#include <map>
#include <vector>
#include <stdexcept>
#include "Customer.h"
#include "PurchaseHistory.h"

class CustomerManager {
private:
    std::map<int, Customer*> customers;                  // Maps customer IDs to Customer objects
    std::map<int, PurchaseHistory> customerPurchases;    // Maps customer IDs to their purchase histories

public:
    // Destructor to clean up allocated memory
    ~CustomerManager();

    // Add a new customer
    void addCustomer(Customer* customer);

    // Retrieve a customer by ID
    Customer* getCustomer(int customer_id) const;

    // Add a purchase record for a customer
    void addPurchase(int customer_id, const std::string& product_name, int quantity, double total_cost);

    // Retrieve the purchase history of a customer
    const std::vector<PurchaseHistory::Purchase>& getPurchaseHistory(int customer_id) const;

    // Retrieve all customers
    const std::map<int, Customer*>& getAllCustomers() const;
};

#endif // CUSTOMER_MANAGER_H
