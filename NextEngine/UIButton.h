#pragma once
#include "TexturedObject.h"
#include <functional>

class UIButton : public TexturedObject {
	bool mouseOver = false;
	function<void()> onClick;

public:
	
	UIButton(function<void()> func) : onClick(func) {
		setDrawCollider(true);
		setCanDrawColliderNew(true);
	};

	void update(float dt);
	bool isMouseOver();
};