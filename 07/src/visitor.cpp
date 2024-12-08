
#include "visitor.h"
#include "npc.h" 


BattleVisitor::~BattleVisitor() = default;


void BattleVisitor::visit(Squirrel& squirrel) {
    for (auto& npc : npcs) {
        if (&squirrel != npc && npc->isAlive() && isInRange(squirrel, *npc)) {
            
            std::string targetType = npc->getType();
            if (targetType == "druid" || targetType == "werewolf") {
                std::string message = squirrel.getName() + " атакует " + npc->getName();
                observer.update(message);
                npc->setAlive(false);
                std::cout << message << std::endl;
            }
        }
    }
}


void BattleVisitor::visit(Werewolf& werewolf) {
    for (auto& npc : npcs) {
        if (&werewolf != npc && npc->isAlive() && isInRange(werewolf, *npc)) {
            
            std::string targetType = npc->getType();
            if (targetType == "druid") {
                std::string message = werewolf.getName() + " атакует " + npc->getName();
                observer.update(message);
                npc->setAlive(false);
                std::cout << message << std::endl;
            }
        }
    }
}


void BattleVisitor::visit(Druid& druid) {
    
}
