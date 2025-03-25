#include "../../headers/moving/Mount.h"
#include "../../headers/utility/Utility.h"

inline bool operator==(MountType lhs, MountType rhs) {
    return static_cast<int>(lhs) == static_cast<int>(rhs);
}


Mount::Mount(const std::string& name, MountType type) 
    : m_name(name), m_type(type), m_condition(100) { 
        m_speedMultiplier = m_type == MountType::Land? 2 : m_type == MountType::Air ? 3.5 : m_type == MountType::Water ? 2.5 : 1;
}

// void Mount::useMount(int distance) {
//     int expense = Utility::getExpenseForMount(distance, m_type);
//     if ((m_condition - expense) < 0) {
//         std::cout << "Too long distance. Power reserve - " << Utility::getPowerReserve(m_condition, m_type) << " Km" << std::endl;
//         return;
//     }
//     m_condition -= expense;
//     std::cout << distance << "Km movment." << std::endl;
// }

void Mount::restOrRefuel() {
    m_condition = 100;
    Utility::printBlue("Power reserve restored!");
}

std::string Mount::getName() const {return m_name;}

MountType Mount::getType() const {return m_type;}

double Mount::getSpeedMultiplier() const {return m_speedMultiplier;}

int Mount::getCondition() const {return m_condition;}
