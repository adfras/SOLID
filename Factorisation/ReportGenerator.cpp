#include "ReportGenerator.h"
#include <iostream>

ReportGenerator::ReportGenerator(Report& report) : report(report) {}

void ReportGenerator::generateReport() const {
    std::cout << report.generate();
}
