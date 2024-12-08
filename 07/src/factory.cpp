#include "factory.h"


std::shared_ptr<NPC> SquirrelFactory::createNPC(const std::string& name, int x, int y) {
    return std::make_shared<Squirrel>(name, x, y);
}


std::shared_ptr<NPC> DruidFactory::createNPC(const std::string& name, int x, int y) {
    return std::make_shared<Druid>(name, x, y);
}


std::shared_ptr<NPC> WerewolfFactory::createNPC(const std::string& name, int x, int y) {
    return std::make_shared<Werewolf>(name, x, y);
}
