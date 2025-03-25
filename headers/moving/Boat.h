#ifndef BOAT_H
#define BOAT_H
#include "Mount.h"
#include <string>

class Boat : public Mount {
    // private:
        // std::string weatherCondition;
    public:
        Boat(const std::string& name);
        ~Boat();
        void useMount(int distance) override;
        // void setWeather(const std::string& weather);
};
#endif