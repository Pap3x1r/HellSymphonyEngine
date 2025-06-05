#include "PlayerSwordState.h"
#include "Player.h"
#include "Sword.h"
#include "Level.h"

PlayerLightSwordAttack1* PlayerLightSwordAttack1::instance = nullptr;
PlayerLightSwordAttack2* PlayerLightSwordAttack2::instance = nullptr;
PlayerLightSwordAttack3* PlayerLightSwordAttack3::instance = nullptr;
PlayerHeavySwordAttack* PlayerHeavySwordAttack::instance = nullptr;
PlayerSmallSwordUlt* PlayerSmallSwordUlt::instance = nullptr;
PlayerBigSwordUlt* PlayerBigSwordUlt::instance = nullptr;

//Light Sword Attack 1
void PlayerLightSwordAttack1::enter(Player* player) {
    if (player->getFacingRight()) {
        player->getTransform().setScale(glm::vec3(5.4f, 3.75f, 1.0f));
    }
    else {
        player->getTransform().setScale(glm::vec3(-5.4f, 3.75f, 1.0f));
    }
    
    //cout << "Player enters Sword Light Attack 1 state.\n";
    
    player->setTexture("../Resource/Texture/Dante/DanteSword/dante_lightAttack1_sword.png", 1, 6, 0);
    player->getAnimationComponent()->setState("lightAttack1Sword");
    currentPhase = STARTUP;
    time = 0.0f;
    player->getSword()->setCurrentChainAttack(1);
    player->getSword()->setInChainAttack(true); //Player is in chain attack
    if (player->getFacingRight()) {
        player->getPhysicsComponent()->setVelocity(glm::vec2(2.0f, player->getPhysicsComponent()->getVelocity().y));
    }
    else {
        player->getPhysicsComponent()->setVelocity(glm::vec2(-2.0f, player->getPhysicsComponent()->getVelocity().y));
    }

    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.16f, 0.0f, 0.0f));
}

void PlayerLightSwordAttack1::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    /*list<DrawableObject*> attackList = player->getSword()->getChainAttackList();
    auto it = attackList.begin();
    advance(it, 0);*/
    

    DrawableObject* collider = player->getSword()->getChainAttackObject(0);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.167f) { //2 frames
            currentPhase = ACTIVE;
            time = 0;
            attackCollider->resetHit();
            collider->setDrawCollider(true);
            collider->getColliderComponent()->setEnableCollision(true);
            SoundManager::GetInstance()->PlaySFX("Dante-Sword_LightAttack-1");
        }
        break;
    case ACTIVE:
        //do something
        //change phase

        if (time >= 0.167f) {
            currentPhase = RECOVERY;
            time = 0;
            player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
            collider->setDrawCollider(false);
            collider->getColliderComponent()->setEnableCollision(false);
        }
        break;
    case RECOVERY:
        //do something
        //return to idle
        //allows 
        
        if (player->getSword()->getInputBuffer()) { //Ready for next attack
            player->getStateMachine()->changeState(PlayerLightSwordAttack2::getInstance(), player); //enter next phase
            player->getSword()->setInputBuffer(false); //remove input
            return;
        }

        if (time >= 0.167f) { //time's up
            if (player->getFacingRight()) {
                player->getTransform().setScale(glm::vec3(4.0f, 4.0f, 1.0f));
            }
            else {
                player->getTransform().setScale(glm::vec3(-4.0f, 4.0f, 1.0f));
            }
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
            player->getSword()->setCurrentChainAttack(0);
            player->getSword()->setInChainAttack(false); // no longer in chain attack
            
        }
        
        
        break;
    };
}

void PlayerLightSwordAttack1::exit(Player* player) {
    //cout << "Player exits Sword Light Attack 1 state.\n";
    player->getSword()->setCurrentChainAttack(0);
    player->getSword()->setInChainAttack(false); // no longer in chain attack
    if (player->getFacingRight()) {
        player->getTransform().setScale(glm::vec3(3.75f, 3.75f, 1.0f));
    }
    else {
        player->getTransform().setScale(glm::vec3(-3.75f, 3.75f, 1.0f));
    }
    player->getSword()->setInputBuffer(false);
    time = 0;
    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.0f, 0.0f, 0.0f));
    DrawableObject* collider = player->getSword()->getChainAttackObject(0);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);
    collider->getColliderComponent()->setEnableCollision(false);
}

