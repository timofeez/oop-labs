#include "dungeon.h"
#include "factory.h"
#include "observer.h"
#include <iostream>

int main() {
    Dungeon dungeon;
    ConsoleObserver consoleObserver;
    FileObserver fileObserver("log.txt");

    NPCFactory* squirrelFactory = new SquirrelFactory();
    NPCFactory* werewolfFactory = new WerewolfFactory();
    NPCFactory* druidFactory = new DruidFactory();

    std::cout << "Type 'help' to get info" << std::endl;

    while (true) {
        std::cout << "\nfigure> ";
        std::string input;
        std::cin >> input;

        if (input == "exit")
            break;

        if (input == "add") {
            int param;
            std::string name;
            int x, y;
            std::cout << "Enter type (1 - Squirrel, 2 - Werewolf, 3 - Druid): ";
            std::cin >> param;
            std::cout << "Enter name: ";
            std::cin >> name;
            std::cout << "Enter x coordinate: ";
            std::cin >> x;
            std::cout << "Enter y coordinate: ";
            std::cin >> y;

            if (param == 1) {
                auto squirrel = squirrelFactory->createNPC(name, x, y);
                dungeon.addNPC(squirrel);
            } else if (param == 2) {
                auto werewolf = werewolfFactory->createNPC(name, x, y);
                dungeon.addNPC(werewolf);
            } else if (param == 3) {
                auto druid = druidFactory->createNPC(name, x, y);
                dungeon.addNPC(druid);
            } else {
                std::cout << "Invalid type!" << std::endl;
            }
        } else if (input == "list") {
            dungeon.printNPCs();
        } else if (input == "save") {
            std::string filename;
            std::cout << "Enter filename: ";
            std::cin >> filename;
            dungeon.saveToFile(filename);
        } else if (input == "load") {
            std::string filename;
            std::cout << "Enter filename: ";
            std::cin >> filename;
            dungeon.loadFromFile(filename);
        } else if (input == "battle") {
            int distance;
            std::cout << "Enter battle distance: ";
            std::cin >> distance;
            dungeon.battle(distance, consoleObserver);
            dungeon.battle(distance, fileObserver);
        } else if (input == "remove") {
            int index;
            std::cout << "Enter index of NPC to remove: ";
            std::cin >> index;
            try {
                auto popped = dungeon.popNPC(index);
                std::cout << *popped << " removed" << std::endl;
            } catch (const std::out_of_range&) {
                std::cout << "Invalid index!" << std::endl;
            }
        } else if (input == "help") {
            std::cout << "Commands:" << std::endl;
            std::cout << "  add : Add a new NPC" << std::endl;
            std::cout << "  list : List all NPCs" << std::endl;
            std::cout << "  save : Save NPCs to file" << std::endl;
            std::cout << "  load : Load NPCs from file" << std::endl;
            std::cout << "  battle : Start battle mode" << std::endl;
            std::cout << "  remove : Remove an NPC by index" << std::endl;
            std::cout << "  exit : Exit the program" << std::endl;
        } else {
            std::cout << "Unknown command!" << std::endl;
        }
    }

    delete squirrelFactory;
    delete werewolfFactory;
    delete druidFactory;

    return 0;
}