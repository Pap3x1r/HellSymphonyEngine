#include "CollisionHandler.h"

constexpr unsigned int COLLISION_RESOLUTION = 4;

bool checkCollision(Collider* col1, Transform& t1, Collider* col2, Transform& t2) {
	Transform globalT1 = col1->getGlobalTransform(t1);
	//globalT1.scales(col1->getWidth(), col1->getHeight());
	glm::vec3 pos1 = globalT1.getPosition();
	float halfWidth1 = abs(globalT1.getScale().x * col1->getWidth() / 2.0f);
	float halfHeight1 = abs(globalT1.getScale().y * col1->getHeight() / 2.0f);
	//unsigned char flag1 = col1->getCollisionFlag();

	Transform globalT2 = col2->getGlobalTransform(t2);
	//globalT2.scales(col2->getWidth(), col2->getHeight());
	glm::vec3 pos2 = globalT2.getPosition();
	float halfWidth2 = abs(globalT2.getScale().x * col2->getWidth() / 2.0f);
	float halfHeight2 = abs(globalT2.getScale().y * col2->getHeight() / 2.0f);
	//unsigned char flag2 = col2->getCollisionFlag();

	bool xAxis = abs(pos1.x - pos2.x) < (halfWidth1 + halfWidth2);
	bool yAxis = abs(pos1.y - pos2.y) < (halfHeight1 + halfHeight2);

	//cout << "check" << endl;

	bool collided = xAxis && yAxis;
	//updateCollisionState(col1, col2, collided);

	return collided;
}

bool checkCollisionPoint(Collider* col, Transform& t, glm::vec2 point) {
	Transform globalT = col->getGlobalTransform(t);
	glm::vec3 pos = globalT.getPosition();
	float halfWidth = abs(globalT.getScale().x * col->getWidth() / 2.0f);
	float halfHeight = abs(globalT.getScale().y * col->getHeight() / 2.0f);

	bool xAxis = pos.x - halfWidth <= point.x && point.x <= pos.x + halfWidth;
	bool yAxis = pos.y - halfHeight <= point.y && point.y <= pos.y + halfHeight;

	//cout << "check pos: " << pos.x << " " << pos.y << "point: " << point.x << " " << point.y << endl;

	return xAxis && yAxis;
}

void updateCollisionState(Collider* col1, Collider* col2, bool collided) {
	std::map<Collider*, Collider::CollisionState>& colMap1 = col1->getCollisionMap();

	bool found = colMap1.find(col2) != colMap1.end();
	if (collided) {
		if (!found) {
			colMap1[col2] = Collider::ENTER;
			return;
		}

		colMap1[col2] = Collider::STAY;
		return;
	}

	if (found) {
		if (colMap1[col2] == Collider::EXIT) {
			colMap1.erase(col2);

			std::map<Collider*, Collider::CollisionState>& colMap2 = col2->getCollisionMap();
			colMap2.erase(col1);

			return;
		}

		colMap1[col2] = Collider::EXIT;
		return;
	}
}

void handleObjectCollision(list<DrawableObject*>& objects) {
	for (list<DrawableObject*>::iterator i = objects.begin(); i != objects.end(); i++) {

		if ((*i)->getColliderComponent() != nullptr) {
			(*i)->getColliderComponent()->setCollisionFlag(0);
		}

		for (list<DrawableObject*>::iterator j = objects.begin(); j != objects.end(); j++) {
			if (i == j) {
				continue;
			}


			DrawableObject* obj1 = *i;
			DrawableObject* obj2 = *j;

			if (shouldIgnoreCollision(obj1, obj2)) {
				continue;
			}

			Collider* col1 = obj1->getColliderComponent();
			Collider* col2 = obj2->getColliderComponent();

			if (col1 == nullptr || col2 == nullptr) {
				continue;
			}

			if (!col1->isEnable() || !col2->isEnable()) {
				continue;
			}

			Transform t1 = obj1->getTransform();
			Transform t2 = obj2->getTransform();

			bool collided = false;

			Physics* phys1 = obj1->getPhysicsComponent();

			if (!obj1->getIsActive() || !obj2->getIsActive()) {
				collided = false;
			}
			else if (phys1 != nullptr) {

				if (shouldResolveCollision(obj1, obj2)) {
					continue;
				}

				Collider tempCol = *col1; // shallow copy
				glm::vec3 dir = t1.getPosition() - phys1->getLastPosition();
				dir /= (float)COLLISION_RESOLUTION;
				for (int k = 0; k < COLLISION_RESOLUTION; k++) {
					collided = checkCollision(&tempCol, t1, col2, t2);

					if (collided) {
						obj1->getTransform() = t1;
						break;
					}

					t1.translate(dir);
				}
			}
			else {
				collided = checkCollision(col1, t1, col2, t2);
			}

			updateCollisionState(col1, col2, collided);

			if (collided) {
				//system("cls");
				//cout << obj1->getName() << " collided with " << obj2->getName() << endl;

				if (col1->isTrigger() || col2->isTrigger()) {
					//cout << "Trigger collision" << endl;
					/// Do nothing
					continue;
				}

				resolveCollision(obj1, obj2);
			}
			//else {
			//	//system("cls");
			//	//cout << "no collision" << endl;
			//}
		}
	}
}

