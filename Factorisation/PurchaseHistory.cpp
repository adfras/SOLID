

// PurchaseHistory Class: Tracks purchases for a customer
// Adheres to SRP: Manages only the storage and retrieval of purchase records.

#include "PurchaseHistory.h"

// Add a purchase record
void PurchaseHistory::addPurchase(const std::string& product_name, int quantity, double total_cost) {
    history.push_back({product_name, quantity, total_cost});
}

// Retrieve all purchase records
const std::vector<PurchaseHistory::Purchase>& PurchaseHistory::getHistory() const {
    return history;
}
