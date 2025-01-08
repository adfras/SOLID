#ifndef REPORT_H
#define REPORT_H

#include <string>

class Report {
public:
    virtual std::string generate() const = 0;
    virtual ~Report() = default;
};

#endif // REPORT_H
