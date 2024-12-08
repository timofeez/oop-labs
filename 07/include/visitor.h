#ifndef VISITOR_H
#define VISITOR_H

#include "observer.h"
#include <vector>
#include <cmath>
#include "npc.h"


class Squirrel;
class Werewolf;
class Druid;
class NPC;


class Visitor {
public:
    virtual void visit(Squirrel& squirrel) = 0;
    virtual void visit(Werewolf& werewolf) = 0;
    virtual void visit(Druid& druid) = 0;
    virtual ~Visitor() = default; 
};


class BattleVisitor : public Visitor {
public:
    BattleVisitor(int distance, Observer& observer)
        : distance(distance), observer(observer) {}

    virtual ~BattleVisitor() override; 

    
    void visit(Squirrel& squirrel) override;
    void visit(Werewolf& werewolf) override;
    void visit(Druid& druid) override;

    
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
