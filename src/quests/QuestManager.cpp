#include "../../headers/quests/QuestManager.h"
#include "../../headers/inventory/Item.h"
#include "../../headers/utility/Utility.h"

void QuestManager::assignQuest(std::shared_ptr<Quest> quest) {
    if (!quest) {
        Utility::printRed("!Failed adding quest. (Invalid quest)\n");
        return;
    }
    m_activeQuests.push_back(quest);
    Utility::printGreen("Successful adding of quest.\n");
}

std::vector<std::shared_ptr<Quest>> QuestManager::getActiveQuests() const {return m_activeQuests;}

void QuestManager::checkQuestCompletion() {
    for (int i = 0; i < m_activeQuests.size(); ++i) {
        if (m_activeQuests[i]->isQuestCompleted()) {
            m_completedQuests.push_back(m_activeQuests[i]);
            m_activeQuests.erase(m_activeQuests.begin() + i);
        }
    }
}

void QuestManager::distributeRewards(Hero* hero) {
    if (!hero) {
        Utility::printRed("!Invalid action.");
        return;
    }
    for (auto quest : m_completedQuests) {
        Utility::printGreen("Rewards for completed quest ");        
        Utility::printGreen(quest->getTitle());
        Utility::printGreen(": +");
        hero->gainXP(quest->getXPReward());
        Utility::printGreen(std::to_string(quest->getXPReward()));
        Utility::printGreen("XP +Item: ");
        hero->addItem(quest->getItemReward());
        Utility::printGreen((quest->getItemReward())->getName());
        std::cout << std::endl;
    }
    m_completedQuests.clear();
}

