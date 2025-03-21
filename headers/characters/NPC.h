#ifndef NPC_H
#define NPC_H
#include "Character.h"
#include "Interactable.h"
#include "Quest.h"
#include <string>
class NPC : public Character, public Interactable {
    private:
        std::string dialogue;
        Quest* associatedQuest;
    public:
        NPC(const std::string& name, const std::string& dialogue, const std::string& quest);
        ~NPC();
        void displayStats() const override;
        void takeDamage(int damage) override;
        void interact(Character* target) override;
        std::string getDialogue() const override;
        Quest* getAssociatedQuest() const;
};
#endif