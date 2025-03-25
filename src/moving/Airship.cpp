#include "../../headers/moving/Airship.h"
#include "../../headers/utility/Utility.h"

Airship::Airship(const std::string& name) : Mount(name, MountType::Air) {}

void Airship::useMount(int distance) {
    int expense = Limits::AIRSHIP_MAX_DISTANCE/100; // Utility::getExpenseForMount(distance, m_type);
    if ((m_condition - expense) < 0) {
        std::cout << "Too long distance. Power reserve - " << Utility::getPowerReserve(m_condition, m_type) << " Km" << std::endl;
        return;
    }
    m_condition -= expense;
    std::cout << distance << "Air travel " << distance << " Km" << std::endl;
}
