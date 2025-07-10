# SOLID Demo Project

This repository contains a small C++ program demonstrating the five SOLID principles:

1. **Single Responsibility** – each class in the `Factorisation` directory handles one focused task. Examples include `Product`, `Customer`, `InventoryUI`, and `Transaction`.
2. **Open/Closed** – behaviour is extended through abstractions without modifying existing classes. `ReceiptFormat` and the new `DiscountStrategy` hierarchy allow new receipt or discount types to be introduced with no changes to the consumers.
3. **Liskov Substitution** – objects of `DiscountStrategy` or `ReceiptFormat` derived classes can replace their base classes without side effects.
4. **Interface Segregation** – small interfaces such as `ReceiptFormat`, `PurchaseHistoryFormatter`, and `Report` expose only the operations a client needs.
5. **Dependency Inversion** – high level modules depend on abstractions. `Transaction` uses the `ReceiptFormat` interface, while `ProductManager` stores `DiscountStrategy` objects.

## Building

This project requires a C++17 compiler. To build the main example run:

```bash
g++ -std=c++17 -Wall -Wextra Factorisation/*.cpp -o demo
```

## Running

```
./demo
```

The program initialises some products and customers, processes purchases, prints receipts and generates reports. It demonstrates usage of the classes while remaining compliant with the SOLID principles described above.
