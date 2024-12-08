#include "npc.h"
#include "visitor.h"

std::string Squirrel::getType() const {
    return "Squirrel";
}

std::string Druid::getType() const {
    return "Druid";
}

std::string Werewolf::getType() const {
    return "Werewolf";
}

void Squirrel::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void Druid::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void Werewolf::accept(Visitor& visitor) {
    visitor.visit(*this);
}
