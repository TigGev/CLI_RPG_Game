#ifndef MOUNT_H
#define MOUNT_H
#include <string>

enum class MountType {Horse, Airship, Boat};

class Mount {
    protected:
        std::string m_name;
        MountType m_type;
        double m_speedMultiplier;
        unsigned int m_condition; //Fuel
    public:
        Mount(const std::string& name, MountType type);
        virtual ~Mount() = default;
        virtual void useMount(int distance);
        virtual void restOrRefuel();
        std::string getName() const;
        MountType getType() const;
        double getSpeedMultiplier() const;
        int getCondition() const;

};
#endif