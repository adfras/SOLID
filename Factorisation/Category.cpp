
// Category Class: Represents a product category
// Adheres to OCP: Categories are managed independently, allowing new properties or methods (e.g., description) 
// to be added without altering the rest of the system.
#include "Category.h"

Category::Category(int id, const std::string& name) : category_id(id), category_name(name) {}

int Category::getCategoryId() const { return category_id; }

std::string Category::getName() const { return category_name; }
