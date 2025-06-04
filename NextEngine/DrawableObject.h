#pragma once
#include "glm.hpp"
#include "Collider.h"
#include "Physics.h"
#include "Transform.h"
#include <string>
#include <list>
#include <vector>

using namespace std;

class Collider; // forward declaration

enum MenuState {
	NONE,
	MAIN,
	PAUSE,
	OPTIONS,
	AUDIO,
	CONTROLLER,
	KEYBOARD,
	CREDITS,
	QUITCONFIRM,
	SAVECONFIRM,
	DEATH,
	VICTORY,
	IGNORE
};

enum class Tag {
	Player,
	PlayerAttack,
	Enemy,
	EnemyAttack,
	Floor,
	GroundChecker,
	UI,
	Default
};

class DrawableObject {
private:
	bool canDrawColliderNew;
	bool canDrawCollider;
	bool canDraw;
	void processCollider();

	bool isActive;
	bool isMarkedForDelete;

	MenuState menuState = MenuState::NONE;
	vector<MenuState> menuStateVec;
	float alpha = 1.0f; // Default alpha (visible)
	float maximumAlpha = 1.0f;

protected:
	string name = "Object";
	Tag tag;
	Transform transform;
	Physics* physics;
	Collider* collider;

	virtual void onCollisionEnter(Collider* collider);
	virtual void onCollisionStay(Collider* collider);
	virtual void onCollisionExit(Collider* collider);

	virtual void onTriggerEnter(Collider* collider);
	virtual void onTriggerStay(Collider* collider);
	virtual void onTriggerExit(Collider* collider);

public:
	int drawLayer = 0;

	string getName();
	void setName(string name);

	Tag getTag() const {
		return tag;
	}

	void setTag(Tag newTag) {
		tag = newTag;
	}

	Transform& getTransform();
	glm::mat4 getTransformMat4();

	Physics* getPhysicsComponent();
	Collider* getColliderComponent();

	void addPhysicsComponent();
	void addPhysicsComponent(Physics& physics);
	void addColliderComponent();
	void addColliderComponent(Collider& collider);

	virtual void updateBehavior();
	virtual void update();
	void update(float dt);

	DrawableObject();
	DrawableObject(string name);
	virtual ~DrawableObject();
	virtual void render(glm::mat4 globalModelTransform) = 0;
	void setDrawCollider(bool value);
	void setDraw(bool value);
	void drawCollider();

	void setActive(bool value);

	bool getIsActive();
	bool getMarkedForDelete();

	bool getCanDraw();

	void setCanDrawColliderNew(bool value) {
		canDrawColliderNew = value;
	}

	bool getCanDrawCollider() {
		return canDrawCollider;
	}

	bool* getCanDrawColliderAddress() {
		return &canDrawColliderNew;
	}

	void setMenuState(MenuState newMenuState) {
		menuState = newMenuState;
		menuStateVec.push_back(newMenuState);
	}

	MenuState getMenuState() const {
		return menuState;
	}

	void addMenuStateToVec(MenuState newMenuState) {
		menuStateVec.push_back(newMenuState);
	}

	vector<MenuState> getMenuStateVec() const {
		return menuStateVec;
	}

	virtual void setAlpha(float value);

	virtual float getAlpha() const;

	static void destroyObject(DrawableObject* obj);

	void setMaximumAlpha(float alpha) {
		maximumAlpha = alpha;
	}

	float getMaximumAlpha() const {
		return maximumAlpha;
	}
};