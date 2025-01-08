#ifndef PROGRAM_H
#define PROGRAM_H

#include "ProductManager.h"
#include "CustomerManager.h"
#include "Transaction.h"
#include "InventoryUI.h"
#include "PurchaseHistoryFormatter.h"
#include "ReportGenerator.h"

class Program {
public:
    Program(ProductManager& pm, CustomerManager& cm, Transaction& transaction,
            InventoryUI& inventoryUI, PurchaseHistoryFormatter& purchaseHistoryFormatter,
            ReportGenerator& reportGenerator);

    void run();

private:
    ProductManager& productManager;
    CustomerManager& customerManager;
    Transaction& transaction;
    InventoryUI& inventoryUI;
    PurchaseHistoryFormatter& purchaseHistoryFormatter;
    ReportGenerator& reportGenerator;

    void initializeProducts();
    void initializeCustomers();
    void initializeDiscounts();
    void processTransactions();
    void displayInventory();
    void displayPurchaseHistory();
};

#endif // PROGRAM_H
