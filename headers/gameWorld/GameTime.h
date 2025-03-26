#ifndef GAMETIME_H
#define GAMETIME_H
#include <iostream>

enum class TimeOfDay { Morning, Afternoon, Evening, Night };

class GameTime {
    private:
        TimeOfDay m_currentTime;
        int m_hours; //initial time 6 (6:00 PM)
        int m_dayCount;
    public:
        GameTime();
        ~GameTime() {std::cout << "~GameTime" << std::endl;}
        void advanceTime(int hours);
        TimeOfDay getCurrentTime() const;
        int getDayCount() const;
};
#endif