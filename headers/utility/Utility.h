#ifndef UTILITY_H
#define UTILITY_H
#include <string>

namespace Utility {
    int getValidatedInput(int min, int max);
    void saveGame(const std::string& filename);
    void loadGame(const std::string& filename);
    int generateRandom(int min, int max);
}
#endif