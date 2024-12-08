#include <gtest/gtest.h>
#include "npc.h"
#include "dungeon.h"
#include "factory.h"
#include "observer.h"
#include "movement_manager.h"
#include "battle_manager.h"
#include "utils.h"
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include <sstream>


TEST(MovementManagerTest, MoveNPCs) {
    Dungeon dungeon;
    auto npc = std::make_shared<Squirrel>("Squirrel", 10, 10);
    dungeon.addNPC(npc);

    std::mutex battleQueueMutex;
    std::queue<BattleTask> battleQueue;
    std::atomic<bool> running(true);

    MovementManager movementManager(dungeon, battleQueueMutex, battleQueue, running);

    
    EXPECT_EQ(npc->getX(), 10);
    EXPECT_EQ(npc->getY(), 10);

    
    movementManager.start();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    running = false;
    movementManager.join();

    
    EXPECT_NE(npc->getX(), 10);
    EXPECT_NE(npc->getY(), 10);
}



TEST(FullScenarioTest, Integration) {
    Dungeon dungeon;
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("test_log.txt");
    std::vector<std::shared_ptr<Observer>> observers = {consoleObserver, fileObserver};

    std::mutex battleQueueMutex;
    std::queue<BattleTask> battleQueue;
    std::atomic<bool> running(true);

    SquirrelFactory squirrelFactory;
    DruidFactory druidFactory;
    WerewolfFactory werewolfFactory;

    
    for (int i = 0; i < 10; ++i) {
        int x = getRandomNumber(0, 100);
        int y = getRandomNumber(0, 100);
        int type = getRandomNumber(0, 2);
        std::shared_ptr<NPC> npc;
        if (type == 0) {
            npc = squirrelFactory.createNPC("Squirrel_" + std::to_string(i), x, y);
        } else if (type == 1) {
            npc = druidFactory.createNPC("Druid_" + std::to_string(i), x, y);
        } else {
            npc = werewolfFactory.createNPC("Werewolf_" + std::to_string(i), x, y);
        }
        dungeon.addNPC(npc);
    }

    
    MovementManager movementManager(dungeon, battleQueueMutex, battleQueue, running);
    BattleManager battleManager(dungeon, battleQueueMutex, battleQueue, *consoleObserver, running);

    movementManager.start();
    battleManager.start();

    
    std::thread printThread([&]() {
        for (int i = 0; i < 5; ++i) {
            std::stringstream ss;
            ss << "Текущее состояние карты:\n";
            dungeon.printNPCs(ss);
            ss << "----------------------------------";
            for (auto &observer : observers) {
                observer->update(ss.str());
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        running = false;
    });

    printThread.join();
    movementManager.join();
    battleManager.join();

    
    std::stringstream ss;
    dungeon.printNPCs(ss);
    EXPECT_GT(ss.str().size(), 0);
}


TEST(UtilsTest, RandomNumber) {
    int min = 10, max = 20;
    for (int i = 0; i < 100; ++i) {
        int random = getRandomNumber(min, max);
        EXPECT_GE(random, min);
        EXPECT_LE(random, max);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
