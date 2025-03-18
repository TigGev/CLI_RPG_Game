#ifndef REPUTATION_H
#define REPUTATION_H
#include <string>
#include <map>

class Reputation {
    private:
        std::map<std::string, int> traits;
    public:
        Reputation();
        ~Reputation();
        void adjustReputation(const std::string& trait, int amount);
        int getReputation(const std::string& trait) const;
};
#endif