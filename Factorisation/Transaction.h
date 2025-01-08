

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "ProductManager.h"
#include "CustomerManager.h"
#include "ReceiptFormat.h"

class Transaction {
private:
    ProductManager& productManager;
    CustomerManager& customerManager;
    const ReceiptFormat& receiptFormat;

public:
    Transaction(ProductManager& pm, CustomerManager& cm, const ReceiptFormat& rf);
    void processPurchase(int customer_id, int product_id, int quantity);
};

#endif // TRANSACTION_H
