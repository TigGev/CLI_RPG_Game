#ifndef ITEM_H
#define ITEM_H
#include <string>

enum class Type {Potion, Weapon, Key};

inline bool operator==(Type lhs, Type rhs) {
    return static_cast<int>(lhs) == static_cast<int>(rhs);
}

class Item {
    private:
        Type m_type;
        std::string m_name;
        std::string m_description;
        int m_value;
    public:
        Item(Type type, const std::string& name, const std::string& description, int value);
        ~Item();
        std::string getName() const;
        std::string getDescription() const;
        const Type& getType() const;
        int getValue() const;
        // virtual void use() = 0;
};
#endif