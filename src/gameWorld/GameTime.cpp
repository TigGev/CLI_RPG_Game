#include "../../headers/gameWorld/GameTime.h"

GameTime::GameTime() : m_currentTime(TimeOfDay::Morning), m_hours(6) /*6:00 PM*/, m_dayCount(0)  {}

void GameTime::advanceTime(int hours) {
    if ((m_hours += hours) >= 24) {
        m_dayCount += m_hours / 24;
        m_hours = m_hours % 24;
    }
    if (m_hours >= 6 && m_hours < 12) m_currentTime = TimeOfDay::Morning;
    if (m_hours >= 12 && m_hours < 18) m_currentTime = TimeOfDay::Afternoon;
    if (m_hours >= 18 && m_hours < 24) m_currentTime = TimeOfDay::Evening;
    if (m_hours >= 0 && m_hours < 6) m_currentTime = TimeOfDay::Night;
}

TimeOfDay GameTime::getCurrentTime() const {return m_currentTime;}

int GameTime::getDayCount() const {return m_dayCount;}


// Compile
// g++ -std=c++20 -I../headers gameTime_test.cpp  ../src/gameWorld/GameTime.cpp -lgtest -lgtest_main -pthread -o gameTime_test