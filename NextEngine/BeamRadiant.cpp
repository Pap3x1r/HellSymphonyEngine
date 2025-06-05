#include "BeamRadiant.h"

BeamRadiant::BeamRadiant(){

    setName("BeamRadiant");

    initAnimation(33, 1);
    getAnimationComponent()->addState("beamradiant", 0, 33);


    getTransform().setScale(glm::vec3(2.5f, 5.0f, 1.0f));
    getTransform().setPosition(glm::vec3(0, -1.0f, 0));

    setTexture("../Resource/Texture/Lucifer/VFX/Laser staff.png", 1, 33, 0);
    getAnimationComponent()->setState("beamradiant");

    lucifer = Lucifer::getInstance();

    timer = 0.08f * 33;
    spawnLaser = 0.08f * 6;
    spawnedLaser = false;

}

void BeamRadiant::update(float dt) {

    if (spawnedLaser == false) {
        spawnLaser -= dt;
        if (spawnLaser <= 0) {
            RadiantLaser* rs = new RadiantLaser();
            lucifer->getLevel()->addObject(rs);
            spawnedLaser = true;
            SoundManager::GetInstance()->PlaySFX("Lucifer-BeamRadiant_Beam");
            SoundManager::GetInstance()->PlaySFX("Lucifer_CloseoutBeams");
        }
    }

    timer -= dt;
    if (timer <= 0) {
        DrawableObject::destroyObject(this);
    }
}