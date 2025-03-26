#ifndef HERO_H
#define HERO_H
#include "Character.h"
#include "Interactable.h"
#include "Combatable.h"
#include "../inventory/Inventory.h"
#include "../moving/Mount.h"
#include "../quests/QuestManager.h"
#include <vector>

class Hero : public Character, public Interactable, public Combatable {
    private:
        Inventory m_inventory;
        int m_experiencePoints;
        int m_level = 1;
        Mount* m_currentMount = nullptr;
        QuestManager m_qm; 

    public:
        Hero(const std::string& name, int health, int attackPower, int defense, QuestManager qm);
        ~Hero()  {std::cout << "~Hero" << std::endl;}
        void displayStats() const override;
        void takeDamage(int damage) override;
        void interact(Character* target) override;
        std::string getDialogue() const override;
        void attack(Character* target) override;
        void useAbility(Character* target) override;
        void addItem(std::shared_ptr<Item> item);
        void useItem(int index);
        void gainXP(int xp);
        void levelUp();
        void setMount(Mount* mount);
        std::vector<std::shared_ptr<Item>> getItems();
        Mount* getMount() const;
        std::vector<std::shared_ptr<Quest>> getActiveQuests();
        Inventory& getInventory();
        int getInventorySize();
        int getAttacPower();
        int getLevel();
        int getEXP();
};
#endif