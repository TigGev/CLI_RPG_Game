#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <vector>

class Character;
class Portal;

class Location {
    private:
        std::string name;
        std::string description;
        std::vector<Character*> entities;
        std::vector<Portal*> portals;
    public:
        Location(const std::string& name, const std::string& description);
        ~Location();
        void addEntity(Character* entity);
        void removeEntity(Character* entity);
        void addPortal(Portal* portal);
        std::string getName() const;
        std::string getDescription() const;
        std::vector<Character*> getEntities() const;
        std::vector<Portal*> getPortals() const;
};
#endif