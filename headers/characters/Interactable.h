#ifndef INTERACTABLE_H
#define INTERACTABLE_H
#include <string>

class Character;
class Interactable {
    public:
        virtual ~Interactable() {std::cout << "~Interactable" << std::endl;}
        virtual void interact(Character* target) = 0;
        virtual std::string getDialogue() const = 0;
};
#endif