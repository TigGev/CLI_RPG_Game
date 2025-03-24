#ifndef MONSTER_H
#define MONSTER_H
#include "Character.h"
#include "Combatable.h"
#include <string>

enum class Ability {None, Regenerate, FireBreath, BoneSmash};

inline bool operator==(Ability lhs, Ability rhs) {
    return static_cast<int>(lhs) == static_cast<int>(rhs);
}


class Monster : public Character, public Combatable {
    private:
        Ability m_specialAbility;
    public:
        Monster(const std::string& name, int health, int attackPower, int defense, const Ability& ability = Ability::None);
        ~Monster() = default;
        void displayStats() const override;
        void takeDamage(int damage) override;
        void attack(Character* target) override;
        void useAbility(Character* target);
};
#endif