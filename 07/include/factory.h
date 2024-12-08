#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include <string>
#include "npc.h"


class NPCFactory {
public:
    virtual std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) = 0;
    virtual ~NPCFactory() = default;
};


class SquirrelFactory : public NPCFactory {
public:
    std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) override;
};


class DruidFactory : public NPCFactory {
public:
    std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) override;
};


class WerewolfFactory : public NPCFactory {
public:
    std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) override;
};

#endif 
