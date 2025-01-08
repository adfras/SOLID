

#include "ReceiptFormat.h"

// Plain text receipt format
std::string TextReceiptFormat::generateReceipt(const std::string& customerName, const std::string& productName, int quantity, double totalCost) const {
    std::ostringstream receipt;
    receipt << "\n--- Receipt ---\n";
    receipt << "Customer: " << customerName << "\n";
    receipt << "Product: " << productName << "\n";
    receipt << "Quantity: " << quantity << "\n";
    receipt << "Total Cost: $" << std::fixed << std::setprecision(2) << totalCost << "\n";
    receipt << "-----------------\n\n";
    return receipt.str();
}

// HTML receipt format
std::string HTMLReceiptFormat::generateReceipt(const std::string& customerName, const std::string& productName, int quantity, double totalCost) const {
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
