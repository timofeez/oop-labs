#ifndef DUNGEON_H
#define DUNGEON_H

#include <shared_mutex>
#include <vector>
#include <memory>
#include "npc.h"

class NPC;

class Dungeon {
public:
    void addNPC(std::shared_ptr<NPC> npc);
    void printNPCs(std::ostream& os) const; 
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    std::shared_ptr<NPC> popNPC(int index);
    
    std::vector<std::shared_ptr<NPC>> getNPCs() const;
    
    void removeDeadNPCs();

private:
    mutable std::shared_mutex mtx; 
    std::vector<std::shared_ptr<NPC>> npcs;
};

#endif 
