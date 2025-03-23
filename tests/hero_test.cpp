#include <gtest/gtest.h>
#include "../headers/characters/Hero.h"
#include "../headers/characters/NPC.h"
#include "../headers/characters/Monster.h"
#include "../headers/inventory/Item.h"
#include "../headers/inventory/Inventory.h"
#include "../headers/moving/Mount.h"
#include "../headers/quests/QuestManager.h"
#include "../headers/utility/Utility.h"
#include <sstream>
#include <iostream>



// Item
Item::Item(Type type, const std::string& name, const std::string& description, int value)
    : m_type(type), m_name(name), m_description(description), m_value(value) {}
Item::~Item() {}
std::string Item::getName() const { return m_name; }
std::string Item::getDescription() const { return m_description; }
const Type& Item::getType() const { return m_type; }
int Item::getValue() const { return m_value; }

// Inventory
Inventory::Inventory() {}
Inventory::~Inventory() {
    for (Item* item : items) delete item;
}
void Inventory::addItem(Item* item) { items.push_back(item); }
void Inventory::removeItem(int index) {
    if (index >= 0 && index < items.size()) {
        delete items[index];
        items.erase(items.begin() + index);
    }
}
Item* Inventory::getItem(int index) const {
    return (index >= 0 && index < items.size()) ? items[index] : nullptr;
}
std::vector<Item*> Inventory::getItems() const { return items; }
int Inventory::getSize() const { return items.size(); }

// NPC
NPC::NPC(const std::string& name, const std::string& dialogue, const std::string& quest)
    : Character(name, 50, 0, 0), dialogue(dialogue), associatedQuest(new Quest(quest)) {}
NPC::~NPC() { delete associatedQuest; }
void NPC::displayStats() const {}
void NPC::takeDamage(int damage) { m_health -= damage; if (m_health < 0) m_health = 0; }
void NPC::interact(Character* target) { std::cout << dialogue << "\n"; }
std::string NPC::getDialogue() const { return dialogue; }
Quest* NPC::getAssociatedQuest() const { return associatedQuest; }

// Monster
Monster::Monster(const std::string& name, int health, int attackPower, int defense, const std::string& ability)
    : Character(name, health, attackPower, defense), specialAbility(ability) {}
Monster::~Monster() {}
void Monster::displayStats() const {}
void Monster::takeDamage(int damage) { m_health -= damage; if (m_health < 0) m_health = 0; }
void Monster::attack(Character* target) { target->takeDamage(m_attackPower); }
void Monster::useAbility(Character* target) {}

// // Limits (заглушка)
// namespace Limits {
//     const int HERO_MAX_HEALT = 100;
//     const int HERO_MAX_ATTAC_POWER = 50;
//     const int HERO_MAX_XP = 1000;
// }

// Тестовый фикстур для Hero
class HeroTest : public ::testing::Test {
protected:
    void SetUp() override {
        qm = new QuestManager();
        hero = new Hero("Elara", 80, 15, 5, qm);
    }

    void TearDown() override {
        delete hero;
        delete qm;
    }

    Hero* hero;
    QuestManager* qm;
};

// Тест конструктора и displayStats
TEST_F(HeroTest, ConstructorAndDisplayStats) {
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    hero->displayStats();
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_TRUE(output.find("Name: Elara") != std::string::npos);
    EXPECT_TRUE(output.find("Healt: 80") != std::string::npos);
    EXPECT_TRUE(output.find("Attack: 15") != std::string::npos);
    EXPECT_TRUE(output.find("Defence: 5") != std::string::npos);
    EXPECT_TRUE(output.find("Level: 1") != std::string::npos);
    EXPECT_TRUE(output.find("XP: 0") != std::string::npos);
}

// Тест takeDamage
TEST_F(HeroTest, TakeDamage) {
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    hero->takeDamage(10);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_EQ(hero->getHealt(), 75); // 80 - (10 - 5 defense) = 75
    EXPECT_TRUE(output.find("Elara takes 5 damage") != std::string::npos);
}

// Тест takeDamage с летальным исходом
TEST_F(HeroTest, TakeDamageFatal) {
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    hero->takeDamage(100);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_EQ(hero->getHealt(), 0);
    EXPECT_TRUE(output.find("Game over! Elara is died.") != std::string::npos);
}

// Тест interact с NPC (имитация ввода)
TEST_F(HeroTest, InteractWithNPC_AcceptQuest) {
    NPC npc("Villager", "Help me!", "Slay the Troll");
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    std::istringstream iss("1\n"); // Имитация ввода "1"
    std::streambuf* oldCin = std::cin.rdbuf(iss.rdbuf());

    hero->interact(&npc);

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_TRUE(output.find("Help me!") != std::string::npos);
    EXPECT_TRUE(output.find("Quest accepted!") != std::string::npos);
    EXPECT_TRUE(output.find("Slay the Troll") != std::string::npos);
}

// Тест attack на монстра
TEST_F(HeroTest, AttackMonster) {
    Monster monster("Goblin", 30, 10, 2, "Poison Sting");
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    hero->attack(&monster);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_EQ(monster.getHealt(), 17); // 30 - (15 - 2 defense) = 17
    EXPECT_TRUE(output.find("Elara attacks Goblin for 15 damage!") != std::string::npos);
}

// Тест addItem и useItem (Potion)
TEST_F(HeroTest, AddAndUsePotion) {
    Item* potion = new Item(Type::Potion, "Health Potion", "Restores 20 HP", 20);
    hero->addItem(potion);
    EXPECT_EQ(hero->getInventorySize(), 1);

    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    hero->useItem(0);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_EQ(hero->getHealt(), 100); // 80 + 20, но не больше 100
    EXPECT_EQ(hero->getInventorySize(), 0); // Зелье удалено
    EXPECT_TRUE(output.find("Health Potion was applied") != std::string::npos);
}

// Тест useItem (Weapon)
TEST_F(HeroTest, UseWeapon) {
    Item* weapon = new Item(Type::Weapon, "Sword", "Increases attack by 10", 10);
    hero->addItem(weapon);
    EXPECT_EQ(hero->getInventorySize(), 1);

    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    hero->useItem(0);
    std::cout.rdbuf(oldCout);

    std::string output = oss.str();
    EXPECT_EQ(hero->getAttacPower(), 25); // 15 + 10 = 25
    EXPECT_EQ(hero->getInventorySize(), 1); // Оружие не удаляется
    EXPECT_TRUE(output.find("Elara equips Sword") != std::string::npos);
}

// Тест gainXP и levelUp
TEST_F(HeroTest, GainXPAndLevelUp) {
    hero->gainXP(50);
    EXPECT_EQ(hero->getEXP(), 50);
    hero->gainXP(50); // Всего 100 XP
    EXPECT_EQ(hero->getEXP(), 100);
    EXPECT_EQ(hero->getLevel(), 2); // Уровень должен увеличиться
}

// Тест setMount и getMount
TEST_F(HeroTest, SetAndGetMount) {
    Mount* horse = new Mount("Horse");
    hero->setMount(horse);
    EXPECT_EQ(hero->getMount()->getName(), "Horse");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}