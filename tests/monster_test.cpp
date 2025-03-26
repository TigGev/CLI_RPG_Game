#include <gtest/gtest.h>
#include "../headers/characters/Monster.h"
#include "../headers/characters/Character.h"
#include "../headers/utility/Utility.h"
#include <sstream>

class MonsterTest : public ::testing::Test {
protected:
    void SetUp() override {
        monster = new Monster("Goblin", 50, 10, 5, Ability::None);
    }

    void TearDown() override {
        delete monster;
    }

    Monster* monster;
};

TEST_F(MonsterTest, ConstructorAndDisplayStats) {
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    monster->displayStats();
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_TRUE(output.find("Name: Goblin") != std::string::npos);
    EXPECT_TRUE(output.find("Healt: \033[33m50\033[0m") != std::string::npos);
    EXPECT_TRUE(output.find("Attack: \033[31m10\033[0m") != std::string::npos); 
    EXPECT_TRUE(output.find("Defence: \033[31m5\033[0m") != std::string::npos); 
    EXPECT_TRUE(output.find("Special Ability:") != std::string::npos);
}


TEST_F(MonsterTest, TakeDamage) {
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    monster->takeDamage(15);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_EQ(monster->getHealt(), 40); 
    EXPECT_TRUE(output.find("Goblin: \033[31mTaking damage!\033[0m") != std::string::npos);
    EXPECT_TRUE(output.find("Remaining health: \033[33m40\033[0m") != std::string::npos);
}

TEST_F(MonsterTest, TakeDamageToZero) {
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    monster->takeDamage(60);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_EQ(monster->getHealt(), 0);
    EXPECT_TRUE(output.find("lost.") != std::string::npos);
    // EXPECT_TRUE(output.find("Remaining health: \033[31m0\033[0m") != std::string::npos);
}

TEST_F(MonsterTest, Attack) {
    Monster target("Orc", 50, 10, 5, Ability::None);
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    monster->attack(&target);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_EQ(target.getHealt(), 45);
    EXPECT_TRUE(output.find("Goblin attacks Orc for 10 damage!") != std::string::npos);
}

TEST_F(MonsterTest, UseAbility_None) {
    Monster target("Orc", 50, 10, 5, Ability::None);
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    monster->useAbility(&target);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_EQ(target.getHealt(), 50);
    EXPECT_TRUE(output.find("Goblin attempts an unknown ability!") != std::string::npos);
}

TEST_F(MonsterTest, UseAbility_Regenerate) {
    Monster regenMonster("Troll", 50, 10, 5, Ability::Regenerate);
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    regenMonster.useAbility(nullptr);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_EQ(regenMonster.getHealt(), 70);
    EXPECT_TRUE(output.find("Troll uses Regenerate and restores 20 health! Health now: 70") != std::string::npos);
}

TEST_F(MonsterTest, UseAbility_FireBreath) {
    Monster fireMonster("Dragon", 100, 10, 5, Ability::FireBreath);
    Monster target("Orc", 50, 10, 5, Ability::None);
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    fireMonster.useAbility(&target);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_EQ(target.getHealt(), 40);
    EXPECT_TRUE(output.find("Dragon uses Fire Breath, dealing 15 damage to Orc!") != std::string::npos);
}

TEST_F(MonsterTest, UseAbility_BoneSmash) {
    Monster smashMonster("Skeleton", 50, 10, 5, Ability::BoneSmash);
    Monster target("Orc", 50, 10, 5, Ability::None);
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    smashMonster.useAbility(&target);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_EQ(target.getHealt(), 40);
    EXPECT_TRUE(output.find("Skeleton uses Bone Smash, dealing 15 damage to Orc!") != std::string::npos);
}

int main(int argc, char **argv) {
    // Monster monst("Gobl", 50, 10, 5, Ability::None);
    // monst.takeDamage(0);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}