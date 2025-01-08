

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
private:
    int customer_id;           // Unique ID for the customer
    std::string customer_name; // Name of the customer
    std::string customer_email; // Email address of the customer

public:
    // Constructor
    Customer(int id, const std::string& name, const std::string& email);

    // Getters
    int getCustomerId() const;
    std::string getName() const;
    std::string getEmail() const;

    // Setters (if needed in the future)
    void setName(const std::string& name);
    void setEmail(const std::string& email);
};

#endif // CUSTOMER_H
