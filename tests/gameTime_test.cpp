#include <gtest/gtest.h>
#include "../headers/gameWorld/GameTime.h" 

// Тестовый фикстур для удобного доступа к объекту GameTime
class GameTimeTest : public ::testing::Test {
protected:
    GameTime gameTime;
};

// Тест конструктора: начальное время должно быть Morning (6:00), день 0
TEST_F(GameTimeTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Morning);
    EXPECT_EQ(gameTime.getDayCount(), 0);
}

// Тест продвижения времени в пределах одного дня
TEST_F(GameTimeTest, AdvanceTimeWithinDay) {
    gameTime.advanceTime(6); // 6:00 + 6 часов = 12:00
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Afternoon);
    EXPECT_EQ(gameTime.getDayCount(), 0);

    gameTime.advanceTime(6); // 12:00 + 6 часов = 18:00
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Evening);
    EXPECT_EQ(gameTime.getDayCount(), 0);
}

// Тест перехода через сутки
TEST_F(GameTimeTest, AdvanceTimeAcrossDay) {
    gameTime.advanceTime(18); // 6:00 + 18 часов = 24:00 (0:00 следующего дня)
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Night);
    EXPECT_EQ(gameTime.getDayCount(), 1);

    gameTime.advanceTime(6); // 0:00 + 6 часов = 6:00
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Morning);
    EXPECT_EQ(gameTime.getDayCount(), 1);
}

// Тест корректности перехода через несколько дней
TEST_F(GameTimeTest, AdvanceTimeMultipleDays) {
    gameTime.advanceTime(42); // 6:00 + 42 часа = 48:00 (0:00 через 2 дня)
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Night);
    EXPECT_EQ(gameTime.getDayCount(), 2);

    gameTime.advanceTime(12); // 0:00 + 12 часов = 12:00
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Afternoon);
    EXPECT_EQ(gameTime.getDayCount(), 2);
}

// Тест граничных значений времени суток
TEST_F(GameTimeTest, TimeOfDayBoundaries) {
    gameTime.advanceTime(5); // 6:00 + 5 = 11:00 (Morning)
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Morning);

    gameTime.advanceTime(1); // 11:00 + 1 = 12:00 (Afternoon)
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Afternoon);

    gameTime.advanceTime(5); // 12:00 + 5 = 17:00 (Afternoon)
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Afternoon);

    gameTime.advanceTime(1); // 17:00 + 1 = 18:00 (Evening)
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Evening);
}

// Тест на случай ошибки в исходном коде (Evening никогда не наступает из-за m_hours < 0)
TEST_F(GameTimeTest, CheckEveningLogic) {
    gameTime.advanceTime(12); // 6:00 + 12 = 18:00
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Evening); // Этот тест провалится из-за бага
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}