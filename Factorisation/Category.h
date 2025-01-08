

#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

class Category {
private:
    int category_id;
    std::string category_name;

public:
    Category(int id, const std::string& name);
    int getCategoryId() const;
    std::string getName() const;
};

#endif // CATEGORY_H
