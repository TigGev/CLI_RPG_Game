#include <gtest/gtest.h>
#include "../headers/gameWorld/GameTime.h" 

class GameTimeTest : public ::testing::Test {
protected:
    GameTime gameTime;
};

TEST_F(GameTimeTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Morning);
    EXPECT_EQ(gameTime.getDayCount(), 0);
}

TEST_F(GameTimeTest, AdvanceTimeWithinDay) {
    gameTime.advanceTime(6);
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Afternoon);
    EXPECT_EQ(gameTime.getDayCount(), 0);

    gameTime.advanceTime(6);
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Evening);
    EXPECT_EQ(gameTime.getDayCount(), 0);
}

TEST_F(GameTimeTest, AdvanceTimeAcrossDay) {
    gameTime.advanceTime(18);
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Night);
    EXPECT_EQ(gameTime.getDayCount(), 1);

    gameTime.advanceTime(6);
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Morning);
    EXPECT_EQ(gameTime.getDayCount(), 1);
}

TEST_F(GameTimeTest, AdvanceTimeMultipleDays) {
    gameTime.advanceTime(42);
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Night);
    EXPECT_EQ(gameTime.getDayCount(), 2);

    gameTime.advanceTime(12);
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Afternoon);
    EXPECT_EQ(gameTime.getDayCount(), 2);
}

TEST_F(GameTimeTest, TimeOfDayBoundaries) {
    gameTime.advanceTime(5);
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Morning);

    gameTime.advanceTime(1);
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Afternoon);

    gameTime.advanceTime(5);
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Afternoon);

    gameTime.advanceTime(1);
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Evening);
}

TEST_F(GameTimeTest, CheckEveningLogic) {
    gameTime.advanceTime(12);
    EXPECT_EQ(gameTime.getCurrentTime(), TimeOfDay::Evening);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}