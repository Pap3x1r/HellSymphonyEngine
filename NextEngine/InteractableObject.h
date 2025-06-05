#pragma once
#include "InteractStateMachine.h"
#include "TexturedObject.h"

class InteractableObject : public TexturedObject {
	bool canHit = false;
	bool playerInside = false;
	InteractStateMachine* stateM = new InteractStateMachine();
public:
    InteractableObject();
	InteractableObject(string name);
    ~InteractableObject();

    void selfUpdate(float dt_);

	void onCollisionEnter(Collider* collider) override;
	void onCollisionStay(Collider* collider) override;
	void onCollisionExit(Collider* collider) override;
	void onTriggerEnter(Collider* collider) override;
	void onTriggerStay(Collider* collider) override;
	void onTriggerExit(Collider* collider) override;

	bool getPlayerInside() const {
		return playerInside;
	}

	InteractStateMachine* getStateMachine() const {
		if (!stateM) return nullptr;
		return stateM;
	}

	void setCanHit(bool b) {
		canHit = b;
	}

	bool getCanHit() const {
		return canHit;
	}
};