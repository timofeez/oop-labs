#include "visitor.h"
#include "dungeon.h" 
#include "utils.h" 
#include <cmath>

BattleVisitor::BattleVisitor(int distance, Observer& observer, Dungeon& dungeon)
    : distance(distance), observer(observer), dungeon(dungeon) {}

BattleVisitor::~BattleVisitor() = default;

bool BattleVisitor::isInRange(const NPC& npc1, const NPC& npc2) const {
    int dx = npc1.getX() - npc2.getX();
    int dy = npc1.getY() - npc2.getY();
    return std::sqrt(dx * dx + dy * dy) <= distance;
}

void BattleVisitor::addNPC(std::shared_ptr<NPC> npc) {
    npcs.push_back(npc);
}

void BattleVisitor::visit(Squirrel& squirrel) {
    for (auto& npc : npcs) {
        if (npc->isAlive()) {
            
            if (npc->getType() == "Druid" || npc->getType() == "Werewolf") {
                
                if (isInRange(squirrel, *npc)) {
                    
                    int attack = getRandomNumber(1, 6);
                    int defense = getRandomNumber(1, 6);
                    std::string message = squirrel.getName() + " атакует " + npc->getName() +
                                          " (Attack: " + std::to_string(attack) +
                                          ", Defense: " + std::to_string(defense) + ")";
                    observer.update(message);
                    if (attack > defense) {
                        npc->setAlive(false);
                        message = npc->getName() + " был убит " + squirrel.getName();
                        observer.update(message);
                    }
                }
            }
        }
    }
}

void BattleVisitor::visit(Werewolf& werewolf) {
    for (auto& npc : npcs) {
        if (npc->isAlive() && npc->getType() == "Druid") {
            if (isInRange(werewolf, *npc)) {
                
                int attack = getRandomNumber(1, 6);
                int defense = getRandomNumber(1, 6);
                std::string message = werewolf.getName() + " атакует " + npc->getName() +
                                      " (Attack: " + std::to_string(attack) +
                                      ", Defense: " + std::to_string(defense) + ")";
                observer.update(message);
                if (attack > defense) {
                    npc->setAlive(false);
                    message = npc->getName() + " был убит " + werewolf.getName();
                    observer.update(message);
                }
            }
        }
    }
}

void BattleVisitor::visit(Druid& druid) {
    
}
