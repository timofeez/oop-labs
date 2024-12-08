#include "movement_manager.h"
#include "utils.h" 
#include <chrono>
#include <cmath>
#include <algorithm>

MovementManager::MovementManager(Dungeon& dungeon, std::mutex& battleQueueMutex, std::queue<BattleTask>& battleQueue, std::atomic<bool>& running)
    : dungeon(dungeon), battleQueueMutex(battleQueueMutex), battleQueue(battleQueue), running(running) {}

void MovementManager::start() {
    movementThread = std::thread(&MovementManager::run, this);
}

void MovementManager::join() {
    if (movementThread.joinable()) {
        movementThread.join();
    }
}

void MovementManager::run() {
    const int MAP_WIDTH = 100;
    const int MAP_HEIGHT = 100;

    while (running) {
        auto npcs = dungeon.getNPCs();
        for(auto& npc : npcs){
            if(!npc->isAlive()) continue;

            int moveDistance;
            if(npc->getType() == "Squirrel"){
                moveDistance = 5;
            }
            else if(npc->getType() == "Druid"){
                moveDistance = 10;
            }
            else { 
                moveDistance = 40;
            }

            int dx = getRandomNumber(-moveDistance, moveDistance);
            int dy = getRandomNumber(-moveDistance, moveDistance);

            int newX = std::clamp(npc->getX() + dx, 0, MAP_WIDTH);
            int newY = std::clamp(npc->getY() + dy, 0, MAP_HEIGHT);

            npc->setPosition(newX, newY);
        }

        
        for(size_t i = 0; i < npcs.size(); ++i){
            for(size_t j = i + 1; j < npcs.size(); ++j){
                if(!npcs[i]->isAlive() || !npcs[j]->isAlive()) continue;
                int dx = npcs[i]->getX() - npcs[j]->getX();
                int dy = npcs[i]->getY() - npcs[j]->getY();
                double distance = std::sqrt(dx * dx + dy * dy);

                if(canAttack(npcs[i]->getType(), npcs[j]->getType(), distance)){
                    std::lock_guard<std::mutex> qlock(battleQueueMutex);
                    battleQueue.push(BattleTask{npcs[i], npcs[j]});
                }

                if(canAttack(npcs[j]->getType(), npcs[i]->getType(), distance)){
                    std::lock_guard<std::mutex> qlock(battleQueueMutex);
                    battleQueue.push(BattleTask{npcs[j], npcs[i]});
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    }
}
