#include <iostream>
#include <string>

// Base interface for all products
class Product {
public:
    virtual ~Product() = default;
    virtual std::string name() const = 0;
    virtual double price() const = 0;
};

// Extended interface for products that can be shipped
class ShippableProduct : public Product {
public:
    virtual void ship() const = 0;
};

class Book : public ShippableProduct {
    std::string title;
    double unitPrice;
public:
    Book(std::string t, double p) : title(std::move(t)), unitPrice(p) {}
    std::string name() const override { return title; }
    double price() const override { return unitPrice; }
    void ship() const override { std::cout << "Shipping book: " << title << '\n'; }
};

class OnlineCourse : public Product {
    std::string courseName;
    double rate;
public:
    OnlineCourse(std::string n, double r) : courseName(std::move(n)), rate(r) {}
    std::string name() const override { return courseName; }
    double price() const override { return rate; }
};

void printPrice(const Product& p) {
    std::cout << p.name() << " costs $" << p.price() << '\n';
}

void deliver(const ShippableProduct& p) {
    p.ship();
}

int main() {
    Book book("C++ Primer", 45.0);
    OnlineCourse course("SOLID Principles", 100.0);

    printPrice(book);    // Works with any Product
    printPrice(course);

    deliver(book);       // Works with any ShippableProduct
    // deliver(course);  // Compile-time error if uncommented
}
