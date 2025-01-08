#include "PlainTextPurchaseHistoryFormatter.h"
#include <sstream>
#include <iomanip> // Add this include

std::string PlainTextPurchaseHistoryFormatter::formatHistory(const std::vector<PurchaseHistory::Purchase>& history) const {
    std::ostringstream oss;
    if (history.empty()) {
        oss << "No purchase history found.\n";
    } else {
        for (const auto& purchase : history) {
            oss << "  - Bought " << purchase.quantity << " " << purchase.product_name
                << " for $" << std::fixed << std::setprecision(2) << purchase.total_cost << "\n";
        }
    }
    return oss.str();
}
