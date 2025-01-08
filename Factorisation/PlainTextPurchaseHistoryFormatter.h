#ifndef PLAIN_TEXT_PURCHASE_HISTORY_FORMATTER_H
#define PLAIN_TEXT_PURCHASE_HISTORY_FORMATTER_H

#include "PurchaseHistoryFormatter.h"

class PlainTextPurchaseHistoryFormatter : public PurchaseHistoryFormatter {
public:
    std::string formatHistory(const std::vector<PurchaseHistory::Purchase>& history) const override;
};

#endif // PLAIN_TEXT_PURCHASE_HISTORY_FORMATTER_H
