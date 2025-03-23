#ifndef MOUNT_H
#define MOUNT_H
#include <string>

enum class MountType { Horse, Airship, Boat };

class Mount {
    protected:
        std::string name;
        MountType type;
        double speedMultiplier;
        int condition;
    public:
        Mount(const std::string& name, MountType type, double speedMultiplier, int condition);
        virtual ~Mount() = default;
        // virtual void useMount(int distance) = 0;
        // virtual void restOrRefuel() = 0;
        // std::string getName() const;
        MountType getType() const;
        double getSpeedMultiplier() const;
        int getCondition() const;

        Mount(const std::string& n) : name(n) {} //////////////
        std::string getName() const { return name; } //////////////
};
#endif