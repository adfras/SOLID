// SalesReport.cpp
#include "SalesReport.h"
#include <sstream>

SalesReport::SalesReport(const CustomerManager& customerManager) : customerManager(customerManager) {}

std::string SalesReport::generate() const {
    std::ostringstream oss;
    oss << "Sales Report:\n";
    // Logic to generate sales report using customerManager data
    // (Iterate through customers, get their purchase histories, etc.)
    for (const auto& customerPair : customerManager.getAllCustomers()) {
        int customerId = customerPair.first;
        const Customer* customer = customerPair.second;
        oss << "Customer: " << customer->getName() << " (ID: " << customerId << ")\n";

        try {
            const std::vector<PurchaseHistory::Purchase>& purchases = customerManager.getPurchaseHistory(customerId);
            if (purchases.empty()) {
                oss << "  No purchases found.\n";
            } else {
                for (const auto& purchase : purchases) {
                    oss << "  - Bought " << purchase.quantity << " " << purchase.product_name
                        << " for $" << purchase.total_cost << "\n";
                }
            }
        } catch (const std::exception& e) {
            oss << "  Error retrieving purchase history: " << e.what() << "\n";
        }
    }
    return oss.str();
}
