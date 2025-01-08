// main.cpp
#include "Program.h"
#include "ProductManager.h"
#include "CustomerManager.h"
#include "Transaction.h"
#include "InventoryUI.h"
#include "PurchaseHistoryFormatter.h"
#include "PlainTextPurchaseHistoryFormatter.h"
#include "ReceiptFormat.h"
#include "ReportGenerator.h"
#include "SalesReport.h"
#include "InventoryReport.h"

int main() {
    try {
        // Initialize managers
        ProductManager productManager;
        CustomerManager customerManager;

        // Initialize UI components
        TextReceiptFormat textReceipt;
        InventoryUI inventoryUI;
        PlainTextPurchaseHistoryFormatter purchaseHistoryFormatter;

        // Initialize transaction processing
        Transaction transaction(productManager, customerManager, textReceipt);

        // Initialize reporting
        SalesReport salesReport(customerManager);
        InventoryReport inventoryReport(productManager);
        ReportGenerator reportGenerator(salesReport); // You can change which report is generated here

        // Create and run the program
        Program program(productManager, customerManager, transaction, inventoryUI,
                        purchaseHistoryFormatter, reportGenerator);
        program.run();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
