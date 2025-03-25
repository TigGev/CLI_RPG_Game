#include "../../headers/moving/Boat.h"
#include "../../headers/utility/Utility.h"

Boat::Boat(const std::string& name) : Mount(name, MountType::Water) {}

void Boat::useMount(int distance) {
    int expense = Utility::getExpenseForMount(distance, m_type);
    if ((m_condition - expense) < 0) {
        std::cout << "Too long distance. Power reserve - " << Utility::getPowerReserve(m_condition, m_type) << " Km" << std::endl;
        return;
    }
    m_condition -= expense;
    std::cout << distance << "Movment on water" << distance << " Km." << std::endl;
}
