#ifndef AIRSHIP_H
#define AIRSHIP_H
#include "Mount.h"

class Airship : public Mount {
    public:
        Airship(const std::string& name);
        ~Airship();
        void useMount(int distance) override;
        void restOrRefuel() override;
};
#endif