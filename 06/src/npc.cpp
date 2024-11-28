#include "npc.h"
#include "visitor.h"

void Squirrel::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void Werewolf::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void Druid::accept(Visitor& visitor) {
    visitor.visit(*this);
}
