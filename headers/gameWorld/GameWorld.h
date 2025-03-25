#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <vector>
#include <memory>

class Location;

class GameWorld {
    private:
        std::vector<std::shared_ptr<Location>> m_locations;
        std::shared_ptr<Location> m_currentLocation;
    public:
        GameWorld(std::shared_ptr<Location> firstLocation);
        ~GameWorld() = default;
        void addLocation(std::shared_ptr<Location> location);
        void moveToLocation(const std::string& destination);
        std::weak_ptr<Location> getCurrentLocation() const;
};
#endif