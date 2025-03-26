#include <gtest/gtest.h>
#include "../headers/gameWorld/Location.h"
#include "../headers/characters/Character.h"
#include "../headers/moving/Portal.h"
#include "../headers/inventory/Inventory.h"
#include "../headers/inventory/Item.h"
#include <memory>

class MockCharacter : public Character {
public:
    MockCharacter(const std::string& name, int health, int attackPower, int defense)
        : Character(name, health, attackPower, defense) {}
    void displayStats() const override {
    }
    void takeDamage(int damage) override {
        m_health -= damage;
    }
};

TEST(LocationTest, CreateLocation) {
    Location loc("Forest", "A dense forest with tall trees.");
    EXPECT_EQ(loc.getName(), "Forest");
    EXPECT_EQ(loc.getDescription(), "A dense forest with tall trees.");
    EXPECT_TRUE(loc.getEntities().empty());
    EXPECT_TRUE(loc.getPortals().empty());
}

TEST(LocationTest, AddEntity) {
    Location loc("Castle", "A grand castle.");
    auto character = std::make_shared<MockCharacter>("Knight", 100, 20, 10);

    loc.addEntity(character);
    auto entities = loc.getEntities();
    ASSERT_EQ(entities.size(), 1);
    EXPECT_EQ(entities[0]->getName(), "Knight");
    EXPECT_EQ(entities[0]->getHealt(), 100);
}

TEST(LocationTest, AddDuplicateEntity) {
    Location loc("Village", "A quiet village.");
    auto character = std::make_shared<MockCharacter>("Villager", 50, 5, 5);

    loc.addEntity(character);
    loc.addEntity(character);
    auto entities = loc.getEntities();
    ASSERT_EQ(entities.size(), 1);
}

TEST(LocationTest, RemoveEntity) {
    Location loc("Dungeon", "A dark dungeon.");
    auto character = std::make_shared<MockCharacter>("Prisoner", 30, 10, 5);

    loc.addEntity(character);
    loc.removeEntity(character);
    auto entities = loc.getEntities();
    EXPECT_TRUE(entities.empty());
}

TEST(LocationTest, AddPortal) {
    Location source("Room1", "A small room.");
    Location destination("Room2", "Another small room.");
    auto portal = std::make_shared<Portal>("Door", source, destination, false, "key");

    source.addPortal(portal);
    auto portals = source.getPortals();
    ASSERT_EQ(portals.size(), 1);
    EXPECT_EQ(portals[0]->getName(), "Door");
    EXPECT_EQ(portals[0]->getSource().getName(), "Room1");
    EXPECT_EQ(portals[0]->getDestination().getName(), "Room2");
}

TEST(LocationTest, AddDuplicatePortal) {
    Location source("Cave", "A damp cave.");
    Location destination("Exit", "The cave exit.");
    auto portal = std::make_shared<Portal>("Tunnel", source, destination, true, "riddle");

    source.addPortal(portal);
    source.addPortal(portal);
    auto portals = source.getPortals();
    ASSERT_EQ(portals.size(), 1);
}

TEST(LocationTest, PortalActivationSuccess) {
    Location source("Lab", "A mysterious lab.");
    Location destination("Exit", "The lab exit.");
    auto portal = std::make_shared<Portal>("Gate", source, destination, true, "password", "secret");
    Inventory inventory;

    source.addPortal(portal);
    bool activated = portal->attemptActivation("password", inventory);
    EXPECT_TRUE(activated);
    EXPECT_FALSE(portal->isPortalLocked());
}

TEST(LocationTest, PortalActivationFailure) {
    Location source("Tower", "A tall tower.");
    Location destination("Ground", "The ground floor.");
    auto portal = std::make_shared<Portal>("Stairs", source, destination, true, "code123");
    Inventory inventory;

    source.addPortal(portal);
    bool activated = portal->attemptActivation("wrong", inventory);
    EXPECT_FALSE(activated);
    EXPECT_TRUE(portal->isPortalLocked());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}