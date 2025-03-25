#ifndef PORTAL_H
#define PORTAL_H
#include <string>

class Inventory;

class Portal {
    private:
        std::string name;
        std::string sourceLocation;
        std::string destinationLocation;
        bool isLocked;
        std::string activationCondition;
        std::string riddleAnswer;
    public:
        Portal(const std::string& source, const std::string& destination, bool locked, 
               const std::string& condition, const std::string& answer = "");
        ~Portal();
        bool attemptActivation(const std::string& playerInput, Inventory& playerInventory);
        std::string getSource() const;
        std::string getName() const;
        std::string getDestination() const;
        bool isPortalLocked() const;
        std::string getCondition() const;
};
#endif