#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
class Character {
    protected:
        std::string name;
        int health;
        int attackPower;
        int defense;
    public:
        Character(const std::string& name, int health, int attackPower, int defense);
        virtual ~Character() = default;
        virtual void displayStats() const = 0;
        virtual void takeDamage(int damage) = 0;
        std::string getName() const;
};
#endif