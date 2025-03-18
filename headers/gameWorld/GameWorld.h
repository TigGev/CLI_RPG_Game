#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <vector>
class Location;
class GameWorld {
    private:
        std::vector<Location*> locations;
        Location* currentLocation;
    public:
        GameWorld();
        ~GameWorld();
        void addLocation(Location* location);
        void moveToLocation(const std::string& destination);
        Location* getCurrentLocation() const;
};
#endif