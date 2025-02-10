#include "PlayerMovementState.h"
#include "Player.h"

PlayerIdleState* PlayerIdleState::instance = nullptr;
PlayerWalkState* PlayerWalkState::instance = nullptr;

//Idle
void PlayerIdleState::enter(Player* player) {
    cout << "Player enters Idle state.\n";
    player->getAnimationComponent()->setState("idle");
}

void PlayerIdleState::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }
}

void PlayerIdleState::exit(Player* player) {
    cout << "Player exits Idle state.\n";
}

//Walk
void PlayerWalkState::enter(Player* player) {
    cout << "Player enters Walk state.\n";
    player->getAnimationComponent()->setState("walk");
}

void PlayerWalkState::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }
}

void PlayerWalkState::exit(Player* player) {
    cout << "Player exits Walk state.\n";
}