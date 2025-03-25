#ifndef AIRSHIP_H
#define AIRSHIP_H
#include "Mount.h"

class Airship : public Mount {
    public:
        Airship(const std::string& name);;
        ~Airship() = default;
        void useMount(int distance) override;
};
#endif