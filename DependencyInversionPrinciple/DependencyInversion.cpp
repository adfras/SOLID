#include <iostream>
#include <string>
#include <vector>

// Abstraction for product storage
class ProductRepository {
public:
    virtual ~ProductRepository() = default;
    virtual std::vector<std::string> allProducts() const = 0;
};

// Low-level module using in-memory data
class MemoryRepository : public ProductRepository {
    std::vector<std::string> products{"Keyboard", "Mouse"};
public:
    std::vector<std::string> allProducts() const override {
        return products;
    }
};

// Another low-level module, e.g. a database
class DatabaseRepository : public ProductRepository {
public:
    std::vector<std::string> allProducts() const override {
        return {"DB Laptop", "DB Phone"};
    }
};

// High-level module depends only on the abstraction
class InventoryReport {
    const ProductRepository& repo;
public:
    explicit InventoryReport(const ProductRepository& r) : repo(r) {}
    void print() const {
        for (const auto& name : repo.allProducts()) {
            std::cout << name << '\n';
        }
    }
};

int main() {
    MemoryRepository memRepo;
    DatabaseRepository dbRepo;

    InventoryReport r1(memRepo);
    InventoryReport r2(dbRepo);

    r1.print();
    r2.print();
}
