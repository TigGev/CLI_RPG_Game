#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H
#include <vector>
#include "Quest.h"
// #include "../characters/Hero.h"
#include <iostream>
#include <memory>

class Hero;

class QuestManager {
    private:
        std::vector<std::shared_ptr<Quest>> m_activeQuests;
        std::vector<std::shared_ptr<Quest>> m_completedQuests;
    public:
        QuestManager() = default; 
        ~QuestManager() {std::cout << "~QuestManager" << std::endl;}
        void assignQuest(std::shared_ptr<Quest> quest);
        void checkQuestCompletion();
        void distributeRewards(Hero* hero);
        std::vector<std::shared_ptr<Quest>> getActiveQuests() const;
};
#endif