//Light Sword Attack 2
void PlayerLightSwordAttack2::enter(Player* player) {
    if (player->getFacingRight()) {
        player->getTransform().setScale(glm::vec3(5.4f, 3.75f, 1.0f));
    }
    else {
        player->getTransform().setScale(glm::vec3(-5.4f, 3.75f, 1.0f));
    }
    //cout << "Player enters Sword Light Attack 2 state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteSword/dante_lightAttack2_sword.png", 1, 5, 0);
    player->getAnimationComponent()->setState("lightAttack2Sword");
    currentPhase = STARTUP;
    time = 0.0f;
    player->getSword()->setCurrentChainAttack(2);
    player->getSword()->setInChainAttack(true); //Player is in chain attack
    if (player->getFacingRight()) {
        player->getPhysicsComponent()->setVelocity(glm::vec2(2.0f, player->getPhysicsComponent()->getVelocity().y));
    }
    else {
        player->getPhysicsComponent()->setVelocity(glm::vec2(-2.0f, player->getPhysicsComponent()->getVelocity().y));
    }

    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.16f, 0.0f, 0.0f));
}

void PlayerLightSwordAttack2::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    DrawableObject* collider = player->getSword()->getChainAttackObject(1);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.083f) {
            currentPhase = ACTIVE;
            time = 0;
            attackCollider->resetHit();
            collider->setDrawCollider(true);
            collider->getColliderComponent()->setEnableCollision(true);
            SoundManager::GetInstance()->PlaySFX("Dante-Sword_LightAttack-2");
        }
        break;
    case ACTIVE:
        //do something
        //change phase

        if (time >= 0.167f) {
            currentPhase = RECOVERY;
            time = 0;
            player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
            collider->setDrawCollider(false);
            collider->getColliderComponent()->setEnableCollision(false);
        }
        break;
    case RECOVERY:
        if (player->getSword()->getInputBuffer()) { //Ready for next attack
            player->getStateMachine()->changeState(PlayerLightSwordAttack3::getInstance(), player); //enter next phase
            player->getSword()->setInputBuffer(false); //remove input
            return;
        }

        if (time >= 0.167f) { //time's up
            if (player->getFacingRight()) {
                player->getTransform().setScale(glm::vec3(3.75f, 3.75f, 1.0f));
            }
            else {
                player->getTransform().setScale(glm::vec3(-3.75f, 3.75f, 1.0f));
            }
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
            player->getSword()->setCurrentChainAttack(0);
            player->getSword()->setInChainAttack(false); // no longer in chain attack
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerLightSwordAttack2::exit(Player* player) {
    //cout << "Player exits Sword Light Attack 2 state.\n";
    player->getSword()->setCurrentChainAttack(0);
    player->getSword()->setInChainAttack(false); // no longer in chain attack
    if (player->getFacingRight()) {
        player->getTransform().setScale(glm::vec3(3.75f, 3.75f, 1.0f));
    }
    else {
        player->getTransform().setScale(glm::vec3(-3.75f, 3.75f, 1.0f));
    }
    player->getSword()->setInputBuffer(false);
    time = 0;
    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.0f, 0.0f, 0.0f));
    DrawableObject* collider = player->getSword()->getChainAttackObject(0);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);
    collider->getColliderComponent()->setEnableCollision(false);
}

//Light Sword Attack 3
void PlayerLightSwordAttack3::enter(Player* player) {
    if (player->getFacingRight()) {
        player->getTransform().setScale(glm::vec3(5.4f, 3.75f, 1.0f));
    }
    else {
        player->getTransform().setScale(glm::vec3(-5.4f, 3.75f, 1.0f));
    }
    //cout << "Player enters Sword Light Attack 3 state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteSword/dante_lightAttack3_sword.png", 1, 5, 0);
    player->getAnimationComponent()->setState("lightAttack3Sword");
    currentPhase = STARTUP;
    time = 0.0f;
    player->getSword()->setCurrentChainAttack(3);
    player->getSword()->setInChainAttack(true); //Player is in chain attack
    if (player->getFacingRight()) {
        player->getPhysicsComponent()->setVelocity(glm::vec2(2.0f, player->getPhysicsComponent()->getVelocity().y));
    }
    else {
        player->getPhysicsComponent()->setVelocity(glm::vec2(-2.0f, player->getPhysicsComponent()->getVelocity().y));
    }

    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.16f, 0.0f, 0.0f));
}

