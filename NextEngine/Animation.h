#pragma once

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Transform.h"
#include <string>
#include <unordered_map>

class TexturedObject;

using namespace std;

/**
 * @struct State
 * @brief Represents an animation state with a name, row index, and frame count.
 */
struct State {
	State() : name(""), row(-1), frameCount(1) {}
	State(string name, int row, int frameCount) : name(name), row(row), frameCount(frameCount) {}
	string name;
	int row;
	int frameCount;
};

/**
 * @class Animation
 * @brief Handles sprite sheet animations and state management for animated objects.
 */
class Animation {
	private:
		// Animator state machine data
		unordered_map<string, State> states;  ///< All possible animation states by name
		State currentState;                   ///< Currently active animation state
		int currentFrame = 0;                 ///< Current frame index in the animation
		int startingFrame = 0;                ///< Frame to start animation from
		bool loop = true;                    ///< Should the animation loop?
		bool animationCompleted = false;    ///< True if a non-looping animation finished

		// Sprite sheet animation data
		unsigned int& texture;               ///< Reference to the texture ID used for this animation
		int rowCount = 1;                   ///< Total rows in the sprite sheet
		int colCount = 1;                   ///< Total columns (frames per row) in the sprite sheet
		float offsetX = 0.0f;               ///< X offset for rendering the sprite
		float offsetY = 0.0f;               ///< Y offset for rendering the sprite

		float animationTimer = 0.0f;        ///< Timer to track animation frame duration

		glm::vec3 animOffset = { 0.0f, 0.0f, 0.0f }; ///< Positional offset applied during rendering

		TexturedObject* parent = nullptr;   ///< Pointer to the parent object owning this animation

	public:
		/**
		 * @brief Adds a new animation state.
		 * @param name State identifier.
		 * @param row Row index in the sprite sheet for the frames.
		 * @param frameCount Number of frames in this state.
		 */
		void addState(string name, int row, int frameCount);
		/**
		 * @brief Sets the current animation state by name.
		 * @param name State name to switch to.
		 */
		void setState(string name);
		/**
		 * @brief Updates the current animation state by advancing frames based on delta time.
		 * @param dt Time elapsed since last update.
		 */
		void updateCurrentState(float dt);

		/**
		 * @brief Constructs an Animation object tied to a texture.
		 * @param texture Reference to an OpenGL texture ID.
		 */
		Animation(unsigned int& texture);

		/**
		 * @brief Renders the current frame of the animation.
		 * @param globalModelTransform The global transform matrix.
		 * @param transform Local transform of the object.
		 */
		void render(glm::mat4 globalModelTransform, Transform& transform);

		/**
		 * @brief Sets the animation frame by row and column on the sprite sheet.
		 * @param row Row index.
		 * @param column Column index.
		 */
		void setFrame(int row, int column);

		/**
		 * @brief Sets the dimensions of the sprite sheet (rows and columns).
		 * @param row Number of rows.
		 * @param col Number of columns.
		 */
		void setDimension(int row, int col);

		/**
		 * @brief Changes the texture used for the animation.
		 * @param newTexture New OpenGL texture ID.
		 */
		void setTexture(unsigned int newTexture);

		/**
		 * @brief Sets the starting frame of the animation.
		 * @param frame Frame index to start from.
		 */
		void setStartingFrame(int frame);

		/**
		 * @brief Sets positional offset for rendering.
		 * @param offset 3D vector offset.
		 */
		void setAnimOffset(glm::vec3 offset);

		/**
		 * @brief Sets whether the animation should loop.
		 * @param value True to loop, false to play once.
		 */
		void setLoop(bool value) {
			loop = value;
		}

		/**
		 * @brief Sets the horizontal offset for rendering the sprite.
		 * @param offset Offset value.
		 */
		void setOffsetX(float offset) {
			offsetX = offset;
		}

		/**
		 * @brief Sets the vertical offset for rendering the sprite.
		 * @param offset Offset value.
		 */
		void setOffsetY(float offset) {
			offsetY = offset;
		}

		/**
		 * @brief Sets the parent object owning this animation.
		 * @param obj Pointer to the parent TexturedObject.
		 */
		void setParent(TexturedObject* obj) {
			parent = obj;
		}

		/**
		 * @brief Returns whether a non-looping animation has completed.
		 * @return True if animation completed.
		 */
		bool getAnimationCompleted() const {
			return animationCompleted;
		}
};