#ifndef HERO_H
#define HERO_H
#include "Character.h"
#include "Interactable.h"
#include "Combatable.h"
#include "../inventory/Inventory.h"
#include "Mount.h"
#include <vector>
class Hero : public Character, public Interactable, public Combatable {
    private:
        Inventory inventory;
        std::vector<std::string> skills;
        int experiencePoints;
        int level;
        Mount* currentMount;
    public:
        Hero(const std::string& name, int health, int attackPower, int defense);
        ~Hero();
        void displayStats() const override;
        void takeDamage(int damage) override;
        void interact(Character* target) override;
        std::string getDialogue() const override;
        void attack(Character* target) override;
        void useAbility(Character* target) override;
        void addItem(Item* item);
        void useItem(int index);
        void gainXP(int xp);
        void levelUp();
        void setMount(Mount* mount);
        Mount* getMount() const;
};
#endif