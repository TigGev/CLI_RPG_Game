#include <gtest/gtest.h>
#include "../headers/characters/NPC.h"
#include "../headers/characters/Monster.h" 
#include "../headers/quests/Quest.h"
#include "../headers/utility/Utility.h"
#include <sstream>
#include <memory>


class NPCTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto quest = std::make_shared<Quest>("Slay the Dragon", "Kill the fierce dragon.", 100);
        npc = new NPC("Villager", "Help me!", quest);
    }

    void TearDown() override {
        delete npc;
    }

    NPC* npc;
};

TEST_F(NPCTest, ConstructorAndDisplayStats) {
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    npc->displayStats();
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_TRUE(output.find("Name: Villager") != std::string::npos);
    EXPECT_TRUE(output.find("Healt: \033[34m100\033[0m") != std::string::npos); 
    EXPECT_TRUE(output.find("Dialogue: \"Help me!\"") != std::string::npos);
}

TEST_F(NPCTest, TakeDamage) {
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    npc->takeDamage(20);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_EQ(npc->getHealt(), 80);
    EXPECT_TRUE(output.find("Villager: ~~Please don't kill me.") != std::string::npos);
}

TEST_F(NPCTest, TakeDamageToDeath) {
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    npc->takeDamage(150);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_EQ(npc->getHealt(), 0);
    EXPECT_TRUE(output.find("\033[31mVillager is dead.\033[0m") != std::string::npos);
}

TEST_F(NPCTest, Interact) {
    Monster target("Goblin", 50, 10, 5, Ability::None);
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    npc->interact(&target);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_TRUE(output.find("Villager: Help me!") != std::string::npos);
}

TEST_F(NPCTest, InteractWithNull) {
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    npc->interact(nullptr);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_TRUE(output.find("Unknown character.") != std::string::npos);
}

TEST_F(NPCTest, GetDialogue) {
    EXPECT_EQ(npc->getDialogue(), "Help me!");
}

TEST_F(NPCTest, GetAssociatedQuest) {
    auto quest = npc->getAssociatedQuest();
    EXPECT_NE(quest, nullptr);
    EXPECT_EQ(quest->getDescription(), "Kill the fierce dragon.");
    EXPECT_EQ(quest->getTitle(), "Slay the Dragon");
    EXPECT_EQ(quest->getXPReward(), 100);
}

int main(int argc, char **argv) {
    auto quest = std::make_shared<Quest>("Slay the Dragon", "Kill the fierce dragon.", 100);
    NPC* npc = new NPC("Villager", "Help me!", quest);
    npc->displayStats();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}