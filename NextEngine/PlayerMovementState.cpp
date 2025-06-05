#include "PlayerMovementState.h"
#include "Player.h"

PlayerIdleState* PlayerIdleState::instance = nullptr;
PlayerWalkState* PlayerWalkState::instance = nullptr;
PlayerJumpUpState* PlayerJumpUpState::instance = nullptr;
PlayerFallDownState* PlayerFallDownState::instance = nullptr;
PlayerDashState* PlayerDashState::instance = nullptr;


//Idle
void PlayerIdleState::enter(Player* player) {
    //cout << "Player enters Idle state.\n";

    switch (player->getWeaponType()) {
    case None_:
        player->setTexture("../Resource/Texture/Dante/DanteNone/dante_unarmed_idle.png", 1, 8, 0);
        player->getAnimationComponent()->setState("idleNone");
        break;
    case Sword_:
        player->setTexture("../Resource/Texture/Dante/DanteSword/dante_idle_sword.png", 1, 8, 0);
        player->getAnimationComponent()->setState("idleSword");
        break;
    case Shield_:
        player->setTexture("../Resource/Texture/Dante/DanteShield/dante_idle_shield.png", 1, 8, 0);
        player->getAnimationComponent()->setState("idleShield");
        break;
    case Bow_:
        player->setTexture("../Resource/Texture/Dante/DanteBow/dante_idle_bow.png", 1, 8, 0);
        player->getAnimationComponent()->setState("idleBow");
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
        player->setTexture("../Resource/Texture/Dante/DanteNone/dante_unarmed_walk.png", 1, 8, 0);
        player->getAnimationComponent()->setState("walkingNone");
        break;
    case Sword_:
        player->setTexture("../Resource/Texture/Dante/DanteSword/dante_walking_sword.png", 1, 8, 0); //set new texture ("path", row, column)
        player->getAnimationComponent()->setState("walkingSword"); //set state
        break;
    case Shield_:
        player->setTexture("../Resource/Texture/Dante/DanteShield/dante_walking_shield.png", 1, 8, 0);
        player->getAnimationComponent()->setState("walkingShield");
        break;
    case Bow_:
        player->setTexture("../Resource/Texture/Dante/DanteBow/dante_walking_bow.png", 1, 8, 0);
        player->getAnimationComponent()->setState("walkingBow");
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
        player->setTexture("../Resource/Texture/Dante/DanteNone/dante_unarmed_jump.png", 1, 2, 0);
        player->getAnimationComponent()->setState("jumpingNone");
        break;
    case Sword_:
        player->setTexture("../Resource/Texture/Dante/DanteSword/dante_jumping_sword.png", 1, 2, 0); //set new texture ("path", row, column, starting anim)
        player->getAnimationComponent()->setState("jumpingSword"); //set state
        break;
    case Shield_:
        player->setTexture("../Resource/Texture/Dante/DanteShield/dante_jumping_shield.png", 1, 1, 0);
        player->getAnimationComponent()->setState("jumpingShield");
        break;
    case Bow_:
        player->setTexture("../Resource/Texture/Dante/DanteBow/dante_jumping_bow.png", 1, 2, 0);
        player->getAnimationComponent()->setState("jumpingBow");
        break;
    default:
        cerr << "Weapon Type does not match any types" << endl;
    }

    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.0f, -0.165f, 0.0f));
    SoundManager::GetInstance()->PlaySFX("Dante-Jump");
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
    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.0f, 0.0f, 0.0f));
}

//Fall Down
void PlayerFallDownState::enter(Player* player) {
    //cout << "Player enters Fall Down state.\n";

    switch (player->getWeaponType()) {
    case None_:
        player->setTexture("../Resource/Texture/Dante/DanteNone/dante_unarmed_jump.png", 1, 2, 1);
        player->getAnimationComponent()->setState("fallingNone");
        break;
    case Sword_:
        player->setTexture("../Resource/Texture/Dante/DanteSword/dante_jumping_sword.png", 1, 2, 1); //set new texture ("path", row, column)
        player->getAnimationComponent()->setState("fallingSword"); //set state
        break;
    case Shield_:
        player->setTexture("../Resource/Texture/Dante/DanteShield/dante_falling_shield.png", 1, 1, 0);
        player->getAnimationComponent()->setState("fallingShield");
        break;
    case Bow_:
        player->setTexture("../Resource/Texture/Dante/DanteBow/dante_falling_bow.png", 1, 1, 0);
        player->getAnimationComponent()->setState("fallingBow");
        break;
    default:
        cerr << "Weapon Type does not match any types" << endl;
    }

    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.0f, -0.165f, 0.0f));
}

void PlayerFallDownState::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    
    if (player->getTransform().getPosition().y < -1.1375) {
        //player->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x, -1.13f, 0.0f));
    }
    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerFallDownState::exit(Player* player) {
    //cout << "Player exits Fall Down state.\n";
    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.0f, 0.0f, 0.0f));
}

//Fall Down
void PlayerDashState::enter(Player* player) {
    //cout << "Player enters Fall Down state.\n";

    switch (player->getWeaponType()) {
    case None_:
        player->setTexture("../Resource/Texture/Dante/DanteNone/dante_unarmed_dash.png", 1, 1, 0);
        player->getAnimationComponent()->setState("dashNone");
        break;
    case Sword_:
        player->setTexture("../Resource/Texture/Dante/DanteSword/dante_dash_sword.png", 1, 1, 0); //set new texture ("path", row, column)
        player->getAnimationComponent()->setState("dashSword"); //set state
        break;
    case Shield_:
        player->setTexture("../Resource/Texture/Dante/DanteShield/dante_dash_shield.png", 1, 1, 0);
        player->getAnimationComponent()->setState("dashShield");
        break;
    case Bow_:
        player->setTexture("../Resource/Texture/Dante/DanteBow/dante_dash_bow.png", 1, 1, 0);
        player->getAnimationComponent()->setState("dashBow");
        break;
    default:
        cerr << "Weapon Type does not match any types" << endl;
    }

    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.0f, -0.1f, 0.0f));
    SoundManager::GetInstance()->PlaySFX("Dante-Dash");
}

void PlayerDashState::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";


    if (player->getTransform().getPosition().y < -1.1375) {
        //player->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x, -1.13f, 0.0f));
    }
    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerDashState::exit(Player* player) {
    //cout << "Player exits Fall Down state.\n";
    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.0f, 0.0f, 0.0f));
}