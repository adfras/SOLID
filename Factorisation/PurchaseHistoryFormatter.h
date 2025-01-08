#ifndef PURCHASE_HISTORY_FORMATTER_H
#define PURCHASE_HISTORY_FORMATTER_H

#include "PurchaseHistory.h"
#include <string>

class PurchaseHistoryFormatter {
public:
    virtual std::string formatHistory(const std::vector<PurchaseHistory::Purchase>& history) const = 0;
    virtual ~PurchaseHistoryFormatter() = default;
};


#endif // PURCHASE_HISTORY_FORMATTER_H
