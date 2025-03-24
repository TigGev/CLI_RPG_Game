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
        // std::vector<std::string> m_skills;
        int m_experiencePoints;
        int m_level = 1;
        Mount* m_currentMount = nullptr;
        QuestManager* m_qm;

    public:
        Hero(const std::string& name, int health, int attackPower, int defense, QuestManager* qm);
        ~Hero();
        void displayStats() const override;
        void takeDamage(int damage) override;
        void interact(Character* target) override;
        std::string getDialogue() const override;
        void attack(Character* target) override;
        void useAbility(Character* target) override {};
        void addItem(Item* item);
        void useItem(int index);
        void gainXP(int xp);
        void levelUp();
        void setMount(Mount* mount);
        Mount* getMount() const;
        int getInventorySize();
        int getAttacPower();
        int getLevel();
        int getEXP();
};
#endif