

#ifndef INVENTORY_UI_H
#define INVENTORY_UI_H

#include "Product.h"
#include <vector>
#include <iostream>
#include <iomanip>

class InventoryUI {
public:
    static void displayInventory(const std::vector<Product*>& products);
};

#endif // INVENTORY_UI_H
