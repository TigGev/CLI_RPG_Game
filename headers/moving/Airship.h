#ifndef AIRSHIP_H
#define AIRSHIP_H
#include "Mount.h"
#include <iostream>

class Airship : public Mount {
    public:
        Airship(const std::string& name);
        ~Airship() {std::cout << "~Airship" << std::endl;}
        void useMount(int distance) override;
};
#endif