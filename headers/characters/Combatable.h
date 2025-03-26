#ifndef COMBATABLE_H
#define COMBATABLE_H

class Character;

class Combatable {
    public:
        virtual ~Combatable() {std::cout << "~Combatable" << std::endl;}
        virtual void attack(Character* target) = 0;
        virtual void useAbility(Character* target) = 0;
};
#endif