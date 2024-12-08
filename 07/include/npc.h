#ifndef NPC_H
#define NPC_H

#include <string>
#include <iostream>
#include <mutex>


class NPC {
public:
    NPC(const std::string& name, int x, int y)
        : name(name), x(x), y(y), alive(true) {}
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;

    std::string getName() const { return name; }

    
    int getX() const {
        std::lock_guard<std::mutex> lock(posMutex);
        return x;
    }

    int getY() const {
        std::lock_guard<std::mutex> lock(posMutex);
        return y;
    }

    bool isAlive() const { return alive; }
    void setAlive(bool status) { alive = status; }

    
    void setPosition(int newX, int newY) {
        std::lock_guard<std::mutex> lock(posMutex);
        x = newX;
        y = newY;
    }

    friend std::ostream& operator<<(std::ostream& os, const NPC& npc) {
        os << "NPC: " << npc.name << " at (" << npc.x << ", " << npc.y << ")";
        return os;
    }

protected:
    std::string name;
    int x, y;
    bool alive;
    mutable std::mutex posMutex; 
};


class Squirrel : public NPC {
public:
    Squirrel(const std::string& name, int x, int y) : NPC(name, x, y) {}
    std::string getType() const override;
};


class Druid : public NPC {
public:
    Druid(const std::string& name, int x, int y) : NPC(name, x, y) {}
    std::string getType() const override;
};


class Werewolf : public NPC {
public:
    Werewolf(const std::string& name, int x, int y) : NPC(name, x, y) {}
    std::string getType() const override;
};

#endif 
