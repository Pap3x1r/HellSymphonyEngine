#pragma once
#include "SimpleObject.h"
#include "UIButton.h"
#include <list>

/**
 * @class SliderObject
 * @brief Represents a UI slider with background, fill, and handle components.
 *
 * Manages slider value, colors, position, scale, and related drawable objects.
 */
class SliderObject {

	string name = "Slider Object";

	float value;

	glm::vec3 bgColor;
	glm::vec3 fillColor;

	glm::vec3 position;

	glm::vec3 originalWidth;
	glm::vec3 basePosition;

	SimpleObject* sliderBackground;
	SimpleObject* sliderFill;
	UIButton* sliderHandle;

	list<DrawableObject*> objectsList;

public:
	/**
	 * @brief Default constructor initializes the slider with default values.
	 */
	SliderObject();
	/**
	 * @brief Constructor initializes the slider with a given name.
	 * @param name Name to assign to the slider.
	 */
	SliderObject(string name);
	/**
	 * @brief Destructor to clean up any allocated resources.
	 */
	~SliderObject();
	/**
	 * @brief Updates the slider state, typically called every frame.
	 * @param dt Delta time since last update.
	 */
	void update(float dt);
	/**
	 * @brief Sets the slider's position.
	 * @param position New position as a glm::vec3.
	 * @param type Type or part of slider to set position for (e.g. background, fill, handle).
	 */
	void setPosition(glm::vec3 position, int type);
	/**
	 * @brief Sets the color of a slider component.
	 * @param color Color vector (RGB) to set.
	 * @param type Type or part of slider to set color for (e.g. background, fill).
	 */
	void setColor(glm::vec3 color, int type);

	/**
	 * @brief Sets the scale of a slider component.
	 * @param scale Scale vector to apply.
	 * @param type Type or part of slider to scale (e.g. background, fill, handle).
	 */
	void setScale(glm::vec3 scale, int type);

	/**
	 * @brief Sets the current value of the slider.
	 * @param v New value for the slider.
	 */
	void setValue(float v);

	/**
	 * @brief Returns the current slider value.
	 * @return Slider value as float.
	 */
	float getValue() const;
	/**
	 * @brief Sets the current menu state (possibly affects appearance or behavior).
	 * @param state The menu state to set.
	 */
	void setMenuState(MenuState state);

	/**
	 * @brief Returns the list of drawable objects associated with the slider.
	 * @return List of DrawableObject pointers.
	 */
	std::list<DrawableObject*> getObjectsList() const;

	/**
	 * @brief Gets a drawable object by index.
	 * @param index Index in the drawable objects list.
	 * @return Pointer to DrawableObject at given index.
	 */
	DrawableObject* getObject(int index);
	/**
	 * @brief Returns the original width (scale) of the slider.
	 * @return Original width as glm::vec3.
	 */
	glm::vec3 getOriginalWidth() const;

	/**
	 * @brief Returns the slider's name.
	 * @return Slider name string.
	 */
	std::string getName() const;
};