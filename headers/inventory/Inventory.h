#ifndef INVENTORY_H
#define INVENTORY_H
#include <vector>

class Item;

class Inventory {
    private:
        std::vector<std::shared_ptr<Item>> m_items;
    public:
        void addItem(std::shared_ptr<Item> item);
        void removeItem(int index);
        std::shared_ptr<Item> getItem(int index) const;
        std::vector<std::shared_ptr<Item>> getItems() const;
        int getSize() const;
};
#endif