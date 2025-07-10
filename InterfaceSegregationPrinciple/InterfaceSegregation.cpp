#include <iostream>
#include <map>
#include <string>

// Separate interfaces for reading and writing stock
class InventoryReader {
public:
    virtual ~InventoryReader() = default;
    virtual int getQuantity(const std::string& name) const = 0;
};

class InventoryWriter {
public:
    virtual ~InventoryWriter() = default;
    virtual void setQuantity(const std::string& name, int qty) = 0;
};

// Concrete class implementing both interfaces
class InventoryDB : public InventoryReader, public InventoryWriter {
    std::map<std::string, int> stock;
public:
    int getQuantity(const std::string& name) const override {
        auto it = stock.find(name);
        return it == stock.end() ? 0 : it->second;
    }
    void setQuantity(const std::string& name, int qty) override {
        stock[name] = qty;
    }
};

// Client that only reads
class StockReport {
    const InventoryReader& reader;
public:
    explicit StockReport(const InventoryReader& r) : reader(r) {}
    void print(const std::string& name) const {
        std::cout << name << ": " << reader.getQuantity(name) << " units\n";
    }
};

// Client that reads and writes
class RestockService {
    InventoryReader& reader;
    InventoryWriter& writer;
public:
    RestockService(InventoryReader& r, InventoryWriter& w) : reader(r), writer(w) {}
    void restock(const std::string& name, int qty) {
        int current = reader.getQuantity(name);
        writer.setQuantity(name, current + qty);
    }
};

int main() {
    InventoryDB db;
    db.setQuantity("Keyboard", 5);

    StockReport report(db);       // uses only reader
    RestockService restock(db, db); // uses both reader and writer

    report.print("Keyboard");
    restock.restock("Keyboard", 10);
    report.print("Keyboard");
}
