#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <vector>
#include <memory>
#include "Location.h"

// class Location;

class GameWorld {
    private:
        std::vector<std::shared_ptr<Location>> m_locations;
        std::shared_ptr<Location> m_currentLocation;
    public:
        GameWorld(std::shared_ptr<Location> firstLocation);
        ~GameWorld() {std::cout << "~GameWorld" << std::endl;}
        void addLocation(std::shared_ptr<Location> location);
        void moveToLocation(const std::string& destination);
        std::weak_ptr<Location> getCurrentLocation() const;
};
#endif