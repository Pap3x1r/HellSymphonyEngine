#pragma once
#include "TexturedObject.h"
#include "UIText.h"
#include "GameEngine.h"
#include "imgui.h"
#include <functional>

class UIButton : public TexturedObject {
	bool isEnable = true;
	bool mouseOver = false;
	function<void()> func;
	string name;

	float xPosition;
	float yPosition;

	float xScale;
	float yScale;

	UIText* label;

public:
	
	UIButton(string name) {
		this->name = name;
		setDrawCollider(true);
		setCanDrawColliderNew(true);
	};

	~UIButton() {
		label = nullptr;
	}

	void OnClick() {
		if (func) {
			func();
		}
	}

	void SetFunction(function<void()> func) {
		this->func = func;
	}

	void update(float dt);
	bool isHovered(int mouseX, int mouseY);
	bool getMouseOver() const;
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
};