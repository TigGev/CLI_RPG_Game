#include "../../headers/gameWorld/Location.h"
#include "../../headers/moving/Portal.h"
#include <iostream>
#include "../../headers/utility/Utility.h"

Location::Location(const std::string& name, const std::string& description) 
    : m_name(name), m_description(description) {}

void Location::addEntity(std::shared_ptr<Character> entity) {
    if (!entity) {
        Utility::printRed("Failed to add. Unknown character.");
        std::cout << std::endl;
        return;
    }
    for (auto ent : m_entities) {
        if (ent == entity) {
            std::cout << entity->getName() << " alredy exists in " << m_name << std::endl;
            return;
        }
    }
    m_entities.push_back(entity);
    std::cout << entity->getName() << " successfuly added to " << m_name << std::endl;
}

void Location::removeEntity(std::shared_ptr<Character> entity) {
    if (!entity) {
        Utility::printRed("Failed to remove. Unknown character.");
        std::cout << std::endl;
        return;
    }
    for (auto ent = m_entities.begin(); ent != m_entities.end(); ++ent) {
        if ((*ent) == entity) {
            m_entities.erase(ent);
            std::cout << entity->getName() << " successfuly removed." << std::endl;
            return;
        }
    }
    Utility::printRed("Failed to delete ");
    Utility::printRed(entity->getName());
    Utility::printRed(". Such character does not exist in ");
    Utility::printRed(m_name);
}

void Location::addPortal(std::shared_ptr<Portal> portal) {
    if (!portal) {
        Utility::printRed("Failed to add portal.");
        std::cout << std::endl;
        return;
    }
    for (auto port : m_portals) {
        if (port == portal) {
            std::cout << portal->getName() << " alredy exists in " << m_name << std::endl;
            return;
        }
    }
    m_portals.push_back(portal);
    std::cout << portal->getName() << " successfuly added to " << m_name << std::endl;
}

std::string Location::getName() const {return m_name;}

std::string Location::getDescription() const {return m_description;}

std::vector<std::shared_ptr<Character>> Location::getEntities() const {return m_entities;}

std::vector<std::shared_ptr<Portal>> Location::getPortals() const {return m_portals;}
