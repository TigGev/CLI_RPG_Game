#include "../../headers/quests/Quest.h"
#include "../../headers/utility/Utility.h"

Quest::Quest(const std::string& title, const std::string& description, int xpReward, std::shared_ptr<Item> itemReward = nullptr) 
    : m_title(title), m_description(description), m_xpReward(xpReward), m_itemReward(itemReward) {}

std::string Quest::getDescription() {return m_description;}

void Quest::complete() {m_isCompleted = true;}

bool Quest::isQuestCompleted() const {return m_isCompleted;}

std::string Quest::getTitle() const {return m_title;}

int Quest::getXPReward() const {return m_xpReward;}

std::shared_ptr<Item> Quest::getItemReward() const {return m_itemReward;}
