#ifndef INVENTORY_H
#define INVENTORY_H
#include <vector>
#include <iostream>

class Item;

class Inventory {
    private:
        std::vector<std::shared_ptr<Item>> m_items;
    public:
        ~Inventory() {std::cout << "~Inventory" << std::endl;};
        void addItem(std::shared_ptr<Item> item);
        void removeItem(unsigned long index);
        std::shared_ptr<Item> getItem(unsigned long index) const;
        std::vector<std::shared_ptr<Item>> getItems() const;
        int getSize() const;
};
#endif