#ifndef UTILITY_H
#define UTILITY_H
#include <string>
#include <iostream>

namespace Utility {
    int getValidatedInput(int min, int max);
    void saveGame(const std::string& filename);
    void loadGame(const std::string& filename);
    int generateRandom(int min, int max);

    void printRed(const std::string& msg);
    void printGreen(const std::string& msg);
    void printYell(const std::string& msg);
    void printBlue(const std::string& msg); 
    void printPurple(const std::string& msg); 

    void printHealt(int healt);
    void printAttack(int attack);
    void printDefence(int defence);
}

namespace Limits {
    const int HERO_PRIM_HEALT = 100;
    const int HERO_MAX_HEALT = 1000;
    const int HERO_MAX_DEFENCE = 100;
    const int HERO_PRIM_DEFENCE = 5;
    const int HERO_PRIM_ATTAC_POWER = 15;
    const int HERO_MAX_ATTAC_POWER = 200;
    const int HERO_PRIM_LEVEL  = 15;
    const int HERO_MAX_LEVEL = 200;
    const int HERO_PRIM_XP  = 0;
    const int HERO_MAX_XP = 10000;

    const int MONSTER_PRIM_HEALT = 50;
    const int MONSTER_MAX_HEALT = 1000;
    const int MONSTER_PRIM_ATTAC_POWER = 10;
    const int MONSTER_MAX_ATTAC_POWER = 100;
    const int MOSTER_PRIM_DEFENCE = 5;
    const int MOSTER_MAX_DEFENCE = 50;


    const int NPC_PRIM_HEALT = 30;
    const int NPC_MAX_HEALT = 100;
    const int NPC_PRIM_ATTAC_POWER = 0;
    const int NPC_MAX_ATTAC_POWER = 0;
    const int NPC_PRIM_DEFENCE = 0;
    const int NPC_MAX_DEFENCE = 0;

    const int MIN_LEVEL = 1;
    const int MAX_LEVEL = 100;
}

#endif