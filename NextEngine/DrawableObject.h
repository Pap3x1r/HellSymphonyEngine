#pragma once
#include "glm.hpp"
#include "Collider.h"
#include "Physics.h"
#include "Transform.h"
#include <string>
#include <list>

using namespace std;

class Collider; // forward declaration

enum class Tag {
	Player,
	PlayerAttack,
	Enemy,
	EnemyAttack,
	Floor,
	GroundChecker,
	Default
};

class DrawableObject {
private:
	bool canDrawCollider;
	bool canDraw;
	void processCollider();

	bool isActive;
	bool isMarkedForDelete;


protected:
	string name;
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

	static void destroyObject(DrawableObject* obj);
};