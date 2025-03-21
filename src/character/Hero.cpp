#include "Hero.h"
#include "NPC.h"
#include "Utility.h"
#include "Monster.h"
#include <iostream>
#include <string>

// class NPC;

Hero::Hero(const std::string& name, int health, int attackPower, int defense, QuestManager* qm) 
    : Character(name, health, attackPower, defense) {
        if (health < 0) m_health = 0;
        if (attackPower < 1) m_attackPower = 1;
        if (defense < 0) m_defense = 0;
        m_qm = qm;
    }

Hero::~Hero() {
    delete m_currentMount;
}

void Hero::displayStats() const {
    std::cout << "Name: " << m_name << "| Healt: ";
    Utility::printHealt(m_health);
    std::cout << " | Attack: ";    
    Utility::printAttack(m_attackPower);
    std::cout << " | Defence: ";
    Utility::printDefence(m_defense);
    std::cout << " | Level: " << m_level << " | XP: ";
    Utility::printYell(std::to_string(m_experiencePoints));
    std::cout << std::endl;
}

void Hero::takeDamage(int damage) {
    if (damage < 1) return;
    int finalDamage = damage - m_defense;
    m_health -= finalDamage;
    if (m_health <= 0) {
        m_health = 0;
        std::cout << "Game over! " << m_name << " is died.";
        //gameOver() // function that turn off the game
        return;
    }
    std::cout << m_name << " takes " << finalDamage << " damage!, Healt remaining: ";
    Utility::printHealt(m_health);
    std::cout << std::endl;
}

void Hero::interact(Character* target) {
    if (NPC* npc = dynamic_cast<NPC*>(target)) {
        npc->interact(this); // npc says his dialogue
        std::cout << "1. Accept \n 2. Skip\n";
        int inp = Utility::getValidatedInput(1,2);
        if (inp == 1) {
            std::cout << "Quest accepted!" << std::endl;
            std::cout << npc->getAssociatedQuest()->getDescription() << std::endl;
            m_qm->assignQuest(npc->getAssociatedQuest());
        }
    }
    // to be continued
    //
    //
    // ...
}

void Hero::attack(Character* target) {
    if (!target) {
        std::cout << "There is no one to attack!" << std::endl;
        return;
    }

    target->takeDamage(m_attackPower);
    std::cout << m_name << " attacks " << target->getName() << " for " << m_attackPower << " damage!" << std::endl;
    if (target->getHealt() <= 0) {
        Utility::printBlue(target->getName());
        Utility::printBlue(" is dead!");
        if (dynamic_cast<Monster*>(target)) { this->gainXP(20); }
        return;
    }
    std::cout << target->getName() << "'s healt: "  << target->getHealt() << std::endl;
}


