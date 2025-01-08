#ifndef FACTORING_METHOD_H
#define FACTORING_METHOD_H

#include <vector>

class FactoringMethod {
public:
    // Pure virtual function to be implemented by subclasses
    virtual std::vector<int> factorize(int number) const = 0;
    virtual ~FactoringMethod() = default;
};

#endif // FACTORING_METHOD_H