void resolveCollision(DrawableObject* obj1, DrawableObject* obj2) {
	Physics* phys1 = obj1->getPhysicsComponent();
	Physics* phys2 = obj2->getPhysicsComponent();

	if (phys1 == nullptr) {
		return;
	}

	if (phys1 != nullptr && phys2 != nullptr) {
		return; // currently ignoring collision between two physics objects
	}

	Transform& t1 = obj1->getTransform();
	Transform& t2 = obj2->getTransform();

	Collider* col1 = obj1->getColliderComponent();
	Collider* col2 = obj2->getColliderComponent();

	Transform globalT1 = col1->getGlobalTransform(t1);
	Transform globalT2 = col2->getGlobalTransform(t2);

	glm::vec3 pos1 = globalT1.getPosition();
	glm::vec3 pos2 = globalT2.getPosition();
	glm::vec3 lastPos = obj1->getPhysicsComponent()->getLastPosition();


	float halfWidth1 = abs(globalT1.getScale().x * col1->getWidth() / 2.0f);
	float halfHeight1 = abs(globalT1.getScale().y * col1->getHeight() / 2.0f);

	float halfWidth2 = abs(globalT2.getScale().x * col2->getWidth() / 2.0f);
	float halfHeight2 = abs(globalT2.getScale().y * col2->getHeight() / 2.0f);

	float distX = abs(pos2.x - pos1.x);
	float distY = abs(pos2.y - pos1.y);

	float intersectedX = halfWidth1 + halfWidth2 - distX;
	float intersectedY = halfHeight1 + halfHeight2 - distY;

	glm::vec3 dir = (lastPos + col1->getTransform().getPosition()) - pos2;
	dir.x /= halfWidth1 * 2.0f + halfWidth2 * 2.0f;
	dir.y /= halfHeight1 * 2.0f + halfHeight2 * 2.0f;

	glm::vec3 newPos1 = pos1;
	//glm::vec3 newPos2 = pos2;
	glm::vec2 vel1 = phys1->getVelocity();
	//glm::vec2 vel2 = phys2 != nullptr ? phys2->getVelocity() : glm::vec2();

	COLLISION_FLAG collisionFlag = col1->getCollisionFlag();

	if (abs(dir.y) >= abs(dir.x)) {
		if (pos1.y - halfHeight1 >= pos2.y) {
			newPos1.y += intersectedY;
			//newPos2.y -= intersectedY;
			collisionFlag |= COLLISION_DOWN;
		}
		else if (pos1.y + halfHeight1 <= pos2.y) {
			newPos1.y -= intersectedY;
			//newPos2.y += intersectedY;
			collisionFlag |= COLLISION_UP;
		}
		vel1.y = 0.0f;
		//vel2.y = 0.0f;
	}
	else {
		if (pos1.x - halfWidth1 >= pos2.x) {
			newPos1.x += intersectedX;
			//newPos2.x -= intersectedX;
			collisionFlag |= COLLISION_LEFT;
		}
		else if (pos1.x + halfWidth1 <= pos2.x) {
			newPos1.x -= intersectedX;
			//newPos2.x += intersectedX;
			collisionFlag |= COLLISION_RIGHT;
		}
		vel1.x = 0.0f;
		//vel2.x = 0.0f;
	}

	col1->setCollisionFlag(collisionFlag);

	//if (phys2 != nullptr) {
	//	phys2->setVelocity(vel2);
	//	t2.setPosition(newPos2);
	//	phys2->setLastPosition(pos2);
	//} 
	//else {
	//	phys1->setVelocity(vel1);
	//	t1.setPosition(newPos1);
	//	phys1->setLastPosition(pos1);
	//}

	phys1->setVelocity(vel1);
	t1.setPosition(newPos1 - col1->getTransform().getPosition());
	//t1.setPosition(newPos1);
	phys1->setLastPosition(pos1);
}

bool shouldIgnoreCollision(DrawableObject* obj1, DrawableObject* obj2) {
	Tag tag1 = obj1->getTag();
	Tag tag2 = obj2->getTag();

	if ((tag1 == Tag::Player && tag2 == Tag::GroundChecker) || (tag1 == Tag::GroundChecker && tag2 == Tag::Player)) {
		return true;
	}

	if ((tag1 == Tag::Player && tag2 == Tag::UI) || (tag1 == Tag::GroundChecker && tag2 == Tag::UI)) {
		return true;
	}

	return false;
}

bool shouldResolveCollision(DrawableObject* obj1, DrawableObject* obj2) {
	Tag tag1 = obj1->getTag();
	Tag tag2 = obj2->getTag();

	if ((tag1 == Tag::Player && tag2 == Tag::Enemy) || (tag1 == Tag::Enemy && tag2 == Tag::Player)) {
		return true;
	}

	if ((tag1 == Tag::Player && tag2 == Tag::EnemyAttack) || (tag1 == Tag::EnemyAttack && tag2 == Tag::Player)) {
		return true;
	}

	if ((tag1 == Tag::Player && tag2 == Tag::UI) || (tag1 == Tag::UI && tag2 == Tag::Player)) {
		return true;
	}

	return false;
}