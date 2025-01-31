#include "Collider.h"
#include "DrawableObject.h"
//#include "CollisionHandler.h"

Collider::Collider(DrawableObject* object) : object(object), width(1), height(1) {
	enableCollision = true;
	trigger = false;
	transform = Transform();

	collisionFlag = 0;
}

Collider::Collider(DrawableObject* object, float width, float height) : object(object), width(width), height(height) {
	enableCollision = true;
	trigger = false;
	transform = Transform();

	collisionFlag = 0;
}

void Collider::setEnableCollision(bool value) {
	if (!value) {
		// Reset specific states or flags related to collision
		collisionFlag = 0;  // Reset the collision flag

		// Reset the collision map
		collisionMap.clear();

		//// Optionally, trigger exit events for the other objects involved in collisions
		//for (auto& entry : collisionMap) {
		//	Collider* otherCollider = entry.first;
		//	if (otherCollider != nullptr) {
		//		// Example: You might want to call a method on the other object as well
		//		otherCollider->getObject()->OnTriggerExit(this->object);
		//	}
		//}
	}

	enableCollision = value;
}

void Collider::setTrigger(bool value) {
	trigger = value;
}

void Collider::setTransform(const Transform& transform) {
	this->transform = transform;
}

void Collider::setWidth(float width) {
	this->width = width;
}

void Collider::setHeight(float height) {
	this->height = height;
}

void Collider::setDimension(float width, float height) {
	this->width = width;
	this->height = height;
}

void Collider::setCollisionFlag(COLLISION_FLAG flag) {
	this->collisionFlag = flag;
}

void Collider::setOffset(glm::vec3 offset) {
	this->transformOffset = offset;
}

Transform& Collider::getTransform() {
	return transform;
}

Transform Collider::getGlobalTransform(Transform& selfTransform) {
	return selfTransform.getGlobalTransform(this->transform);
}

//Transform Collider::getGlobalTransform(Transform& selfTransform) {
//	// Assuming getGlobalTransform for the Transform class combines local and parent transforms
//	Transform globalTransform = selfTransform.getGlobalTransform(this->transform);
//	// Apply the offset to the global transform
//	globalTransform.setPosition(globalTransform.getPosition() + transformOffset);
//	return globalTransform;
//}

float Collider::getWidth() const {
	//return width * const_cast<Transform*>(&transform)->getScale().x;
	return width * std::abs(transform.getScale().x);
}

float Collider::getHeight() const {
	//return height * const_cast<Transform*>(&transform)->getScale().y;
	return height * std::abs(transform.getScale().y);
}

std::map<Collider*, Collider::CollisionState>& Collider::getCollisionMap() {
	return collisionMap;
}

Collider::CollisionState Collider::getCollisionState(Collider* other) {
	if (collisionMap.find(other) == collisionMap.end()) {
		return Collider::NONE;
	}

	return collisionMap[other];
}

bool Collider::isEnable() const {
	return enableCollision;
}

bool Collider::isTrigger() const {
	return trigger;
}

COLLISION_FLAG Collider::getCollisionFlag() const {
	return collisionFlag;
}

glm::vec3 Collider::getOffset() const {
	return transformOffset;
}

glm::vec3 Collider::getAdjustedOffset(const Transform& transform) const {
	glm::vec3 adjustedOffset = transformOffset;
	glm::vec3 scale = transform.getScale(); // Ensure const correctness
	if (scale.x < 0) adjustedOffset.x = -transformOffset.x; // Flip for negative X scale
	if (scale.y < 0) adjustedOffset.y = -transformOffset.y; // Flip for negative Y scale
	return adjustedOffset;
}

DrawableObject* Collider::getObject() {
	return object;
}