#include "../../headers/gameWorld/GameWorld.h"
#include "../../headers/gameWorld/Location.h"
#include "../../headers/utility/Utility.h"
#include <iostream>

GameWorld::GameWorld(std::shared_ptr<Location> firstLocation) : m_currentLocation(firstLocation) {
    m_locations.push_back(m_currentLocation);
}

void GameWorld::addLocation(std::shared_ptr<Location> location) {
    if (!location) {
        std::cout << "Unknown location!" << std::endl;
        return;
    }
    for (auto loc : m_locations) {
        if (loc == location) {
            std::cout << "This location alredy exists in the game world." << std::endl;
            return;
        }
    }
    m_locations.push_back(location);
}

void GameWorld::moveToLocation(const std::string& destination) {
    for (auto loc : m_locations) {
        if (loc->getName() == destination) {
            m_currentLocation = loc;
            std::cout << "Location changed.\n  New location -> " << destination  << std::endl;
            loc -> getDescription();
            return;
        }
    }
    std::cout << "Failed to change location." << std::endl;
}

std::weak_ptr<Location> GameWorld::getCurrentLocation() const {return m_currentLocation;}