void PlayerLightSwordAttack3::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";
    DrawableObject* collider = player->getSword()->getChainAttackObject(2);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.083f) {
            currentPhase = ACTIVE;
            time = 0;
            attackCollider->resetHit();
            collider->setDrawCollider(true);
            collider->getColliderComponent()->setEnableCollision(true);
            SoundManager::GetInstance()->PlaySFX("Dante-Sword_LightAttack-3");
        }
        break;
    case ACTIVE:
        //do something
        //change phase

        if (time >= 0.167f) {
            currentPhase = RECOVERY;
            time = 0;
            player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
            collider->setDrawCollider(false);
            collider->getColliderComponent()->setEnableCollision(false);
        }
        break;
    case RECOVERY:

        if (time >= 0.167f) { //time's up
            if (player->getFacingRight()) {
                player->getTransform().setScale(glm::vec3(3.75f, 3.75f, 1.0f));
            }
            else {
                player->getTransform().setScale(glm::vec3(-3.75f, 3.75f, 1.0f));
            }
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
            player->getSword()->setCurrentChainAttack(0);
            player->getSword()->setInChainAttack(false); // no longer in chain attack
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerLightSwordAttack3::exit(Player* player) {
    //cout << "Player exits Sword Light Attack 3 state.\n";
    player->getSword()->setCurrentChainAttack(0);
    player->getSword()->setInChainAttack(false); // no longer in chain attack
    if (player->getFacingRight()) {
        player->getTransform().setScale(glm::vec3(3.75f, 3.75f, 1.0f));
    }
    else {
        player->getTransform().setScale(glm::vec3(-3.75f, 3.75f, 1.0f));
    }
    time = 0;
    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.0f, 0.0f, 0.0f));
    DrawableObject* collider = player->getSword()->getChainAttackObject(0);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);
    collider->getColliderComponent()->setEnableCollision(false);
}

//Heavy Sword Attack
void PlayerHeavySwordAttack::enter(Player* player) {
    //cout << "Player enters Sword Heavy Attack state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteSword/dante_heavyAttack_sword.png", 1, 7, 0);
    player->getAnimationComponent()->setState("heavyAttackSword");
    currentPhase = STARTUP;
    player->getSword()->setInChainAttack(true); //Player is in chain attack
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
}

void PlayerHeavySwordAttack::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    DrawableObject* collider = player->getSword()->getChainAttackObject(3);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.25f) {
            currentPhase = ACTIVE;
            time = 0;
            attackCollider->resetHit();
            collider->setDrawCollider(true);
            collider->getColliderComponent()->setEnableCollision(true);
            SoundManager::GetInstance()->PlaySFX("Dante-Sword_HeavyAttack");
        }
        break;
    case ACTIVE:
        //do something
        //change phase

        if (time >= 0.083f) {
            currentPhase = RECOVERY;
            time = 0;
            collider->setDrawCollider(false);
            collider->getColliderComponent()->setEnableCollision(false);
        }
        break;
    case RECOVERY:
        //do something
        //return to idle
        if (time >= 0.25f) {
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerHeavySwordAttack::exit(Player* player) {
    //cout << "Player exits Sword Heavy Attack state.\n";
    player->getSword()->setInChainAttack(false);
}

////Small Sword Ult
void PlayerSmallSwordUlt::enter(Player* player) {
    //cout << "Player enters Sword Small Ult state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteSword/dante_smallUlt_sword.png", 1, 10, 0);
    player->getAnimationComponent()->setState("smallUltSword");
    currentPhase = STARTUP;
    player->getSword()->setInChainAttack(true); //Player is in chain attack
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.2f, 0.0f, 0.0f));
    player->getSword()->setSmallUltReady(false);
    SoundManager::GetInstance()->PlaySFX("Dante-Sword_UltSmall");
}

void PlayerSmallSwordUlt::update(Player* player, float dt_) {
    time += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    DrawableObject* collider = player->getSword()->getChainAttackObject(4);
    //cout << collider->getName() << endl;
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 0.5f) {
            currentPhase = ACTIVE;
            time = 0;
            attackCollider->resetHit();
            collider->setDrawCollider(true);
            collider->getColliderComponent()->setEnableCollision(true);
         
            if (player->getFacingRight()) {
                player->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x + 4.0f, player->getTransform().getPosition().y, player->getTransform().getPosition().z));
            }
            else {
                player->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x - 4.0f, player->getTransform().getPosition().y, player->getTransform().getPosition().z));
            }
        }
        break;
    case ACTIVE:
        //do something
        //change phase

        if (time >= 0.167f) {
            currentPhase = RECOVERY;
            time = 0;
            collider->setDrawCollider(false);
            collider->getColliderComponent()->setEnableCollision(false);
        }
        break;
    case RECOVERY:
        //do something
        //return to idle
        if (time >= 0.167f) {
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerSmallSwordUlt::exit(Player* player) {
    //cout << "Player exits Sword Small Ult state.\n";
    player->getSword()->setInChainAttack(false); //Player is in chain attack
    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.0f, 0.0f, 0.0f));
    player->getSword()->setSmallUltReady(true);
}

