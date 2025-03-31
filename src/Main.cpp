#include "../headers/characters/Hero.h"
#include "../headers/characters/Monster.h"
#include "../headers/characters/NPC.h"
#include "../headers/gameWorld/GameWorld.h"
#include "../headers/gameWorld/GameTime.h"
#include "../headers/moving/Portal.h"
#include "../headers/moving/Horse.h"
#include "../headers/inventory/Item.h"
#include "../headers/quests/Quest.h"
#include "../headers/quests/QuestManager.h"
#include "../headers/utility/Utility.h"
#include <iostream>
#include <memory>

int main() {
    GameTime gameTime;
    std::cout << "Day " << gameTime.getDayCount() << ", Time: Morning\n";

    auto forest = std::make_shared<Location>("Forest", "A dark and eerie forest.");
    auto village = std::make_shared<Location>("Village", "A peaceful village with friendly folk.");

    GameWorld gameWorld(forest);

    gameWorld.addLocation(village);

    QuestManager qm;
    Hero hero("Aragorn", Limits::HERO_PRIM_HEALT, Limits::HERO_PRIM_ATTAC_POWER, Limits::HERO_PRIM_DEFENCE, qm);
    forest->addEntity(std::make_shared<Hero>(hero));

    auto quest = std::make_shared<Quest>("Slay the Goblin", "Kill the goblin in the forest.", 50, 
                                         std::make_shared<Item>(Type::Potion, "Health Potion", "Restores 30 HP", 30));
    auto villager = std::make_shared<NPC>("Villager", "Please, slay the goblin tormenting our village!", quest);
    village->addEntity(villager);

    auto goblin = std::make_shared<Monster>("Goblin", Limits::MONSTER_PRIM_HEALT, Limits::MONSTER_PRIM_ATTAC_POWER, 
                                            Limits::MOSTER_PRIM_DEFENCE, Ability::BoneSmash);
    forest->addEntity(goblin);

    auto portal = std::make_shared<Portal>("Forest Portal", *forest, *village, false, "open");
    forest->addPortal(portal);

    auto sword = std::make_shared<Item>(Type::Weapon, "Iron Sword", "A sharp blade", 20);
    hero.addItem(sword);

    std::cout << "\n=== Game Start ===\n";
    hero.displayStats();

    std::cout << "\nUsing item from inventory...\n";
    hero.useItem(0);

    std::cout << "\nAttempting to use portal...\n";
    if (portal->attemptActivation("open" /*,hero.getInventory()*/)) {
        gameWorld.moveToLocation(portal->getDestination().getName());
    }

    std::cout << "\nInteracting with NPC...\n";
    hero.interact(villager.get());

    gameWorld.moveToLocation("Forest");

    std::cout << "\nFighting the goblin...\n";
    hero.attack(goblin.get());
    goblin->useAbility(&hero);
    hero.attack(goblin.get());

    quest->complete();
    qm.checkQuestCompletion();
    qm.distributeRewards(&hero);

    std::cout << "\nMounting a horse...\n";
    auto horse = std::make_shared<Horse>("Thunderbolt");

    hero.setMount(horse);
    hero.getMount()->useMount(100);

    std::cout << "\nAdvancing time...\n";
    gameTime.advanceTime(12);
    std::cout << "Day " << gameTime.getDayCount() << ", Time: ";
    switch (gameTime.getCurrentTime()) {
        case TimeOfDay::Morning: std::cout << "Morning"; break;
        case TimeOfDay::Afternoon: std::cout << "Afternoon"; break;
        case TimeOfDay::Evening: std::cout << "Evening"; break;
        case TimeOfDay::Night: std::cout << "Night"; break;
    }
    std::cout << "\n";

    std::cout << "\n=== Game End ===\n";
    hero.displayStats();

    return 0;
}