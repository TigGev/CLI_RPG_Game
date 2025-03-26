#ifndef QUEST_H
#define QUEST_H
#include <string>
#include "../inventory/Item.h"

class Quest {
    private:
        std::string m_title;
        std::string m_description;
        bool m_isCompleted;
        int m_xpReward;
        std::shared_ptr<Item> m_itemReward;
    public:
        Quest(const std::string& title, const std::string& description, int xpReward, std::shared_ptr<Item> itemReward = nullptr);
        ~Quest() {}; 
        // Quest(const std::string& desc);
        void complete();
        std::string getDescription() ;
        bool isQuestCompleted() const;
        std::string getTitle() const;
        int getXPReward() const;
        std::shared_ptr<Item> getItemReward() const;
};
#endif