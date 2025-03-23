#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H
#include <vector>
#include "Quest.h"
#include <iostream>
// class Quest;

class QuestManager {
    private:
        std::vector<Quest*> activeQuests;
        std::vector<Quest*> completedQuests;
    public:
        QuestManager() {}; ///////////////
        ~QuestManager() {}; /////////////////
        void assignQuest(Quest* quest) { ///////////////
           std::cout << "Quest assigned: " << quest->getDescription() << "\n";
        } //////////////
        void checkQuestCompletion();
        void distributeRewards();
        // void assignQuest(Quest* quest);
        std::vector<Quest*> getActiveQuests() const;
};
#endif