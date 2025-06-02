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

    if (key == ' ') {
        return;
    }

    inputs.push_back(key);

    if (key != sequence[currentIndex]) {
        fail();
        return;
    }

    currentIndex++;

    if (currentIndex == sequence.size()) {
        success();
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

    cout << "Sequence: ";
    for (char key : sequence) {
        cout << key << " ";
    }
    cout << endl;

    cout << "Input: ";
    for (char key : inputs) {
        cout << key << " ";
    }
    cout << endl;

    isActive = false;
}

void QTEManager::fail() {
    cout << "QTE failed!" << endl;


    cout << "Sequence: ";
    for (char key : sequence) {
        cout << key << " ";
    }
    cout << endl;

    cout << "Input: ";
    for (char key : inputs) {
        cout << key << " ";
    }
    cout << endl;

    isActive = false;
}