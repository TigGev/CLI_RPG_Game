# Adventure Quest - CLI RPG Game

## Objective
Design and implement a fully interactive Command-Line Interface (CLI) Role-Playing Game (RPG) named "Adventure Quest", leveraging C++ concepts such as abstract classes, interfaces (pure virtual functions), dynamic polymorphism, and Run-Time Type Identification (RTTI). The game provides an engaging experience where players explore a fantasy world, interact with various characters, engage in turn-based combat, complete quests, and manage their character's progression.

## Game Description
"Adventure Quest" immerses the player in a fantasy world filled with heroes, monsters, and non-playable characters (NPCs). The player takes on the role of a hero who explores different locations (e.g., forests, dungeons, villages), interacts with NPCs to uncover the storyline and receive quests, and engages in turn-based battles with monsters. Choices made by the player dynamically affect the game flow, storyline progression, and character development.

## Project Structure

CLI_RPG_Game/
├── CLI/
│   └── headers/
│       ├── characters/
│       │   ├── Character.h
│       │   ├── Combatable.h
│       │   ├── Hero.h
│       │   ├── Interactable.h
│       │   ├── Monster.h
│       │   └── NPC.h
│       ├── gameWorld/
│       │   ├── GameTime.h
│       │   ├── GameWorld.h
│       │   ├── Location.h
│       │   └── Reputation.h
│       ├── inventory/
│       │   ├── Inventory.h
│       │   └── Item.h
│       ├── moving/
│       │   ├── Airship.h
│       │   ├── Boat.h
│       │   ├── Horse.h
│       │   ├── Mount.h
│       │   └── Portal.h
│       ├── quests/
│       │   ├── Quest.h
│       │   └── QuestManager.h
│       └── utility/
│           ├── Quest.h
│           └── QuestManager.h
├── src/
│   ├── Main.cpp
│   ├── gameWorld/
│   │   ├── GameTime.cpp
│   │   ├── GameWorld.cpp
│   │   └── Location.cpp
│   ├── moving/
│   │   ├── Airship.cpp
│   │   ├── Boat.cpp
│   │   ├── Horse.cpp
│   │   ├── Mount.cpp
│   │   └── Portal.cpp
│   ├── utility/
│   │   └── Utility.cpp
│   ├── character/
│   │   ├── Character.cpp
│   │   ├── Hero.cpp
│   │   ├── Monster.cpp
│   │   └── NPC.cpp
│   ├── inventory/
│   │   ├── Inventory.cpp
│   │   └── Item.cpp
│   └── quests/
│       ├── QuestManager.cpp
│       └── Quest.cpp
├── tests/
│   ├── gameTime_test.cpp
│   ├── hero_test.cpp
│   ├── monster_test.cpp
│   ├── gameWorld_test.cpp
│   ├── location_test.cpp
│   └── npc_test.cpp
├── Makefile
└── README.md


## Game Entities
### Hero
- **Description**: The player-controlled character who can interact, fight, level up, manage an inventory, and gain new skills.
- **Subtypes (optional)**: Warrior (high health, melee-focused), Mage (magic-focused, ranged attacks), Rogue (stealth and critical hits).
- **Attributes**: Health, attack power, defense, experience points (XP), level, inventory (items like potions, weapons), and skills/spells.

### Monster
- **Description**: Hostile entities that the hero encounters and battles.
- **Subtypes**: Goblin (weak but fast), Troll (high health, slow), Dragon (strong, with special abilities like fire breath).
- **Attributes**: Health, attack power, defense, special abilities (e.g., poison attack, area damage).

### NPC
- **Description**: Non-hostile characters that provide story elements, quests, or items.
- **Subtypes**: Villager (provides quests), Merchant (sells items), Healer (restores health).
- **Attributes**: Name, dialogue, associated quest or items.

## Gameplay Mechanics
### Exploration
- The game world consists of multiple textual environments (e.g., "Enchanted Forest", "Dark Dungeon", "Quiet Village").
- Players navigate between locations via a CLI menu (e.g., "1. Move to Forest", "2. Move to Village").
- Each location contains unique encounters (e.g., meeting an NPC, finding an item, or encountering a monster).

### Interactions
- Players can interact with NPCs and certain objects (e.g., treasure chests) using textual prompts.
- RTTI varies interactions based on character types (e.g., a Merchant NPC might offer different dialogue to a Warrior than to a Mage).
- **Example**: Talking to a Villager NPC might yield a quest like "Slay the Troll in the Dark Dungeon."

