#include <gtest/gtest.h>
#include "../headers/characters/Hero.h"
#include "../headers/characters/Monster.h"
#include "../headers/characters/NPC.h"
#include "../headers/inventory/Item.h"
#include "../headers/moving/Horse.h"
#include "../headers/quests/Quest.h"
#include "../headers/quests/QuestManager.h"
#include "../headers/utility/Utility.h"
#include <memory>
#include <sstream>

TEST(HeroTest, CreateHero) {
    QuestManager qm;
    Hero hero("Arthur", Limits::HERO_PRIM_HEALT, Limits::HERO_PRIM_ATTAC_POWER, Limits::HERO_PRIM_DEFENCE, qm);
    EXPECT_EQ(hero.getName(), "Arthur");
    EXPECT_EQ(hero.getHealt(), Limits::HERO_PRIM_HEALT);
    EXPECT_EQ(hero.getAttacPower(), Limits::HERO_PRIM_ATTAC_POWER);
    EXPECT_EQ(hero.getLevel(), 1);
    EXPECT_EQ(hero.getEXP(), Limits::HERO_PRIM_XP);
    EXPECT_EQ(hero.getInventorySize(), 0);
    EXPECT_EQ(hero.getMount(), nullptr);
}

TEST(HeroTest, CreateHeroWithInvalidValues) {
    QuestManager qm;
    Hero hero("Merlin", -50, -10, -5, qm);
    EXPECT_EQ(hero.getHealt(), 0);
    EXPECT_EQ(hero.getAttacPower(), 1);
    EXPECT_EQ(hero.getLevel(), 1);
    EXPECT_EQ(hero.getEXP(), 0);
}

TEST(HeroTest, TakeDamage) {
    QuestManager qm;
    Hero hero("Lancelot", 100, 15, 5, qm);
    hero.takeDamage(20);
    EXPECT_EQ(hero.getHealt(), 85);
    hero.takeDamage(100);
    EXPECT_EQ(hero.getHealt(), 0);
}

TEST(HeroTest, AttackMonster) {
    QuestManager qm;
    Hero hero("Galahad", 100, 25, 10, qm);
    Monster monster("Dragon", 50, 15, 5, Ability::FireBreath);

    hero.attack(&monster);
    EXPECT_EQ(monster.getHealt(), 30);
    hero.attack(&monster); 
    EXPECT_EQ(monster.getHealt(),10);
    hero.attack(&monster);
    EXPECT_EQ(hero.getEXP(), 20);
}

TEST(HeroTest, UsePotion) {
    QuestManager qm;
    Hero hero("Percival", 50, 10, 5, qm);
    auto potion = std::make_shared<Item>(Type::Potion, "Health Potion", "Restores 30 HP", 30);

    hero.addItem(potion);
    EXPECT_EQ(hero.getInventorySize(), 1);
    hero.useItem(0);
    EXPECT_EQ(hero.getHealt(), 80);
    EXPECT_EQ(hero.getInventorySize(), 0);
}

TEST(HeroTest, UsePotionExceedMaxHealth) {
    QuestManager qm;
    Hero hero("Tristan", Limits::HERO_MAX_HEALT - 10, 15, 5, qm);
    auto potion = std::make_shared<Item>(Type::Potion, "Big Potion", "Restores 50 HP", 50);

    hero.addItem(potion);
    hero.useItem(0);
    EXPECT_EQ(hero.getHealt(), Limits::HERO_MAX_HEALT);
}

TEST(HeroTest, UseWeapon) {
    QuestManager qm;
    Hero hero("Bors", 100, 15, 5, qm);
    auto weapon = std::make_shared<Item>(Type::Weapon, "Sword", "Increases attack by 10", 10);

    hero.addItem(weapon);
    EXPECT_EQ(hero.getInventorySize(), 1);
    hero.useItem(0);
    EXPECT_EQ(hero.getAttacPower(), 25);
    EXPECT_EQ(hero.getInventorySize(), 1);
}

TEST(HeroTest, UseWeaponExceedMaxAttack) {
    QuestManager qm;
    Hero hero("Gawain", 100, Limits::HERO_MAX_ATTAC_POWER - 10, 5, qm); // 190 attack
    auto weapon = std::make_shared<Item>(Type::Weapon, "Great Axe", "Increases attack by 20", 20);

    hero.addItem(weapon);
    hero.useItem(0);
    EXPECT_EQ(hero.getAttacPower(), Limits::HERO_MAX_ATTAC_POWER);
}

TEST(HeroTest, GainXPAndLevelUp) {
    QuestManager qm;
    Hero hero("Bedivere", 100, 20, 10, qm);
    hero.gainXP(50);
    EXPECT_EQ(hero.getEXP(), 50);
    EXPECT_EQ(hero.getLevel(), 1);
    hero.gainXP(50);
    EXPECT_EQ(hero.getEXP(), 100);
    EXPECT_EQ(hero.getLevel(), 2);
}

TEST(HeroTest, GainXPExceedMax) {
    QuestManager qm;
    Hero hero("Kay", 100, 20, 10, qm);
    hero.gainXP(Limits::HERO_MAX_XP + 100);
    EXPECT_EQ(hero.getEXP(), Limits::HERO_MAX_XP);
    EXPECT_EQ(hero.getLevel(), Limits::HERO_MAX_XP / 100 + 1);
}

TEST(HeroTest, SetAndUseMount) {
    QuestManager qm;
    Hero hero("Ector", 100, 20, 10, qm);
    Horse* horse = new Horse("Thunderbolt");

    hero.setMount(horse);
    EXPECT_EQ(hero.getMount()->getName(), "Thunderbolt");
    EXPECT_EQ(hero.getMount()->getCondition(), 100);
    hero.getMount()->useMount(50);
    EXPECT_EQ(hero.getMount()->getCondition(), 83);
    hero.getMount()->useMount(301);
    EXPECT_EQ(hero.getMount()->getCondition(), 83);
}

TEST(HeroTest, InteractWithNPC) {
    QuestManager qm;
    Hero hero("Gareth", 100, 20, 10, qm);
    auto quest = std::make_shared<Quest>("Slay Dragon", "Kill the dragon", 50);
    NPC npc("Villager", "Please help us!", quest);

    std::stringstream input("1\n");
    std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
    std::cin.rdbuf(oldCin);
    hero.interact(&npc);
    EXPECT_EQ(hero.getActiveQuests()[0]->getTitle(), "Slay Dragon");
    EXPECT_EQ(hero.getActiveQuests().size(), 1);
}

TEST(HeroTest, DistributeRewards) {
    QuestManager qm;
    Hero hero("Lionel", 100, 20, 10, qm);
    auto item = std::make_shared<Item>(Type::Potion, "Elixir", "Restores 20 HP", 20);
    auto quest = std::make_shared<Quest>("Find Treasure", "Locate the chest", 30, item);

    qm.assignQuest(quest);
    quest->complete();
    qm.checkQuestCompletion();
    qm.distributeRewards(&hero);

    EXPECT_EQ(hero.getEXP(), 30);
    EXPECT_EQ(hero.getInventorySize(), 1);
    
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}