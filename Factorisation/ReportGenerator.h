#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include "Report.h"

class ReportGenerator {
public:
    ReportGenerator(Report& report);
    void generateReport() const;

private:
    Report& report;
};

#endif // REPORT_GENERATOR_H
