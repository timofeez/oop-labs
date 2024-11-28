#ifndef VISITOR_H
#define VISITOR_H

#include <cmath>
#include <vector>
#include "npc.h"
#include "observer.h"

class Visitor {
public:
    virtual void visit(Squirrel& squirrel) = 0;
    virtual void visit(Werewolf& werewolf) = 0;
    virtual void visit(Druid& druid) = 0;
    virtual ~Visitor() = default;
};

class BattleVisitor : public Visitor {
public:
    BattleVisitor(int distance, Observer& observer) : distance(distance), observer(observer) {}

    void visit(Squirrel& squirrel) override {
        for (auto& npc : npcs) {
            if (npc != &squirrel && npc->isAlive() && isInRange(squirrel, *npc)) {
                if (dynamic_cast<Werewolf*>(npc) || dynamic_cast<Druid*>(npc)) {
                    observer.update(squirrel.getName() + " атакует " + npc->getName());
                    npc->setAlive(false);
                }
            }
        }
    }

    void visit(Werewolf& werewolf) override {
        for (auto& npc : npcs) {
            if (npc != &werewolf && npc->isAlive() && isInRange(werewolf, *npc)) {
                if (dynamic_cast<Druid*>(npc)) {
                    observer.update(werewolf.getName() + " атакует " + npc->getName());
                    npc->setAlive(false);
                }
            }
        }
    }

    void visit(Druid& druid) override {
        
    }

    void addNPC(NPC* npc) {
        npcs.push_back(npc);
    }

private:
    bool isInRange(const NPC& npc1, const NPC& npc2) const {
        int dx = npc1.getX() - npc2.getX();
        int dy = npc1.getY() - npc2.getY();
        return std::sqrt(dx * dx + dy * dy) <= distance;
    }

    int distance;
    Observer& observer;
    std::vector<NPC*> npcs;
};

#endif 
