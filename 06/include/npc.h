#ifndef NPC_H
#define NPC_H

#include <string>
#include <iostream>  

class Visitor;

class NPC {
public:
    NPC(const std::string& name, int x, int y) : name(name), x(x), y(y), alive(true) {}
    virtual ~NPC() = default;

    virtual void accept(Visitor& visitor) = 0;

    std::string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    bool isAlive() const { return alive; }
    void setAlive(bool status) { alive = status; }

    friend std::ostream& operator<<(std::ostream& os, const NPC& npc) {
        os << "NPC: " << npc.name << " at (" << npc.x << ", " << npc.y << ")";
        return os;
    }

private:
    std::string name;
    int x, y;
    bool alive;
};

class Squirrel : public NPC {
public:
    Squirrel(const std::string& name, int x, int y) : NPC(name, x, y) {}
    void accept(Visitor& visitor) override;
};

class Werewolf : public NPC {
public:
    Werewolf(const std::string& name, int x, int y) : NPC(name, x, y) {}
    void accept(Visitor& visitor) override;
};

class Druid : public NPC {
public:
    Druid(const std::string& name, int x, int y) : NPC(name, x, y) {}
    void accept(Visitor& visitor) override;
};

#endif 
