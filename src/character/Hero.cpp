#include "../../headers/characters/Hero.h"
#include "../../headers/characters/NPC.h"
#include "../../headers/utility/Utility.h"
#include "../../headers/characters/Monster.h"
#include "../../headers/inventory/Item.h"
#include <iostream>
#include <string>

// class NPC;

Hero::Hero(const std::string& name, int health, int attackPower, int defense, QuestManager qm) 
    : Character(name, health, attackPower, defense) {
        m_level = 1;
        m_experiencePoints = Limits::HERO_PRIM_XP;
        if (health < 0) m_health = 0;
        if (attackPower < 1) m_attackPower = 1;
        if (defense < 0) m_defense = 0;
        m_qm = qm;
    }

void Hero::displayStats() const {
    std::cout << "Name: " << m_name << " | Healt: ";
    Utility::printHealt(m_health);
    std::cout << " | Attack: ";    
    Utility::printAttack(m_attackPower);
    std::cout << " | Defence: ";
    Utility::printDefence(m_defense);
    std::cout << " | Level: " << m_level << " | XP: ";
    Utility::printYell(std::to_string(m_experiencePoints));
    std::cout << std::endl;
}

void Hero::useAbility(Character* target) {
    m_attackPower += 10;
    attack(target);
    m_attackPower -= 10;
}


void Hero::takeDamage(int damage) {
    if (damage < 1) return;
    int finalDamage = damage - m_defense;
    if (finalDamage < 0) finalDamage = 0;
    m_health -= finalDamage;
    if (m_health <= 0) {
        m_health = 0;
        std::cout << "Game over! " << m_name << " is died.\n";
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
            m_qm.assignQuest(npc->getAssociatedQuest());
        }
    }
    // to be continued
    //
    //
    // ...
}

std::vector<std::shared_ptr<Quest>> Hero::getActiveQuests() {return m_qm.getActiveQuests();}


void Hero::attack(Character* target) {
    if (!target) {
        std::cout << "There is no one to attack!" << std::endl;
        return;
    }

    target->takeDamage(m_attackPower);
    std::cout << m_name << " attacks " << target->getName() << " for " << m_attackPower << " damage!" << std::endl;
    if (target->getHealt() <= 0) {
        Utility::printBlue(target->getName());
        Utility::printBlue(" is dead!\n");
        if (dynamic_cast<Monster*>(target)) { this->gainXP(20); }
        return;
    }
    std::cout << target->getName() << "'s healt: "  << target->getHealt() << std::endl;
}

void Hero::addItem(std::shared_ptr<Item> item) {
    m_inventory.addItem(item);
}

void Hero::useItem(int index) {
    std::shared_ptr<Item> item = m_inventory.getItem(index); 
    if (item) { //if the index is incorrect the function will retun nullptr
        const Type type = item->getType();
        if (type == Type::Potion) {
            m_health += item->getValue();
            if (m_health > Limits::HERO_MAX_HEALT) m_health = Limits::HERO_MAX_HEALT;
            Utility::printGreen(item->getName());
            Utility::printGreen(" was applied | Healt: +");
            Utility::printGreen(std::to_string(item->getValue()));
            std::cout << std::endl;
            m_inventory.removeItem(index);
        }
        else if (type == Type::Weapon) {
            m_attackPower += item->getValue();
            if (m_attackPower > Limits::HERO_MAX_ATTAC_POWER) m_attackPower = Limits::HERO_MAX_ATTAC_POWER;
            Utility::printGreen(m_name);
            Utility::printGreen(" equips ");
            Utility::printGreen(item->getName());
            Utility::printGreen(" | Attac Power: +");
            Utility::printGreen(std::to_string(item->getValue()));
            std::cout << std::endl;
        }
        // else if (item->getType() == Type::Key) {
            // std::cout << m_name << " uses " << item->getName() << " to unlock something!\n";
            // // e.g. gameWorld->unlockPortal(item->getName());
            // delete item; 
            // m_inventory.removeItem(index);
        // }
    }
}

void Hero::gainXP(int xp) {
    m_experiencePoints += xp;
    if(m_experiencePoints > Limits::HERO_MAX_XP) m_experiencePoints = Limits::HERO_MAX_XP;
    if(m_experiencePoints >= 100) {
        levelUp();
    }
}

void Hero::levelUp() {
    m_level = m_experiencePoints/100 + 1;
}

void Hero::setMount(std::shared_ptr<Mount> mount) {
    if (!mount) {
        Utility::printRed("Unknown Mount\n");
        return;
    }
    m_currentMount = mount;
}

std::vector<std::shared_ptr<Item>> Hero::getItems() {return m_inventory.getItems();}


std::shared_ptr<Mount> Hero::getMount() const {return m_currentMount;}

std::string Hero::getDialogue() const {
    return ("Hello I am " + m_name + " \n");
}

Inventory& Hero::getInventory() {return m_inventory;}

int Hero::getInventorySize() {return m_inventory.getSize();}

int Hero::getAttacPower() {return m_attackPower;}

int Hero::getLevel() {return m_level;}

int Hero::getEXP() {return m_experiencePoints;}
