#include "QTEManager.h"

QTEManager* QTEManager::instance = nullptr;

void QTEManager::startQTE(const vector<char>& sequence, float timeLimit) {
    this->sequence = sequence;
    this->timeLimit = timeLimit;
    currentIndex = 0;
    inputs.clear();
    startTime = chrono::steady_clock::now();
    isActive = true;
}

void QTEManager::handleInput(char key) {
    if (!isActive) {
        return;
    }

    inputs.push_back(key);
    if (inputs.size() <= sequence.size()) {
        if (key == sequence[inputs.size() - 1]) {
            if (inputs.size() == sequence.size()) {
                success();
            }
        }
        else {
            fail();
        }
    }
}

void QTEManager::update() {
    if (!isActive) {
        return;
    }

    auto currentTime = chrono::steady_clock::now();
    auto elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();
    if (elapsedTime > timeLimit) {
        fail();
    }
}

void QTEManager::success() {
    cout << "QTE succeeded!" << endl;
    isActive = false;
}

void QTEManager::fail() {
    cout << "QTE failed!" << endl;
    isActive = false;
}