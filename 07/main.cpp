#include "dungeon.h"
#include "factory.h"
#include "observer.h"
#include "npc.h" 
#include "movement_manager.h"
#include "battle_manager.h"
#include "utils.h"
#include "tasks.h"

#include <thread>
#include <mutex>
#include <queue>
#include <random>
#include <chrono>
#include <atomic>
#include <iostream>
#include <sstream>
#include <memory> 

int main() {
    
    Dungeon dungeon;
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("game_log.txt");
    std::vector<std::shared_ptr<Observer>> observers = {consoleObserver, fileObserver};

    
    std::mutex battleQueueMutex; 
    std::queue<BattleTask> battleQueue; 
    std::atomic<bool> running(true); 

    
    SquirrelFactory squirrelFactory;
    DruidFactory druidFactory;
    WerewolfFactory werewolfFactory;

    
    for(int i = 0; i < 50; ++i){
        int x = getRandomNumber(0, 100);
        int y = getRandomNumber(0, 100);
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

    
    MovementManager movementManager(dungeon, battleQueueMutex, battleQueue, running);
    BattleManager battleManager(dungeon, battleQueueMutex, battleQueue, *consoleObserver, running);

    
    movementManager.start();
    battleManager.start();

    
    std::thread printThread([&]() {
        while(running){
            std::stringstream ss;
            ss << "Текущее состояние карты:" << std::endl;
            dungeon.printNPCs(ss);
            ss << "----------------------------------";
            for(auto& observer : observers){
                observer->update(ss.str());
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    
    std::this_thread::sleep_for(std::chrono::seconds(30));
    running = false;

    
    movementManager.join();
    battleManager.join();
    printThread.join();

    
    std::stringstream ss;
    ss << "Список выживших NPC:" << std::endl;
    dungeon.printNPCs(ss);
    ss << "----------------------------------";
    for(auto& observer : observers){
        observer->update(ss.str());
    }

    return 0;
}
