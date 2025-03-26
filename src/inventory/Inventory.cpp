#include "../../headers/inventory/Inventory.h"
#include "../../headers/inventory/Item.h"
#include "../../headers/utility/Utility.h"

void Inventory::addItem(std::shared_ptr<Item> item) {
    if (!item) {
        Utility::printRed("!Failed to add item. Item unknown.");
        return;
    }
    for (auto itm : m_items) {
        if (itm == item) {
            std::cout << item->getName() << " alredt exists in inventory." << std::endl;
            return;
        }
    }
    m_items.push_back(item);
    std::cout << item->getName() << " successfuly added to inventory." << std::endl;
}

void Inventory::removeItem(int index) {
    if (index < 0 || index >= m_items.size()) {
        Utility::printRed("!Invalid item index.");
        return;
    }    
    m_items.erase(m_items.begin() + index);
    std::cout << "Item has been successfully removed from inventory." << std::endl;
}

std::shared_ptr<Item> Inventory::getItem(int index) const {
    if (index < 0 || index >= m_items.size()) {
        Utility::printRed("!Invalid item index.");
        return nullptr;
    }
    return m_items.at(index);
}

std::vector<std::shared_ptr<Item>> Inventory::getItems() const {return m_items;}

int Inventory::getSize() const {return m_items.size();}
