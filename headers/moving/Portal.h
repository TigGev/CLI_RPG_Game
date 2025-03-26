#ifndef PORTAL_H
#define PORTAL_H
#include <string>
#include "../gameWorld/Location.h"

class Inventory;

class Portal {
    private:
        std::string m_name;
        // std::string sourceLocation;
        Location m_sourceLocation;
        Location m_destinationLocation;
        bool m_isLocked;
        std::string m_activationCondition;
        std::string m_Answer;
    public:
        Portal(const std::string& name, Location source, Location destination, bool locked, 
               const std::string& condition, const std::string& answer = "") ;
        ~Portal() {std::cout << "~Portal" << std::endl;}
        bool attemptActivation(const std::string& playerInput /*,Inventory& playerInventory*/);
        Location getSource() const;
        std::string getName() const;
        Location getDestination() const;
        bool isPortalLocked() const;
        std::string getCondition() const;
};
#endif