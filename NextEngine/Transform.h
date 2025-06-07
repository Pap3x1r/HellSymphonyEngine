#pragma once
#include "glm.hpp"

/**
 * @class Transform
 * @brief Represents the position, rotation, and scale of an object in 2D/3D space.
 *
 * Provides utilities for modifying and combining object transformations.
 */
class Transform {
	private:
		glm::vec3 position;   ///< Position in world/local space.
		float rotation;       ///< Rotation in radians.
		glm::vec3 scale;      ///< Scaling factor.
	public:
		/** @brief Default constructor (position: 0, rotation: 0, scale: 1). */
		Transform();
		/**
		 * @brief Parameterized constructor.
		 * @param position Initial position.
		 * @param rotation Initial rotation (in radians).
		 * @param scale Initial scale.
		 */

		 /// @name Setters
		/// @{
		Transform(glm::vec3 position, float rotation, glm::vec3 scale);
		void setPosition(glm::vec3 position);
		void setPosition(float x, float y);
		void setRotationRad(float rotation);
		void setRotationDeg(float rotation);
		void setRotation(float angle);
		void setScale(glm::vec3 scale);
		void setScale(float scale);
		void setScale(float scaleX, float scaleY);
		void scales(glm::vec3 scale);
		void scales(float scale);
		void scales(float scaleX, float scaleY);
		/// @}

		/// @name Transformation Modifiers
		/// @{
		void translate(glm::vec3 translate);
		void translate(float x, float y);
		void rotateRad(float rad);
		void rotateDeg(float deg);
		void rotate(float angle);
		/// @}

		/**
		 * @brief Computes a global transform by combining with another Transform (Collider).
		 * @param objectTransform Another Transform to combine with.
		 * @return Combined Transform.
		 */
		Transform getGlobalTransform(Transform& objectTransform);

		/// @name Getters
		/// @{
		glm::vec3 getPosition();
		float getRotationRad();
		float getRotationDeg();
		float getRotation();
		glm::vec3 getScale() const;

		/**
		 * @brief Gets the 4x4 transformation matrix.
		 * @return glm::mat4 representing translation, rotation, and scale.
		 */
		glm::mat4 getTransformMat4();
		/// @}
		
		/// @name Operators
		/// @{
		Transform operator+(const Transform& other);
		Transform operator-(const Transform& other);
		/// @}
};