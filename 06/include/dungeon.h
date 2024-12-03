#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <memory>
#include "npc.h"
#include "observer.h"

class Dungeon {
public:
    void addNPC(std::shared_ptr<NPC> npc);
    void printNPCs() const;
    void saveToFile(const std::string &filename) const;
    void loadFromFile(const std::string &filename);
    void battle(int distance, Observer& observer);
    std::shared_ptr<NPC> popNPC(int index);

private:
    std::vector<std::shared_ptr<NPC>> npcs;
};

#endif 