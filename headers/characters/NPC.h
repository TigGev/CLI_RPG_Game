#ifndef NPC_H
#define NPC_H
#include "Character.h"
#include "Interactable.h"
#include "../quests/Quest.h"
#include <string>


class NPC : public Character, public Interactable {
    private:
        std::string m_dialogue;
        std::shared_ptr<Quest> m_associatedQuest;
    public:
        NPC(const std::string& name, const std::string& dialogue, std::shared_ptr<Quest> quest);
        ~NPC() {std::cout << "~NPC" << std::endl;}
        void displayStats() const override;
        void takeDamage(int damage) override;
        void interact(Character* target) override;
        std::string getDialogue() const override;
        std::shared_ptr<Quest> getAssociatedQuest() const;
};
#endif