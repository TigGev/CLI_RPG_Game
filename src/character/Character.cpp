#include "../../headers/characters/Character.h"

Character::Character(const std::string& name, int health, int attackPower, int defense) 
    : m_name(name), m_health(health), m_attackPower(attackPower), m_defense(defense) {
    }

std::string Character::getName() const {return m_name;}

int Character::getHealt() const {return m_health;}
