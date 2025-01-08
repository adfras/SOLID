

#include "InventoryUI.h"

// Display inventory
void InventoryUI::displayInventory(const std::vector<Product*>& products) {
    if (products.empty()) {
        std::cout << "Inventory is empty.\n";
        return; // Add a return here to exit early if the inventory is empty
    }

    for (const auto& product : products) {
        if (product == nullptr) {
            std::cerr << "Error: Null product found in inventory.\n";
            continue; // Skip to the next product if a null pointer is found
        }

        std::cout << "Product ID: " << product->getProductId()
                  << ", Name: " << product->getName()
                  << ", Category: ";

        if (product->getCategory() && !product->getCategory()->getName().empty()) {
            std::cout << product->getCategory()->getName();
        } else {
            std::cout << "None";
        }

        std::cout << ", Price: $" << std::fixed << std::setprecision(2) << product->getPrice()
                  << ", Quantity: " << product->getQuantity() << "\n";
    }

    std::cout << "--------------------------\n";
}
