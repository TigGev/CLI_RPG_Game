#ifndef QUEST_H
#define QUEST_H
#include <string>

class Item;

class Quest {
    private:
        std::string title;
        std::string description;
        bool isCompleted;
        int xpReward;
        Item* itemReward;
    public:
        Quest(const std::string& title, const std::string& description, int xpReward, Item* itemReward = nullptr) {}; ///
        ~Quest() {}; ////////////////
        Quest(const std::string& desc) : description(desc) {} ///////
        std::string getDescription() const { return description; } ///////
        void complete();
        bool isQuestCompleted() const;
        std::string getTitle() const;
        // std::string getDescription() const;
        int getXPReward() const;
        Item* getItemReward() const;
};
#endif