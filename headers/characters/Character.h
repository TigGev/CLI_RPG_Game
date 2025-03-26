#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <iostream>



class Character {
    protected:
        std::string m_name;
        int m_health;
        int m_attackPower;
        int m_defense;
    public:
        Character(const std::string& name, int health, int attackPower, int defense);
        virtual ~Character() {std::cout << "~Character" << std::endl;}
        virtual void displayStats() const = 0;
        virtual void takeDamage(int damage) = 0;
        std::string getName() const;
        int getHealt() const;
};
#endif