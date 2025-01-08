

#include "Customer.h"

// Customer Class: Manages customer properties
// Adheres to SRP: Handles only the properties and state of a single customer.

// Constructor
Customer::Customer(int id, const std::string& name, const std::string& email)
    : customer_id(id), customer_name(name), customer_email(email) {}

// Getters
int Customer::getCustomerId() const {
    return customer_id;
}

std::string Customer::getName() const {
    return customer_name;
}

std::string Customer::getEmail() const {
    return customer_email;
}

// Setters (if needed)
void Customer::setName(const std::string& name) {
    customer_name = name;
}

void Customer::setEmail(const std::string& email) {
    customer_email = email;
}
