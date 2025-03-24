#include "../../headers/characters/NPC.h"
#include "../../headers/utility/Utility.h"
NPC::NPC(const std::string& name, const std::string& dialogue, std::shared_ptr<Quest>quest)
    : Character(name, Limits::NPC_MAX_HEALT, Limits::NPC_PRIM_ATTAC_POWER, Limits::NPC_MAX_DEFENCE) {
        m_dialogue = dialogue;
        m_associatedQuest = quest;
}

void NPC::displayStats() const {
    std::cout << "Name: " << m_name << " | Healt: ";
    Utility::printHealt(m_health);
    std::cout << " | Dialogue: \"" << m_dialogue << "\"" << std::endl;
}

void NPC::takeDamage(int damage) {
    if (damage < 1) return;
    int finalDamage = damage - m_defense;
    if (finalDamage < 0) finalDamage = 0;
    m_health -= finalDamage;
    if (m_health <= 0) {
        m_health = 0;
        Utility::printRed(m_name);
        Utility::printRed("Villager is dead.");
        return;
    }
    std::cout << m_name << ": ~~Please don't kill me." << std::endl;
}

void NPC::interact(Character* target) {
    if (!target) {
        std::cout << "Unknown character." << std::endl;
        return;
    }
    std::cout << m_name << ": " << m_dialogue << std::endl;
}

std::string NPC::getDialogue() const {return m_dialogue;}

std::shared_ptr<Quest> NPC::getAssociatedQuest() const {return m_associatedQuest;}
