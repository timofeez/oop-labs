#include "battle_manager.h"
#include "visitor.h" 
#include "utils.h" 
#include <chrono>

BattleManager::BattleManager(Dungeon& dungeon, std::mutex& battleQueueMutex, std::queue<BattleTask>& battleQueue, Observer& observer, std::atomic<bool>& running)
    : dungeon(dungeon), battleQueueMutex(battleQueueMutex), battleQueue(battleQueue), observer(observer), running(running) {}

void BattleManager::start() {
    battleThread = std::thread(&BattleManager::run, this);
}

void BattleManager::join() {
    if (battleThread.joinable()) {
        battleThread.join();
    }
}

void BattleManager::run() {
    while (running) {
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
                
                BattleVisitor visitor(5, observer, dungeon);
                visitor.addNPC(task.target); 

                
                task.attacker->accept(visitor);
            }
        }
        else{
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
        }
    }
}
