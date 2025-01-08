      
#ifndef INVENTORY_REPORT_H
#define INVENTORY_REPORT_H

#include "Report.h"
#include "ProductManager.h"

class InventoryReport : public Report {
public:
    InventoryReport(const ProductManager& productManager);
    std::string generate() const override;

private:
    const ProductManager& productManager;
};

#endif // INVENTORY_REPORT_H

    