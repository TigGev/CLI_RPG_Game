#include <gtest/gtest.h>
#include "../headers/gameWorld/GameWorld.h"
#include "../headers/gameWorld/Location.h"
#include "../headers/utility/Utility.h"

class GameWorldTest : public ::testing::Test {
protected:
    std::shared_ptr<Location> forest;
    std::shared_ptr<Location> village;
    std::shared_ptr<GameWorld> world;

    void SetUp() override {
        forest = std::make_shared<Location>("Forest", "A dense forest");
        village = std::make_shared<Location>("Village", "A quiet village");
        world = std::make_shared<GameWorld>(forest);
    }
};

TEST_F(GameWorldTest, ConstructorSetsInitialLocation) {
    auto currentLoc = world->getCurrentLocation().lock();
    ASSERT_TRUE(currentLoc != nullptr);
    EXPECT_EQ(currentLoc->getName(), "Forest");
    EXPECT_EQ(currentLoc->getDescription(), "A dense forest");
}

TEST_F(GameWorldTest, AddLocationSuccess) {
    world->addLocation(village);
    EXPECT_EQ(world->getCurrentLocation().lock()->getName(), "Forest");
}

TEST_F(GameWorldTest, AddDuplicateLocation) {
    testing::internal::CaptureStdout();
    world->addLocation(forest);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("This location alredy exists"), std::string::npos);
}

TEST_F(GameWorldTest, AddNullLocation) {
    testing::internal::CaptureStdout();
    world->addLocation(nullptr);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Unknown location!"), std::string::npos);
}

TEST_F(GameWorldTest, MoveToExistingLocation) {
    world->addLocation(village);
    testing::internal::CaptureStdout();
    world->moveToLocation("Village");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Location changed"), std::string::npos);
    EXPECT_EQ(world->getCurrentLocation().lock()->getName(), "Village");
}

TEST_F(GameWorldTest, MoveToNonExistentLocation) {
    testing::internal::CaptureStdout();
    world->moveToLocation("Dungeon");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Failed to change location"), std::string::npos);
    EXPECT_EQ(world->getCurrentLocation().lock()->getName(), "Forest");
}

