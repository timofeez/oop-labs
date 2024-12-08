#include "dungeon.h"
#include "factory.h"
#include "observer.h"
#include "npc.h" 
#include <thread>
#include <mutex>
#include <queue>
#include <random>
#include <chrono>
#include <atomic>
#include <iostream>
#include <sstream>
#include <algorithm>


const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;


int getRandomNumber(int min, int max) {
    static thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}


bool canAttack(const std::string& attackerType, const std::string& targetType, int distance) {
    if (attackerType == "Squirrel") {
        if (targetType == "Druid" || targetType == "Werewolf") {
            return distance <= 5;
        }
    }
    else if (attackerType == "Werewolf") {
        if (targetType == "Druid") {
            return distance <= 5;
        }
    }
    
    return false;
}

int main() {
    Dungeon dungeon;
    ConsoleObserver consoleObserver;

    std::mutex battleQueueMutex; 
    std::queue<BattleTask> battleQueue; 
    std::atomic<bool> running(true); 

    
    SquirrelFactory squirrelFactory;
    DruidFactory druidFactory;
    WerewolfFactory werewolfFactory;

    
    for(int i = 0; i < 50; ++i){
        int x = getRandomNumber(0, MAP_WIDTH);
        int y = getRandomNumber(0, MAP_HEIGHT);
        int type = getRandomNumber(0, 2);
        std::shared_ptr<NPC> npc;
        if(type == 0){
            npc = squirrelFactory.createNPC("Squirrel_" + std::to_string(i), x, y);
        }
        else if(type == 1){
            npc = druidFactory.createNPC("Druid_" + std::to_string(i), x, y);
        }
        else{
            npc = werewolfFactory.createNPC("Werewolf_" + std::to_string(i), x, y);
        }
        dungeon.addNPC(npc);
    }

    
    std::thread movementThread([&]() {
        while(running){
            
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

            
            npcs = dungeon.getNPCs(); 
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
    });

    
    std::thread battleThread([&]() {
        while(running){
            BattleTask task;
            bool hasTask = false;
            {
                std::lock_guard<std::mutex> qlock(battleQueueMutex);
                if(!battleQueue.empty()){
                    task = battleQueue.front();
                    battleQueue.pop();
                    hasTask = true;
                }
            }

            if(hasTask){
                
                if(task.attacker->isAlive() && task.target->isAlive()){
                    
                    int attack = getRandomNumber(1, 6);
                    int defense = getRandomNumber(1, 6);

                    if(attack > defense){
                        
                        consoleObserver.update(task.attacker->getName() + " убивает " + task.target->getName());
                        task.target->setAlive(false);
                    }
                }
            }
            else{
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
            }
        }
    });

    
    std::thread printThread([&]() {
        while(running){
            std::stringstream ss;
            ss << "Текущее состояние карты:" << std::endl;
            dungeon.printNPCs(ss);
            ss << "----------------------------------";
            consoleObserver.update(ss.str());
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    
    std::this_thread::sleep_for(std::chrono::seconds(30));
    running = false;

    
    movementThread.join();
    battleThread.join();
    printThread.join();

    
    {
        std::stringstream ss;
        ss << "Список выживших NPC:" << std::endl;
        dungeon.printNPCs(ss);
        ss << "----------------------------------";
        consoleObserver.update(ss.str());
    }

    return 0;
}
