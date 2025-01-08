

#ifndef RECEIPT_FORMAT_H
#define RECEIPT_FORMAT_H

#include <string>
#include <sstream>
#include <iomanip>

// Abstract class for receipt format
class ReceiptFormat {
public:
    virtual std::string generateReceipt(const std::string& customerName, const std::string& productName, int quantity, double totalCost) const = 0;
    virtual ~ReceiptFormat() = default;
};

// Plain text receipt format
class TextReceiptFormat : public ReceiptFormat {
public:
    std::string generateReceipt(const std::string& customerName, const std::string& productName, int quantity, double totalCost) const override;
};

// HTML receipt format
class HTMLReceiptFormat : public ReceiptFormat {
public:
    std::string generateReceipt(const std::string& customerName, const std::string& productName, int quantity, double totalCost) const override;
};

#endif // RECEIPT_FORMAT_H