////BigSwordUlt
void PlayerBigSwordUlt::enter(Player* player) {
    //cout << "Player enters Sword Big Ult state.\n";
    player->setTexture("../Resource/Texture/Dante/DanteSword/dante_bigUlt_sword.png", 1, 25, 0);
    player->getAnimationComponent()->setState("bigUltSword");
    currentPhase = STARTUP;
    currentPhase2 = ONE;
    player->getSword()->setInChainAttack(true); //Player is in chain attack
    player->getPhysicsComponent()->setVelocity(glm::vec2(0.0f, player->getPhysicsComponent()->getVelocity().y));
    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.125f, -0.2f, 0.0f));
    player->getSword()->setBigUltReady(false);
    player->setInvincibleFloat(2.5f);
    SoundManager::GetInstance()->PlaySFX("Dante-Sword_UltBig");
}

void PlayerBigSwordUlt::update(Player* player, float dt_) {
    time += dt_;
    time2 += dt_;
    //cout << "Player Idle State: " << time << " (total dt)\n";

    DrawableObject* collider = player->getSword()->getChainAttackObject(5);
    PlayerAttackCollider* attackCollider = dynamic_cast<PlayerAttackCollider*>(collider);


    switch (currentPhase2) {
    case ONE:
        if (time2 >= 0.083f * 4) {
            currentPhase2 = TWO;
            time2 = 0;
            attackCollider->setDraw(true);
            attackCollider->setTexture("../Resource/Texture/Dante/DanteSword/dante_bigUltEffect_sword1.png", 1, 5, 0);
            attackCollider->getAnimationComponent()->setState("BigUlt1");
            attackCollider->getAnimationComponent()->setLoop(false);
        }
        break;
    case TWO:
        //do something
        //change phase

        if (time2 >= 0.083f * 5) {
            currentPhase2 = THREE;
            time2 = 0;
            attackCollider->setTexture("../Resource/Texture/Dante/DanteSword/dante_bigUltEffect_sword2.png", 1, 5, 0);
            attackCollider->getAnimationComponent()->setState("BigUlt2");

        }
        break;
    case THREE:
        
        if (time2 >= 0.083f * 5) {
            time2 = 0;
            currentPhase2 = FOUR;
            attackCollider->setTexture("../Resource/Texture/Dante/DanteSword/dante_bigUltEffect_sword3.png", 1, 5, 0);
            attackCollider->getAnimationComponent()->setState("BigUlt3");
        }
        break;
    case FOUR:

        if (time2 >= 0.083f * 5) {
            time2 = 0;
            currentPhase2 = FIVE;
            attackCollider->setTexture("../Resource/Texture/Dante/DanteSword/dante_bigUltEffect_sword4.png", 1, 3, 0);
            attackCollider->getAnimationComponent()->setState("BigUlt4");
        }
        break;
    case FIVE:

        if (time2 >= 0.083f * 3) {
            time2 = 0;
            attackCollider->setDraw(false);
        }
        break;
    };

    switch (currentPhase) {
    case STARTUP:
        //do something
        //change phase
        if (time >= 2.0f) {
            currentPhase = ACTIVE;
            time = 0;
            attackCollider->resetHit();
            collider->setDrawCollider(true);
            collider->getColliderComponent()->setEnableCollision(true);
        }
        break;
    case ACTIVE:
        //do something
        //change phase

        if (time >= 0.083f) {
            currentPhase = RECOVERY;
            time = 0;
            collider->setDrawCollider(false);
            collider->getColliderComponent()->setEnableCollision(false);
            attackCollider->setDraw(false);
        }
        break;
    case RECOVERY:
        //do something
        //return to idle
        if (time >= 0.0f) {
            player->getStateMachine()->changeState(PlayerIdleState::getInstance(), player);
        }
        break;
    };

    /*if (time > 0.12f) {
        player->getAnimationComponent()->updateCurrentState();
        time = 0;
    }*/
}

void PlayerBigSwordUlt::exit(Player* player) {
    //cout << "Player exits Sword Big Ult state.\n";
    player->getSword()->setInChainAttack(false); //Player is in chain attack
    player->getAnimationComponent()->setAnimOffset(glm::vec3(0.0f, 0.0f, 0.0f));
    player->getSword()->setBigUltReady(true);
}