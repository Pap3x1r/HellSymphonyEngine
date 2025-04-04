#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <deque>
#include <chrono>

using namespace std;


class QTEManager {
    QTEManager() : isActive(false), timeLimit(0.0f) {}
    void success();
    void fail();

    vector<char> sequence;
    deque<char> inputs;
    size_t currentIndex;
    float timeLimit;
    chrono::steady_clock::time_point startTime;
    bool isActive;
public:

    static QTEManager* instance;

    static QTEManager* getInstance() {
        if (instance == nullptr) {
            instance = new QTEManager();
        }

        return instance;
    }

    void startQTE(const vector<char>& sequence, float timeLimit);
    void handleInput(char key);
    void update();
    bool getActive() const { return isActive; }
    void setActive(bool value) { isActive = value; }
};