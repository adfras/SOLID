#include "InventoryReport.h"
#include <sstream>

InventoryReport::InventoryReport(const ProductManager& productManager) : productManager(productManager) {}

std::string InventoryReport::generate() const {
    std::ostringstream oss;
    oss << "Inventory Report:\n";
    // Logic to generate inventory report using productManager data
    const std::vector<Product*>& products = productManager.getAllProducts();

    if (products.empty()) {
        oss << "No products in inventory.\n";
    } else {
        for (const auto& product : products) {
            oss << "- Product: " << product->getName()
                << ", Price: $" << product->getPrice()
                << ", Quantity: " << product->getQuantity() << "\n";
        }
    }

    return oss.str();
}
