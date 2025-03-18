#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H
#include <vector>

class Quest;

class QuestManager {
    private:
        std::vector<Quest*> activeQuests;
        std::vector<Quest*> completedQuests;
    public:
        QuestManager();
        ~QuestManager();
        void assignQuest(Quest* quest);
        void checkQuestCompletion();
        void distributeRewards();
        std::vector<Quest*> getActiveQuests() const;
};
#endif