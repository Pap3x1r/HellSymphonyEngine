#pragma once

#include "Animation.h"
#include "DrawableObject.h"
#include "Physics.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <map>

#include "VergilMovementState.h"


/**
 * @class TexturedObject
 * @brief A renderable game object that uses a texture and supports animation.
 *
 * Inherits from DrawableObject and adds texture mapping, animation handling,
 * sprite offsetting, hit effect, and color override features.
 */
class TexturedObject : public DrawableObject
{	
	glm::vec3 spriteOffset;        ///< Offset to apply to sprite rendering
	unsigned int texture;          ///< OpenGL texture ID
	Animation* animation;          ///< Pointer to the object's animation

	float hitEffectStrength = 0;   ///< Strength of the hit visual effect
	float alpha = 1.0f;            ///< Transparency level
	glm::vec4 newColor = { 1.0f, 0.0f, 0.0f, 1.0f }; ///< Color override (RGBA)


	/*bool animated = false;
	int rowCount;
	int colCount;
	float offsetX;
	float offsetY;*/

public:
	/** @brief Default constructor */
	TexturedObject();
	/** @brief Constructor with name parameter */
	TexturedObject(std::string name);
	/** @brief Destructor */
	~TexturedObject();
	/**
	 * @brief Sets a static texture (non-animated).
	 * @param path Path to the texture file.
	 */
	void setTexture(std::string path);
	/**
	 * @brief Sets up an animated texture.
	 * @param path Path to sprite sheet.
	 * @param row Number of rows in the sprite sheet.
	 * @param col Number of columns in the sprite sheet.
	 * @param startFrame Initial frame to start on.
	 */
	void setTexture(string path, int row, int col, int startFrame);
	/**
	 * @brief Sets up an animated texture with loop option.
	 * @param path Path to sprite sheet.
	 * @param row Number of rows.
	 * @param col Number of columns.
	 * @param startFrame Starting frame.
	 * @param loop Whether the animation should loop.
	 */
	void setTexture(string path, int row, int col, int startFrame, bool loop);
	/**
	 * @brief Initializes animation with a given grid.
	 * @param row Number of rows.
	 * @param column Number of columns.
	 */
	void initAnimation(int row, int column);
	/**
	 * @brief Renders the object with its texture and animation.
	 * @param globalModelTransform Combined world/model transform matrix.
	 */
	void render(glm::mat4 globalModelTransform);
	/**
	 * @brief Gets the animation component.
	 * @return Pointer to the Animation instance.
	 */
	Animation* getAnimationComponent();
	/**
	 * @brief Checks if the object has an animation.
	 * @return True if animated, false otherwise.
	 */
	bool isAnimated();
	//void setFrame(float row, float column);
	/**
	 * @brief Sets an offset to the sprite rendering.
	 * @param vector3 Offset as a vec3.
	 */
	void setSpriteOffset(glm::vec3 vector3);
	/**
	 * @brief Sets the strength of the hit effect.
	 * @param value Hit effect intensity.
	 */
	void setHitEffectStrength(float value);
	/**
	 * @brief Gets the strength of the hit effect.
	 * @return Float value representing the strength.
	 */
	float getHitEffectStrength();
	/**
	 * @brief Overrides the object's alpha (transparency).
	 * @param value Alpha value [0.0 - 1.0].
	 */
	void setAlpha(float value) override;
	/**
	 * @brief Gets the current alpha value.
	 * @return Alpha transparency as a float.
	 */
	float getAlpha() const override;
	/**
	 * @brief Sets the override color for the sprite.
	 * @param v4 RGBA color vector.
	 */
	void setNewColor(glm::vec4 v4);
	/**
	 * @brief Gets the override color.
	 * @return RGBA color vector.
	 */
	glm::vec4 getNewColor() const;
};