### Combat
- Combat is turn-based, with the player selecting actions (e.g., "Attack", "Use Skill", "Defend", "Use Item") via a CLI menu.
- Dynamic polymorphism handles combat between heroes and monsters, allowing for diverse behaviors (e.g., a Troll might have a chance to counterattack).
- RTTI applies type-specific effects (e.g., a Mage's spell deals bonus damage to a Dragon).
- **Example Combat Flow**:
A Troll appears! Health: 80 | Attack: 12
Your turn:

Attack
Use Fireball (Mage skill)
Defend
Use Potion Choose an action: 2 You cast Fireball! Deals 25 damage to Troll. Troll attacks! Deals 8 damage to you.


### Inventory and Skills
- The hero has an inventory to store items (e.g., Health Potion, Sword, Magic Amulet).
- Items can be used in combat (e.g., a potion restores health) or during exploration (e.g., a key unlocks a door).
- Skills/spells are tied to the hero's type (e.g., Warrior: "Power Strike", Mage: "Fireball", Rogue: "Stealth Attack").

### Story and Quests
- A simple storyline with branching dialogues and quests.
- Quests involve objectives like "Defeat 3 Goblins", "Find the Lost Amulet", or "Rescue a Villager from the Dungeon".
- Completing quests rewards the hero with XP, items, or story progression.
- **Example Quest Flow**:
Villager: "A Troll has been terrorizing our village! Please slay it."
Quest Accepted: Slay the Troll in the Dark Dungeon.
[After defeating the Troll]
Villager: "Thank you, hero! Take this Magic Amulet as a reward."
Quest Completed! Gained 50 XP and Magic Amulet.

### Progression and Saving
- The hero gains XP from battles and quests, leveling up to improve stats (e.g., health, attack power).
- A save/load system stores the game state (hero stats, inventory, quest progress) in a file and loads it back.

## Technical Requirements
### Abstract Class: Character
- **Base class** for all entities (Hero, Monster, NPC).
- **Data members**: name, health, attackPower, defense.
- **Pure virtual functions**: `displayStats()`, `takeDamage()`.
- **Virtual destructor** for proper cleanup of derived classes.

### Interfaces
- **Interactable**: Pure virtual functions like `interact(Character* target)`, `getDialogue()`.
- **Combatable**: Pure virtual functions like `attack(Character* target)`, `useAbility(Character* target)`.

### Dynamic Polymorphism
- Uses vectors of `Character*` raw pointers to manage all entities in a location.
- Polymorphic behavior in combat (e.g., a Warrior's `attack()` differs from a Mage's `attack()`).

### RTTI
- Uses `dynamic_cast` to identify specific types (e.g., `if (dynamic_cast<Mage*>(hero)) { /* Mage-specific effect */ }`).
- Example: A Dragon might deal extra fire damage to a Warrior but take extra damage from a Mage’s spells.

### Manual Memory Management
- Uses raw pointers (`Character*`, `Item*`, etc.) for dynamically allocated objects.
- Ensures proper cleanup in destructors of classes that manage these pointers.
- Avoids memory leaks by carefully managing ownership.

## Building and Running
### Prerequisites
- A C++17-compatible compiler (e.g., g++).
- (Optional) Google Test for running tests (install via `brew install googletest` on macOS or equivalent).

### Build Instructions
1. Clone the repository or navigate to the project directory:
  `cd CLI_RPG_Game`

2. Build the main game:
    `make`
3. Run the game:
    `./CLI_Game`

Test Instructions

 Build all tests:
    `make tests`
 Run individual tests:
    `make run-gameTime  # Runs gameTime_test`
    `make run-hero      # Runs hero_test`
    `make run-monster   # Runs monster_test`
    `make run-gameWorld # Runs gameWorld_test`
    `make run-location  # Runs location_test`
    `make run-npc       # Runs npc_test`
 Alternatively, run a test manually after building:
    `./tests/hero_test`

Clean Up

 Remove all generated files:
    `make clean`
 Rebuild everything from scratch:
    `make rebuild`

Notes

 The project uses raw pointers for memory management, so ensure proper deletion to avoid memory leaks.

 Tests assume Google Test integration. If not used, modify the Makefile by removing $(GTEST_LIBS) and ensure each test file has its own main() function.

 Contributions or bug reports are welcome!
