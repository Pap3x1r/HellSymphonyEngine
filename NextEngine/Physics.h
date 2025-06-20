#pragma once

//#include "CollisionHandler.h"
#include "glm.hpp"
#include "Transform.h"
#include <vector>

#define DEFAULT_GRAVITY -1.0f // fine tune later
#define CONST_DELTA_TIME 0.001f // for testing

using namespace std;

class Physics {
	private:
		glm::vec3 lastPos;
		glm::vec2 velocity;
		glm::vec2 acceleration;
		glm::vec2 gravity;
		float mass;
		glm::vec2 force;
		float drag;
		bool enablePhysics;
		bool enableGravity;

	public:
		Physics(Transform& transform);
		void setVelocity(glm::vec2 vel);
		void setAcceleration(glm::vec2 accel);
		void setGravity(glm::vec2 g);
		void setMass(float m);
		void addForce(glm::vec2 f);
		void setDrag(float drag);
		void applyGravity();
		void update(Transform& transform);
		void update(Transform& transform, float dt);

		glm::vec3 getLastPosition();
		glm::vec2 getVelocity();
		glm::vec2 getAcceleration();
		glm::vec2 getGravity();
		float getMass();
		glm::vec2 getForce();
		float getDrag();

		void setLastPosition(glm::vec3 pos);
		void setEnablePhysics(bool flag);
		void setEnableGravity(bool flag);

		bool isGravityEnable();

		//void operator=(Physics& other);
};