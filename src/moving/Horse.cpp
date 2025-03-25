#include "../../headers/moving/Horse.h"
#include "../../headers/utility/Utility.h"

Horse::Horse(const std::string& name) : Mount(name, MountType::Land) {}

void Horse::useMount(int distance) {
    int expense = Limits::HORSE_MAX_DISTANCE/100;  //Utility::getExpenseForMount(distance, m_type);
    if ((m_condition - expense) < 0) {
        std::cout << "Too long distance. Power reserve - " << Utility::getPowerReserve(m_condition, m_type) << " Km" << std::endl;
        return;
    }
    m_condition -= expense;
    std::cout << distance << "Land travel " << distance << " Km" << std::endl;
}

