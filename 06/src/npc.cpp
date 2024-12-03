#include "npc.h"
#include "visitor.h"

void Squirrel::accept(Visitor& visitor) {
    visitor.visit(*this);
}

std::string Squirrel::getType() const {  
    return "Squirrel";
}

void Werewolf::accept(Visitor& visitor) {
    visitor.visit(*this);
}

std::string Werewolf::getType() const {  
    return "Werewolf";
}

void Druid::accept(Visitor& visitor) {
    visitor.visit(*this);
}

std::string Druid::getType() const {  
    return "Druid";
}
