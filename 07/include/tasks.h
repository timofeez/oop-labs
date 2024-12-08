#ifndef TASKS_H
#define TASKS_H

#include <memory>
#include "npc.h"


struct BattleTask {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> target;
};

#endif 
