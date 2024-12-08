#ifndef VISITOR_H
#define VISITOR_H

#include "observer.h"
#include "npc.h"
#include "dungeon.h"
#include "utils.h"
#include <vector>
#include <cmath>
#include <string>
#include <memory> 

class Dungeon; 

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
    BattleVisitor(int distance, Observer& observer, Dungeon& dungeon);
    virtual ~BattleVisitor() override; 

    void visit(Squirrel& squirrel) override;
    void visit(Werewolf& werewolf) override;
    void visit(Druid& druid) override;

    void addNPC(std::shared_ptr<NPC> npc); 

private:
    bool isInRange(const NPC& npc1, const NPC& npc2) const;

    int distance;                
    Observer& observer;          
    Dungeon& dungeon;
    std::vector<std::shared_ptr<NPC>> npcs;      
};

#endif 
