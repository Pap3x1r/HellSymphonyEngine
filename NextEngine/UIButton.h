#pragma once
#include "TexturedObject.h"
#include "UIText.h"
#include "GameEngine.h"
#include "imgui.h"
#include <functional>

class SliderObject;

/**
 * @class UIButton
 * @brief UI button class with click functionality, hover detection, and optional label and slider.
 *
 * Extends TexturedObject and supports:
 * - Activation and enable/disable states.
 * - Mouse hover detection.
 * - Function callback on click.
 * - Associated UIText label and SliderObject.
 */
class UIButton : public TexturedObject {
	bool active = true;
	bool isEnable = true;
	bool mouseOver = false;
	function<void()> func;
	string name = "Button";

	float xPosition;
	float yPosition;

	float xScale;
	float yScale;

	UIText* label = nullptr;
	SliderObject* slider = nullptr;
	
	bool isHandle = false;

public:
	/**
	 * @brief Default constructor initializing the button with default name and properties.
	 */
	UIButton() {
		DrawableObject::setName(name);
		setDrawCollider(true);
		setCanDrawColliderNew(false);
		setTag(Tag::UI);
	};
	/**
	 * @brief Constructor that initializes the button with a custom name.
	 * @param name Name to assign to the button.
	 */
	UIButton(string name) {
		this->name = name;
		DrawableObject::setName(this->name);
		setDrawCollider(true);
		setCanDrawColliderNew(false);
		setTag(Tag::UI);
	};
	/**
	 * @brief Destructor cleans up associated label pointer (does not delete).
	 */
	~UIButton() {
		label = nullptr;
	}
	/**
	 * @brief Called when the button is clicked; executes the bound function if any.
	 */
	void OnClick() {
		if (func) {
			func();
		}
	}
	/**
	 * @brief Sets the callback function to be executed on click.
	 * @param func A std::function<void()> callback.
	 */
	void setFunction(function<void()> func) {
		this->func = func;
	}
	/**
	 * @brief Updates the button state, typically called every frame.
	 * @param dt Delta time since last update.
	 */
	void update(float dt);
	/**
	 * @brief Checks whether the mouse coordinates hover over the button.
	 * @param mouseX X coordinate of the mouse.
	 * @param mouseY Y coordinate of the mouse.
	 * @return True if mouse is over the button; false otherwise.
	 */
	bool isHovered(int mouseX, int mouseY);
	/**
	 * @brief Gets whether the mouse is currently over the button.
	 * @return True if hovered; false otherwise.
	 */
	bool getMouseOver() const;

	/**
	 * @brief Sets the mouse hover state.
	 * @param value True if mouse is over the button, false otherwise.
	 */
	void setMouseOver(bool value) {
		mouseOver = value;
	}
	/**
	 * @brief Enables or disables the button.
	 * @param value True to enable, false to disable.
	 */
	void setEnable(bool value) {
		isEnable = value;
	}
	/**
	 * @brief Returns whether the button is enabled.
	 * @return True if enabled; false otherwise.
	 */
	bool getEnable() const {
		return isEnable;
	}
	/**
	 * @brief Sets the label text object associated with this button.
	 * @param text Pointer to a UIText object.
	 */
	void setLabel(UIText* text) {
		label = text;
	}
	/**
	 * @brief Returns the label text object associated with this button.
	 * @return Pointer to UIText label.
	 */
	UIText* getLabel() const {
		return label;
	}
	/**
	 * @brief Returns the button's name.
	 * @return The button name string.
	 */
	string getName() const {
		return name;
	}
	/**
	 * @brief Sets whether this button acts as a slider handle.
	 * @param value True if it is a handle, false otherwise.
	 */
	void setHandle(bool value) {
		isHandle = value;
	}
	/**
	 * @brief Gets whether this button acts as a slider handle.
	 * @return True if handle, false otherwise.
	 */
	bool getHandle() const {
		return isHandle;
	}
	/**
	 * @brief Sets the slider object linked to this button.
	 * @param obj Pointer to a SliderObject.
	 */
	void setSlider(SliderObject* obj) {
		slider = obj;
	}
	/**
	 * @brief Gets the slider object linked to this button.
	 * @return Pointer to SliderObject.
	 */
	SliderObject* getSlider() const {
		return slider;
	}
	/**
	 * @brief Sets the active state of the button.
	 * @param a True to activate, false to deactivate.
	 */
	void setActive(bool a) {
		active = a;
	}
	/**
	 * @brief Returns whether the button is active.
	 * @return True if active; false otherwise.
	 */
	bool getActive() const {
		return active;
	}
};