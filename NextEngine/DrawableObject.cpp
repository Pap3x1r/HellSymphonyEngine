#include "DrawableObject.h"
#include "GameEngine.h"
#include "SquareBorderMesh.h"
#include "SquareMeshVbo.h"

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <iostream>

using namespace std;

Transform& DrawableObject::getTransform() {
	/*glm::mat4 transform = glm::mat4(1.0);
	transform = glm::translate(transform, glm::vec3(pos.x, pos.y, 0));
	transform = glm::scale(transform, glm::vec3(size.x, size.y, 1));
	return transform;*/

	return transform;
}

glm::mat4 DrawableObject::getTransformMat4() {
	return transform.getTransformMat4();
}

DrawableObject::DrawableObject() {
	/*pos = glm::vec3(0.0, 0.0, 0.0);
	size = glm::vec3(1.0, 1.0, 1.0);*/

	this->name = "Object";
	this->transform = Transform();
	tag = Tag::Default;
	physics = nullptr;
	collider = nullptr;

	isActive = true;

	canDrawCollider = false;
	canDraw = true;

}

DrawableObject::DrawableObject(string name) {
	/*pos = glm::vec3(0.0, 0.0, 0.0);
	size = glm::vec3(1.0, 1.0, 1.0);*/

	this->name = name;
	this->transform = Transform();
	physics = nullptr;
	collider = nullptr;

	isActive = true;

	canDrawCollider = false;
	canDraw = true;
}

DrawableObject::~DrawableObject() {
	//std::cout << "Destroying DrawableObject: " << name << std::endl;

	if (physics != nullptr) {
		delete physics;
		physics = nullptr;
	}

	if (collider) {
		for (auto& [other, state] : collider->getCollisionMap()) {
			if (other && !other->isDestroyed) {
				other->getCollisionMap().erase(collider);
			}
		}
		collider->getCollisionMap().clear();

		delete collider;
		collider = nullptr;
	}
}

string DrawableObject::getName() {
	return this->name;
}

void DrawableObject::setName(string name) {
	this->name = name;
}

Physics* DrawableObject::getPhysicsComponent() {
	if (this->physics == nullptr) {
		//cout << "Physics component does not exist" << endl;
		return nullptr;
	}

	return this->physics;
}
Collider* DrawableObject::getColliderComponent() {
	if (this->collider == nullptr) {
		//cout << "Collider component does not exist" << endl;
		return nullptr;
	}

	return this->collider;
}

void DrawableObject::addPhysicsComponent() {
	if (this->physics != nullptr) {
		cout << "Physics component already exists" << endl;
		return;
	}

	this->physics = new Physics(this->transform);
}

void DrawableObject::addPhysicsComponent(Physics& physics) {
	if (this->physics != nullptr) {
		cout << "Physics component already exists" << endl;
		return;
	}

	this->physics = new Physics(this->transform);
	*(this->physics) = physics;
}

void DrawableObject::addColliderComponent() {
	if (this->collider != nullptr) {
		cout << "Collider component already exists" << endl;
		return;
	}

	this->collider = new Collider(this);
}

void DrawableObject::addColliderComponent(Collider& collider) {
	if (this->collider != nullptr) {
		cout << "Collider component already exists" << endl;
		return;
	}

	this->collider = new Collider(this);
	this->collider->setTransform(collider.getTransform());
	this->collider->setWidth(collider.getWidth());
	this->collider->setHeight(collider.getHeight());
}

/// For implementation in derived class ///
void DrawableObject::onCollisionEnter(Collider* collider) {}
void DrawableObject::onCollisionStay(Collider* collider) {}
void DrawableObject::onCollisionExit(Collider* collider) {}
void DrawableObject::onTriggerEnter(Collider* collider) {}
void DrawableObject::onTriggerStay(Collider* collider) {}
void DrawableObject::onTriggerExit(Collider* collider) {}

