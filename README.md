# SOLID Demo Project

This repository contains a small C++ program demonstrating the five SOLID principles.  
The main example lives in the `Factorisation` directory and exercises all of the principles together.  
Smaller demonstrations for each principle can be found in their own folders.

The principles are:

1. **Single Responsibility** – each class in the `Factorisation` directory handles one focused task. Examples include `Product`, `Customer`, `InventoryUI`, and `Transaction`.
2. **Open/Closed** – behaviour is extended through abstractions without modifying existing classes. `ReceiptFormat` and the new `DiscountStrategy` hierarchy allow new receipt or discount types to be introduced with no changes to the consumers.
3. **Liskov Substitution** – physical and digital products share a base `Product` interface so either can be used where a product is expected.
4. **Interface Segregation** – inventory access is split into reader and writer interfaces so clients depend only on what they use.
5. **Dependency Inversion** – reports obtain products through a `ProductRepository` abstraction, decoupling them from concrete storage.

Demo programs for these principles appear in the `LiskovSubstitutionPrinciple`, `InterfaceSegregationPrinciple` and `DependencyInversionPrinciple` folders using product and inventory examples.

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
