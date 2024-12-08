#ifndef BATTLE_MANAGER_H
#define BATTLE_MANAGER_H

#include "dungeon.h"
#include "observer.h"
#include "visitor.h"
#include "tasks.h"
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>

class BattleManager {
public:
    BattleManager(Dungeon& dungeon, std::mutex& battleQueueMutex, std::queue<BattleTask>& battleQueue, Observer& observer, std::atomic<bool>& running);
    void start();
    void join();

private:
    void run();

    Dungeon& dungeon;
    std::mutex& battleQueueMutex;
    std::queue<BattleTask>& battleQueue;
    Observer& observer;
    std::atomic<bool>& running;
    std::thread battleThread;
};

#endif 
