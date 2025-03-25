#include "../../headers/inventory/Item.h"
#include "../../headers/utility/Utility.h"

Item::Item(Type type, const std::string& name, const std::string& description, int value)
    : m_type(type), m_name(name), m_description(description), m_value(value) {}

std::string Item::getName() const {return m_name;}

std::string Item::getDescription() const {return m_description;}

const Type& Item::getType() const {return m_type;}

int Item::getValue() const {return m_value;}
