#include "PlayerMovementState.h"
#include "Player.h"

PlayerIdleState* PlayerIdleState::instance = nullptr;
PlayerWalkState* PlayerWalkState::instance = nullptr;
PlayerJumpUpState* PlayerJumpUpState::instance = nullptr;
PlayerFallDownState* PlayerFallDownState::instance = nullptr;

//Idle
void PlayerIdleState::enter(Player* player) {
    //cout << "Player enters Idle state.\n";

    switch (player->getWeaponType()) {
    case None_:
        break;
    case Sword_:
        player->setTexture("../Resource/Texture/dante_idle.png", 1, 8, 0);
        player->getAnimationComponent()->setState("idle");
        break;
    case Shield_:
        break;
    case Bow_:
        break;
    default:
        cerr << "Weapon Type does not match any types" << endl;
    }
}

void PlayerIdleState::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerIdleState::exit(Player* player) {
    //cout << "Player exits Idle state.\n";
}

//Walk
void PlayerWalkState::enter(Player* player) {
    //cout << "Player enters Walk state.\n";

    switch (player->getWeaponType()) {
    case None_:
        break;
    case Sword_:
        player->setTexture("../Resource/Texture/dante_walking_sword.png", 1, 8, 0); //set new texture ("path", row, column)
        player->getAnimationComponent()->setState("walkingSword"); //set state
        break;
    case Shield_:
        break;
    case Bow_:
        break;
    default:
        cerr << "Weapon Type does not match any types" << endl;
    }
}

void PlayerWalkState::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerWalkState::exit(Player* player) {
    //cout << "Player exits Walk state.\n";
}

//Jump Up
void PlayerJumpUpState::enter(Player* player) {
    //cout << "Player enters Jump Up state.\n";

    switch (player->getWeaponType()) {
    case None_:
        break;
    case Sword_:
        player->setTexture("../Resource/Texture/dante_jumping_sword.png", 1, 2, 0); //set new texture ("path", row, column, starting anim)
        player->getAnimationComponent()->setState("jumpingSword"); //set state
        break;
    case Shield_:
        break;
    case Bow_:
        break;
    default:
        cerr << "Weapon Type does not match any types" << endl;
    }
}

void PlayerJumpUpState::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerJumpUpState::exit(Player* player) {
    //cout << "Player exits Jump Up state.\n";
}

//Fall Down
void PlayerFallDownState::enter(Player* player) {
    //cout << "Player enters Fall Down state.\n";

    switch (player->getWeaponType()) {
    case None_:
        break;
    case Sword_:
        player->setTexture("../Resource/Texture/dante_jumping_sword.png", 1, 2, 1); //set new texture ("path", row, column)
        player->getAnimationComponent()->setState("fallingSword"); //set state
        break;
    case Shield_:
        break;
    case Bow_:
        break;
    default:
        cerr << "Weapon Type does not match any types" << endl;
    }
}

void PlayerFallDownState::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerFallDownState::exit(Player* player) {
    //cout << "Player exits Fall Down state.\n";
}