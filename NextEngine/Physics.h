#pragma once

//#include "CollisionHandler.h"
#include "glm.hpp"
#include "Transform.h"
#include <vector>

#define DEFAULT_GRAVITY -1.0f // fine tune later
#define CONST_DELTA_TIME 0.001f // for testing

using namespace std;

/**
 * @class Physics
 * @brief Handles 2D physics calculations including motion, forces, gravity, and drag.
 */
class Physics {
	private:
		glm::vec3 lastPos;         ///< Last known position of the object (for interpolation or rollback).
		glm::vec2 velocity;        ///< Current velocity of the object.
		glm::vec2 acceleration;    ///< Acceleration applied to the object.
		glm::vec2 gravity;         ///< Gravity vector.
		float mass;                ///< Mass of the object.
		glm::vec2 force;           ///< Net force applied to the object.
		float drag;                ///< Drag coefficient.
		bool enablePhysics;        ///< Flag to enable or disable physics updates.
		bool enableGravity;        ///< Flag to enable or disable gravity.

	public:

		/**
		 * @brief Constructor that binds the physics system to a transform.
		 * @param transform The transform to be updated by this physics component.
		 */
		Physics(Transform& transform);

        /// @name Setters
    /// @{
        void setVelocity(glm::vec2 vel);
        void setAcceleration(glm::vec2 accel);
        void setGravity(glm::vec2 g);
        void setMass(float m);
        void addForce(glm::vec2 f);       ///< Adds a force vector to the current force.
        void setDrag(float drag);
        void setLastPosition(glm::vec3 pos);
        void setEnablePhysics(bool flag); ///< Enable or disable physics processing.
        void setEnableGravity(bool flag); ///< Enable or disable gravity.
        /// @}

        /// @name Getters
        /// @{
        glm::vec3 getLastPosition();
        glm::vec2 getVelocity();
        glm::vec2 getAcceleration();
        glm::vec2 getGravity();
        float getMass();
        glm::vec2 getForce();
        float getDrag();
        bool isGravityEnable();           ///< Check if gravity is enabled.
        /// @}

        /**
         * @brief Applies gravity to the current force, if gravity is enabled.
         */
        void applyGravity();

        /**
         * @brief Updates the associated Transform based on physics simulation.
         * @param transform The transform to be updated.
         */
        void update(Transform& transform);

        /**
         * @brief Updates the transform using a specific delta time.
         * @param transform The transform to be updated.
         * @param dt Delta time for the physics step.
         */
        void update(Transform& transform, float dt);

        // Copy assignment operator intentionally commented out
        // void operator=(Physics& other);
};