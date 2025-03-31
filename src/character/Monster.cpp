#include "../../headers/characters/Monster.h"
#include "../../headers/utility/Utility.h"
#include <iostream>


Monster::Monster(const std::string& name, int health, int attackPower, int defense, const Ability& ability) 
    : Character(name, health, attackPower, defense) {
        m_specialAbility = ability;
}

void Monster::displayStats() const {
    std::cout << "Name: " << m_name << "| Healt: ";
    Utility::printHealt(m_health);
    std::cout << " | Attack: ";    
    Utility::printAttack(m_attackPower);
    std::cout << " | Defence: ";
    Utility::printDefence(m_defense);
    std::cout << " | Special Ability: ";
    Utility::printAbility(m_specialAbility);
    std::cout << std::endl;
}

void Monster::useAbility(Character* target) {
    switch (m_specialAbility) {
        case Ability::Regenerate: {
            int heal = 20;
            m_health += heal;
            if (m_health > Limits::MONSTER_MAX_HEALT) m_health = Limits::MONSTER_MAX_HEALT;
            std::cout << m_name << " uses Regenerate and restores " << heal << " health! Health now: " << m_health << "\n";
            break;
        }
        case Ability::FireBreath: {
            int damage = m_attackPower + 5;
            target->takeDamage(damage);
            std::cout << m_name << " uses Fire Breath, dealing " << damage << " damage to " << target->getName() << "!\n";
            break;
        }
        case Ability::BoneSmash: {
            int damage = static_cast<int>(m_attackPower * 1.5);
            target->takeDamage(damage);
            std::cout << m_name << " uses Bone Smash, dealing " << damage << " damage to " << target->getName() << "!\n";
            break;
        }
        default:
            std::cout << m_name << " attempts an unknown ability!\n";
            break;
    }
}

void Monster::takeDamage(int damage) {
 if (damage < 1) return;
    int finalDamage = damage - m_defense;
    if (finalDamage < 0) finalDamage = 0;
    m_health -= finalDamage;
    if (m_health <= 0) {
        m_health = 0;
        Utility::printRed(m_name);
        Utility::printRed(" lost.");
        return;
    }
    std::cout << m_name << ": ";
    Utility::printRed("Taking damage!");
    std::cout << " Remaining health: "; 
    Utility::printHealt(m_health);
    std::cout << std::endl;
}

void Monster::attack(Character* target) {
    if (!target) {
        std::cout << "There is no one to attack!" << std::endl;
        return;
    }
    target->takeDamage(m_attackPower);
    std::cout << m_name << " attacks " << target->getName() << " for " << m_attackPower << " damage!" << std::endl;
}

