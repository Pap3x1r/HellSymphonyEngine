#pragma once
#include "SimpleObject.h"
#include "UIButton.h"
#include <list>

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
	SliderObject();
	SliderObject(string name);
	~SliderObject();
	void update(float dt);
	void setPosition(glm::vec3 position, int type);
	void setColor(glm::vec3 color, int type);
	void setScale(glm::vec3 scale, int type);
	void setValue(float v);
	float getValue() const;
	void setMenuState(MenuState state);
	list<DrawableObject*> getObjectsList() const;
	DrawableObject* getObject(int index);
	glm::vec3 getOriginalWidth() const;
	string getName() const;
};