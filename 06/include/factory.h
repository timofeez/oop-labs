#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include "npc.h"

class NPCFactory {
public:
    virtual std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) = 0;
    virtual ~NPCFactory() = default;
};

class SquirrelFactory : public NPCFactory {
public:
    std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) override {
        return std::make_shared<Squirrel>(name, x, y);
    }
};

class WerewolfFactory : public NPCFactory {
public:
    std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) override {
        return std::make_shared<Werewolf>(name, x, y);
    }
};

class DruidFactory : public NPCFactory {
public:
    std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) override {
        return std::make_shared<Druid>(name, x, y);
    }
};

#endif 