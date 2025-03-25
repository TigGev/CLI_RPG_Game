#ifndef HORSE_H
#define HORSE_H
#include "Mount.h"
class Horse : public Mount {
    public:
        Horse(const std::string& name);
        ~Horse() = default;
        void useMount(int distance) override;
};
#endif