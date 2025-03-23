#ifndef MONSTER_H
#define MONSTER_H
#include "Character.h"
#include "Combatable.h"
#include <string>
class Monster : public Character, public Combatable {
    private:
        std::string specialAbility;
    public:
        Monster(const std::string& name, int health, int attackPower, int defense, const std::string& ability);
        ~Monster();
        void displayStats() const override;
        void takeDamage(int damage) override;
        void attack(Character* target) override;
        void useAbility(Character* target);
};
#endif