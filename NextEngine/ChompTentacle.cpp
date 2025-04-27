#include "ChompTentacle.h"


ChompTentacle::ChompTentacle() {
    setName("ChompTentacle");
    //setTexture("../Resource/Texture/Ziz_Aircutter.png");
    getTransform().setScale(glm::vec3(10.0f, 10.0f, 1.0f));
    getTransform().setPosition(glm::vec3(0.0f,0.0f,0.0f));
    addColliderComponent();
    getColliderComponent()->setTrigger(true);
    setDrawCollider(true);
    setCanDrawColliderNew(true);
    
    

    

    initAnimation(32, 1);
    
    getAnimationComponent()->addState("chomptentacle", 0, 32);
    setTexture("../Resource/Texture/FinalZiz/Zyzz_Chomp/Zyzz_Chomp_Mouth-Sheet.png", 1, 32, 0);
    getAnimationComponent()->setState("chomptentacle");

    
    chompTimer = 0.08 * 32;
    isFacingRight = false;
    hasHit = false;
    damage = 100;
    cout << "chompTentacle Spawned" << endl;
}

ChompTentacle::ChompTentacle(bool facingRight) {
    isFacingRight = facingRight;

    setName("ChompTentacle");
    if (isFacingRight == true) {
        getTransform().setScale(glm::vec3(-10.0f, 10.0f, 1.0f));
    }
    else {
        getTransform().setScale(glm::vec3(10.0f, 10.0f, 1.0f));
    }
    
    getTransform().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    addColliderComponent();
    getColliderComponent()->setTrigger(true);
    setDrawCollider(true);
    setCanDrawColliderNew(true);

    initAnimation(32, 1);

    getAnimationComponent()->addState("chomptentacle", 0, 32);
    setTexture("../Resource/Texture/FinalZiz/Zyzz_Chomp/Zyzz_Chomp_Mouth-Sheet.png", 1, 32, 0);
    getAnimationComponent()->setState("chomptentacle");



    chompTimer = 0.08 * 32;
    hasHit = false;
    damage = 100;
    cout << "chompTentacle Spawned" << endl;
}

void ChompTentacle::update(float dt) {
    if (chompTimer >= 0) {
        chompTimer -= dt;
    }
    else {
        DrawableObject::destroyObject(this);
    }
}
