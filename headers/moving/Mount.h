#ifndef MOUNT_H
#define MOUNT_H
#include <string>
#include <iostream>

enum class MountType {Land, Air, Water};

class Mount {
    protected:
        std::string m_name;
        MountType m_type;
        double m_speedMultiplier;
        int m_condition; //Fuel
    public:
        // Mount(const std::string& name);
        Mount(const std::string& name, MountType type);
        virtual ~Mount() {std::cout << "~Mount" << std::endl;}
        virtual void useMount(int distance) = 0;
        virtual void restOrRefuel();
        std::string getName() const;
        MountType getType() const;
        double getSpeedMultiplier() const;
        int getCondition() const;

};
#endif