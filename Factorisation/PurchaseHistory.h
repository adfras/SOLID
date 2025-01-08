

#ifndef PURCHASE_HISTORY_H
#define PURCHASE_HISTORY_H

#include <string>
#include <vector>

class PurchaseHistory {
public:
    struct Purchase {
        std::string product_name; // Name of the product purchased
        int quantity;             // Quantity purchased
        double total_cost;        // Total cost of the purchase
    };

private:
    std::vector<Purchase> history; // Vector to store purchase records

public:
    // Add a purchase record
    void addPurchase(const std::string& product_name, int quantity, double total_cost);

    // Retrieve all purchase records
    const std::vector<Purchase>& getHistory() const;
};

#endif // PURCHASE_HISTORY_H
