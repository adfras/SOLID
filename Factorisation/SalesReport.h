
#ifndef SALES_REPORT_H
#define SALES_REPORT_H

#include "Report.h"
#include "CustomerManager.h"

class SalesReport : public Report {
public:
    SalesReport(const CustomerManager& customerManager);
    std::string generate() const override;

private:
    const CustomerManager& customerManager;
};

#endif // SALES_REPORT_H

    