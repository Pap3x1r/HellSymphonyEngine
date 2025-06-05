#include "InteractableObject.h"
#include "Player.h"

InteractableObject::InteractableObject() {

}

InteractableObject::InteractableObject(string name) {
	DrawableObject::setName(name);
}

InteractableObject::~InteractableObject() {

}

void InteractableObject::selfUpdate(float dt_) {
	if (playerInside) {
		//cout << "Is Inside" << endl;
	}

	/*if (collider) {
		setDrawCollider(true);
		setCanDrawColliderNew(true);
	}*/
}

void InteractableObject::onCollisionEnter(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	if (player) {
		playerInside = true;
		//cout << "Player is in" << endl;
	}
}

void InteractableObject::onCollisionStay(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	if (player) {
		playerInside = true;
		//cout << "Player is in" << endl;
	}
}

void InteractableObject::onCollisionExit(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);
	if (player) {
		playerInside = false;
		//cout << "Player is out" << endl;
	}
}

void InteractableObject::onTriggerEnter(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);

	if (player) {
		playerInside = true;
		//cout << "Player is in" << endl;
	}
}

void InteractableObject::onTriggerStay(Collider* collider) {
	DrawableObject* obj = collider->getObject();

	Player* player = dynamic_cast<Player*>(obj);
	if (player) {
		//cout << "Player is in" << endl;
		playerInside = true;
	}
}

void InteractableObject::onTriggerExit(Collider* collider) {
	DrawableObject* obj = collider->getObject();
	Player* player = dynamic_cast<Player*>(obj);
	if (player) {
		playerInside = false;
		//cout << "Player is out" << endl;
	}
}