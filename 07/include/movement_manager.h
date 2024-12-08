#ifndef MOVEMENT_MANAGER_H
#define MOVEMENT_MANAGER_H

#include "dungeon.h"
#include "utils.h" 
#include "tasks.h" 
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>

class MovementManager {
public:
    MovementManager(Dungeon& dungeon, std::mutex& battleQueueMutex, std::queue<BattleTask>& battleQueue, std::atomic<bool>& running);
    void start();
    void join();

private:
    void run();

    Dungeon& dungeon;
    std::mutex& battleQueueMutex;
    std::queue<BattleTask>& battleQueue;
    std::atomic<bool>& running;
    std::thread movementThread;
};

#endif 
