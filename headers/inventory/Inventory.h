#ifndef INVENTORY_H
#define INVENTORY_H
#include <vector>

class Item;

class Inventory {
    private:
        std::vector<Item*> items;
    public:
        Inventory();
        ~Inventory();
        void addItem(Item* item);
        void removeItem(int index);
        Item* getItem(int index) const;
        std::vector<Item*> getItems() const;
        int getSize() const;
};
#endif