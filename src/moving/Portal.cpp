#include "../../headers/moving/Portal.h"
#include "../../headers/utility/Utility.h"

Portal::Portal(const std::string& name, Location source, Location destination, bool locked, 
    const std::string& condition, const std::string& answer) 
        : m_name(name), m_sourceLocation(source), m_destinationLocation(destination), m_isLocked(locked),
            m_activationCondition(condition), m_Answer(answer) {}

bool Portal::attemptActivation(const std::string& playerInput, Inventory& playerInventory) {
    if (playerInput == m_activationCondition) {
        m_isLocked = true;
        return true;
    }
    return false;
}

Location Portal::getSource() const {return m_sourceLocation;}

Location Portal::getDestination() const {return m_destinationLocation;}

std::string Portal::getName() const {return m_name;}

bool Portal::isPortalLocked() const {return m_isLocked;}

std::string Portal::getCondition() const {return m_activationCondition;}