void DrawableObject::processCollider() {
	if (collider == nullptr) {
		return;
	}

	map<Collider*, Collider::CollisionState>& colliderMap = collider->getCollisionMap();

	for (pair<Collider*, Collider::CollisionState> pair : colliderMap) {
		Collider* col = pair.first;

		if (!col) continue;

		Collider::CollisionState state = pair.second;
		switch (state) {
		case Collider::ENTER:
			/*cout << "Col is a trigger: " << col->isTrigger() << endl;
			cout << "Enter detected" << endl;*/
			col->isTrigger() ? onTriggerEnter(col) : onCollisionEnter(col);
			break;
		case Collider::STAY:
			col->isTrigger() ? onTriggerStay(col) : onCollisionStay(col);
			break;
		case Collider::EXIT:
			col->isTrigger() ? onTriggerExit(col) : onCollisionExit(col);
			break;
		}
	}
}

void DrawableObject::updateBehavior() {}

void DrawableObject::update() {
	processCollider();

	if (physics != nullptr) {
		physics->update(this->transform);
	}

	updateBehavior();
}

void DrawableObject::update(float dt) {
	processCollider();

	if (physics != nullptr) {
		physics->update(this->transform, dt);
	}

	updateBehavior();
}

void DrawableObject::setDrawCollider(bool value) {
	canDrawCollider = value;
}

void DrawableObject::setDraw(bool value) {
	canDraw = value;
}

void DrawableObject::drawCollider() {
	if (collider == nullptr) {
		return;
	}

	if (!canDrawCollider) {
		return;
	}

	if (!canDrawColliderNew) {
		return;
	}

	SquareBorderMesh* squareBorderMesh = dynamic_cast<SquareBorderMesh*> (GameEngine::getInstance()->getRenderer()->getMesh(SquareBorderMesh::MESH_NAME));

	GLuint modelMatixId = GameEngine::getInstance()->getRenderer()->getModelMatrixAttrId();
	GLuint renderModeId = GameEngine::getInstance()->getRenderer()->getModeUniformId();
	GLuint colorId = GameEngine::getInstance()->getRenderer()->getColorUniformId();

	if (modelMatixId == -1) {
		cout << "Error: Can't perform transformation " << endl;
		return;
	}
	if (renderModeId == -1) {
		cout << "Error: Can't set renderMode in TexturedObject " << endl;
		return;
	}
	if (colorId == -1) {
		cout << "Error: Can't set color " << endl;
		return;
	}

	vector <glm::mat4> matrixStack;

	//glm::mat4 currentMatrix = this->getTransformMat4();
	Transform colTransform = collider->getGlobalTransform(this->transform);
	//colTransform.setPosition(colTransform.getPosition() + collider->getOffset());
	colTransform.scales(collider->getWidth(), collider->getHeight());
	glm::mat4 currentMatrix = colTransform.getTransformMat4();
	//glm::mat4 currentMatrix = collider->getGlobalTransform(this->transform).getTransformMat4();

	if (squareBorderMesh != nullptr) {

		//currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform3f(colorId, 0, 1, 0);
		glUniform1i(renderModeId, 0);
		squareBorderMesh->render();
	}
}

void DrawableObject::setActive(bool value) {
	isActive = value;

	if (collider != nullptr && !isActive) {
		map<Collider*, Collider::CollisionState>& colMap = collider->getCollisionMap();
		colMap.clear();
	}
}

bool DrawableObject::getIsActive() {
	return isActive;
}

bool DrawableObject::getMarkedForDelete() {
	return isMarkedForDelete;
}

bool DrawableObject::getCanDraw() {
	return canDraw;
}

void DrawableObject::destroyObject(DrawableObject* obj) {
	obj->isMarkedForDelete = true;
}

void DrawableObject::setAlpha(float value) {
	alpha = value;
}

float DrawableObject::getAlpha() const {
	return alpha;
}