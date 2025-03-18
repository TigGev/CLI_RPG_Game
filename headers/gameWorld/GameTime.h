#ifndef GAMETIME_H
#define GAMETIME_H
enum class TimeOfDay { Morning, Afternoon, Evening, Night };
class GameTime {
    private:
        TimeOfDay currentTime;
        int dayCount;
    public:
        GameTime();
        ~GameTime();
        void advanceTime(int hours);
        TimeOfDay getCurrentTime() const;
        int getDayCount() const;
};
#endif