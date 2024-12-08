#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <iostream>
#include <fstream>
#include <mutex>


class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};


class ConsoleObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << message << std::endl;
    }
private:
    static std::mutex coutMutex;
};


class FileObserver : public Observer {
public:
    FileObserver(const std::string& filename) : file(filename, std::ios::app), filename_(filename) {}
    void update(const std::string& message) override {
        std::lock_guard<std::mutex> lock(fileMutex);
        if (file.is_open()) {
            file << message << std::endl;
        }
        else {
            std::cerr << "Не удалось открыть файл " << filename_ << " для записи." << std::endl;
        }
    }
private:
    std::ofstream file;
    std::string filename_;
    static std::mutex fileMutex;
};

#endif 
