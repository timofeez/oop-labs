#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
#include <fstream>

class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

class ConsoleObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

class FileObserver : public Observer {
public:
    FileObserver(const std::string& filename) : file(filename, std::ios::app) {}
    void update(const std::string& message) override {
        file << message << std::endl;
    }

private:
    std::ofstream file;
};

#endif 