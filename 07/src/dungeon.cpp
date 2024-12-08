#include "dungeon.h"
#include "factory.h" 
#include <iostream>
#include <fstream>
#include <algorithm>



void Dungeon::addNPC(std::shared_ptr<NPC> npc) {
    std::unique_lock lock(mtx);
    npcs.push_back(npc);
}

void Dungeon::printNPCs(std::ostream& os) const {
    std::shared_lock lock(mtx);
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            os << "Type: " << npc->getType()
               << ", Name: " << npc->getName()
               << ", Coordinates: (" << npc->getX()
               << ", " << npc->getY() << ")" << std::endl;
        }
    }
}

void Dungeon::saveToFile(const std::string& filename) const {
    std::shared_lock lock(mtx);
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << " для записи." << std::endl;
        return;
    }
    for (const auto& npc : npcs) {
        file << npc->getType() << " " << npc->getName()
             << " " << npc->getX() << " " << npc->getY() << std::endl;
    }
}

void Dungeon::loadFromFile(const std::string& filename) {
    std::unique_lock lock(mtx);
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << " для чтения." << std::endl;
        return;
    }
    std::string type, name;
    int x, y;
    while (file >> type >> name >> x >> y) {
        std::shared_ptr<NPC> npc;
        if (type == "Squirrel") {
            SquirrelFactory squirrelFactory;
            npc = squirrelFactory.createNPC(name, x, y);
        }
        else if (type == "Druid") {
            DruidFactory druidFactory;
            npc = druidFactory.createNPC(name, x, y);
        }
        else if (type == "Werewolf") {
            WerewolfFactory werewolfFactory;
            npc = werewolfFactory.createNPC(name, x, y);
        }
        else {
            std::cerr << "Неизвестный тип NPC: " << type << std::endl;
            continue;
        }
        addNPC(npc);
    }
}

std::shared_ptr<NPC> Dungeon::popNPC(int index) {
    std::unique_lock lock(mtx);
    if (index < 0 || index >= static_cast<int>(npcs.size())) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    auto npc = npcs[index];
    npcs.erase(npcs.begin() + index);
    return npc;
}

std::vector<std::shared_ptr<NPC>> Dungeon::getNPCs() const {
    std::shared_lock lock(mtx);
    return npcs;
}

void Dungeon::removeDeadNPCs() {
    std::unique_lock lock(mtx);
    npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
        [](const std::shared_ptr<NPC>& npc) { return !npc->isAlive(); }),
        npcs.end());
}
