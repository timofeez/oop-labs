#include "dungeon.h"
#include "visitor.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void Dungeon::addNPC(std::shared_ptr<NPC> npc) {
    npcs.push_back(npc);
}

void Dungeon::printNPCs() const {
    for (const auto& npc : npcs) {
        std::cout << "Type: " << npc->getType() << ", Name: " << npc->getName() << ", Coordinates: (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
    }
}

void Dungeon::saveToFile(const std::string &filename) const {
    std::ofstream file(filename);
    for (const auto& npc : npcs) {
        file << npc->getType() << " " << npc->getName() << " " << npc->getX() << " " << npc->getY() << std::endl;
    }
}

void Dungeon::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    std::string type, name;
    int x, y;
    while (file >> type >> name >> x >> y) {
        if (type == "Squirrel") {
            addNPC(std::make_shared<Squirrel>(name, x, y));
        } else if (type == "Werewolf") {
            addNPC(std::make_shared<Werewolf>(name, x, y));
        } else if (type == "Druid") {
            addNPC(std::make_shared<Druid>(name, x, y));
        }
    }
}

void Dungeon::battle(int distance, Observer& observer) {
    BattleVisitor visitor(distance, observer);
    for (auto& npc : npcs) {
        visitor.addNPC(npc.get());
    }
    for (auto& npc : npcs) {
        npc->accept(visitor);
    }
    
    npcs.erase(std::remove_if(npcs.begin(), npcs.end(), [](const std::shared_ptr<NPC>& npc) {
        return !npc->isAlive();
    }), npcs.end());
}

std::shared_ptr<NPC> Dungeon::popNPC(int index) {
    if (index < 0 || index >= npcs.size()) {
        throw std::out_of_range("Index out of range");
    }
    auto npc = npcs[index];
    npcs.erase(npcs.begin() + index);
    return npc;
}
