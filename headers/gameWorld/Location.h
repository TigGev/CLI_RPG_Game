#ifndef LOCATION_H
#define LOCATION_H
#include "../characters/Character.h"
#include "../moving/Portal.h"
#include <string>
#include <vector>
#include <memory>

// class Character;
// class Portal;

class Location {
    private:
        std::string m_name;
        std::string m_description;
        std::vector<std::shared_ptr<Character>> m_entities;
        std::vector<std::shared_ptr<Portal>> m_portals;
    public:
        Location(const std::string& name, const std::string& description);
        ~Location() = default;
        void addEntity(std::shared_ptr<Character>entity);
        void removeEntity(std::shared_ptr<Character> entity);
        void addPortal(std::shared_ptr<Portal> portal);
        std::string getName() const;
        std::string getDescription() const;
        std::vector<std::shared_ptr<Character>> getEntities() const;
        std::vector<std::shared_ptr<Portal>> getPortals() const;
};
#endif