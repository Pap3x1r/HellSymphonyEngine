#pragma once
#include "TexturedObject.h"
#include "GameEngine.h"
#include <functional>

class UIButton : public TexturedObject {
	bool mouseOver = false;
	function<void()> func;
public:
	
	UIButton() {
		setDrawCollider(true);
		setCanDrawColliderNew(true);
	};

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
};