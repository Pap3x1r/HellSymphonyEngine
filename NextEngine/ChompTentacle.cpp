#include "ChompTentacle.h"


ChompTentacle::ChompTentacle() {
    
}

ChompTentacle::ChompTentacle(bool facingRight,Ziz* boss) {
    ziz = dynamic_cast<Ziz*>(boss);
    if (ziz) {
        cout << "Found Ziz in tentacle" << endl;
    }
    isFacingRight = facingRight;


    setName("ChompTentacle");
    if (isFacingRight == true) {
        getTransform().setScale(glm::vec3(-7.5f, 7.5f, 1.0f));
    }
    else {
        getTransform().setScale(glm::vec3(7.5f, 7.5f, 1.0f));
    }
    
    
    addColliderComponent();
    getColliderComponent()->setTrigger(true);
    setDrawCollider(true);
    //setCanDrawColliderNew(true);

    initAnimation(32, 1);

    getAnimationComponent()->addState("chomptentacle", 0, 32);
    setTexture("../Resource/Texture/FinalZiz/Zyzz_Chomp/Zyzz_Chomp_Mouth-Sheet.png", 1, 32, 0);
    getAnimationComponent()->setState("chomptentacle");



    chompTimer = 0.08 * 32;
    hasAttack1 = false;
    hasAttack2 = false;
    damage = 100;
    cout << "chompTentacle Spawned" << endl;

    attackOffSet1 = 1.0f;
    attackOffSet2 = 3.0f;
    attackTimer1 = 0.08 * 10;
    attackTimer2 = 0.08 * 7;
    attackduration1 = 0.08 * 4;
    attackduration2 = 0.08 * 4;

    attackCollider1 = new EnemyAttackCollider(5);
    attackCollider1->addColliderComponent();
    attackCollider1->setDraw(false);
    attackCollider1->setDrawCollider(true);
    //attackCollider1->setCanDrawColliderNew(true);
    attackCollider1->setActive(false);
    attackCollider1->getColliderComponent()->setTrigger(true);
    attackCollider1->getColliderComponent()->setDimension(1.5f, 3.0f);
    if (isFacingRight == true) {//right
        attackCollider1->getTransform().setPosition(glm::vec3(getTransform().getPosition().x  + 4.75f, getTransform().getPosition().y - 1.5f, 0.0f));
    }
    else {
        attackCollider1->getTransform().setPosition(glm::vec3(getTransform().getPosition().x - 0.75f, getTransform().getPosition().y - 1.5f, 0.0f));
    }

    attackCollider2 = new EnemyAttackCollider(5);
    attackCollider2->addColliderComponent();
    attackCollider2->setDraw(false);
    attackCollider2->setDrawCollider(true);
    //attackCollider2->setCanDrawColliderNew(true);
    attackCollider2->setActive(false);
    attackCollider2->getColliderComponent()->setTrigger(true);
    attackCollider2->getColliderComponent()->setDimension(1.5f, 3.0f);
    if (isFacingRight == true) {//right
        attackCollider2->getTransform().setPosition(glm::vec3(getTransform().getPosition().x + 6.75f, getTransform().getPosition().y - 1.5f, 0.0f));
    }
    else {
        attackCollider2->getTransform().setPosition(glm::vec3(getTransform().getPosition().x - 2.75f, getTransform().getPosition().y - 1.5f, 0.0f));
    }
    
    
    
}

ChompTentacle::~ChompTentacle() {
    //DrawableObject::destroyObject(attackCollider1);
}

void ChompTentacle::update(float dt) {
    if (chompTimer >= 0) {
        chompTimer -= dt;
    }
    else {
        
        DrawableObject::destroyObject(this);
        
    }


    if (hasAttack1 == false && attackTimer1 > 0) {
        attackTimer1 -= dt;
        //cout << attackTimer1 << endl;
        if (attackTimer1 <= 0) {
            hasAttack1 = true;
            ziz->getLevel()->addObject(attackCollider1);
            attackCollider1->setActive(true);
        }
    }

    if (hasAttack1 == true && hasAttack2 == false) {
        
        //cout << "Finished first attack" << endl;
        attackTimer2 -= dt;
        if (attackTimer2 <= 0) {
            hasAttack2 = true;
            ziz->getLevel()->addObject(attackCollider2);
            attackCollider2->setActive(true);
        }
        
    }

    

    if (attackCollider1->getIsActive() == true) {
        attackduration1 -= dt;
        if (attackduration1 <= 0) {
            DrawableObject::destroyObject(attackCollider1);
        }
    }
    if (attackCollider2->getIsActive() == true) {
        attackduration2 -= dt;
        if (attackduration2 <= 0) {
            DrawableObject::destroyObject(attackCollider2);
        }
    }
}
