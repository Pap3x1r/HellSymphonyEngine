#pragma once
#include "TexturedObject.h"
#include "UIText.h"
#include "GameEngine.h"
#include "imgui.h"
#include <functional>

class SliderObject;

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
	
	UIButton() {
		DrawableObject::setName(name);
		setDrawCollider(true);
		setCanDrawColliderNew(false);
		setTag(Tag::UI);
	};

	UIButton(string name) {
		this->name = name;
		DrawableObject::setName(this->name);
		setDrawCollider(true);
		setCanDrawColliderNew(false);
		setTag(Tag::UI);
	};

	~UIButton() {
		label = nullptr;
	}

	void OnClick() {
		if (func) {
			func();
		}
	}

	void setFunction(function<void()> func) {
		this->func = func;
	}

	void update(float dt);
	bool isHovered(int mouseX, int mouseY);
	bool getMouseOver() const;

	void setMouseOver(bool value) {
		mouseOver = value;
	}

	void setEnable(bool value) {
		isEnable = value;
	}

	bool getEnable() const {
		return isEnable;
	}

	void setLabel(UIText* text) {
		label = text;
	}

	UIText* getLabel() const {
		return label;
	}

	string getName() const {
		return name;
	}

	void setHandle(bool value) {
		isHandle = value;
	}

	bool getHandle() const {
		return isHandle;
	}

	void setSlider(SliderObject* obj) {
		slider = obj;
	}

	SliderObject* getSlider() const {
		return slider;
	}

	void setActive(bool a) {
		active = a;
	}

	bool getActive() const {
		return active;
	}
};