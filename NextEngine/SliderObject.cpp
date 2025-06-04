#include "SliderObject.h"

SliderObject::SliderObject() {
	sliderBackground = new SimpleObject("SliderBackground");
	sliderBackground->setColor(1.0f, 1.0f, 1.0f);
	sliderBackground->setTag(Tag::UI);
	//sliderBackground->setMenuState(MenuState::MAIN);
	objectsList.push_back(sliderBackground);


	sliderFill = new SimpleObject("SliderFill");
	sliderFill->setColor(1.0f, 1.0f, 1.0f);
	sliderFill->setTag(Tag::UI);
	//sliderFill->setMenuState(MenuState::MAIN);
	objectsList.push_back(sliderFill);



	sliderHandle = new UIButton("SliderHandle");
	sliderHandle->addColliderComponent();
	sliderHandle->setDrawCollider(true);
	sliderHandle->setCanDrawColliderNew(false);
	sliderHandle->setDraw(true);
	sliderHandle->setHandle(true);
	sliderHandle->setTag(Tag::UI);
	//sliderHandle->setMenuState(MenuState::MAIN);
	sliderHandle->setSlider(this);
	cout << "Handle Slider: " << sliderHandle->getSlider()->getName() << endl;
	objectsList.push_back(sliderHandle);
}

SliderObject::SliderObject(string name) {
	this->name = name;
	sliderBackground = new SimpleObject("SliderBackground");
	sliderBackground->setColor(1.0f, 1.0f, 1.0f);
	sliderBackground->setTag(Tag::UI);
	//sliderBackground->setMenuState(MenuState::MAIN);
	objectsList.push_back(sliderBackground);


	sliderFill = new SimpleObject("SliderFill");
	sliderFill->setColor(1.0f, 1.0f, 1.0f);
	sliderFill->setTag(Tag::UI);
	//sliderFill->setMenuState(MenuState::MAIN);
	objectsList.push_back(sliderFill);



	sliderHandle = new UIButton("SliderHandle");
	sliderHandle->addColliderComponent();
	sliderHandle->setDrawCollider(true);
	sliderHandle->setCanDrawColliderNew(false);
	sliderHandle->setDraw(true);
	sliderHandle->setHandle(true);
	sliderHandle->setTag(Tag::UI);
	//sliderHandle->setMenuState(MenuState::MAIN);
	sliderHandle->setSlider(this);
	cout << "Handle Slider: " << sliderHandle->getSlider()->getName() << endl;
	objectsList.push_back(sliderHandle);
}

SliderObject::~SliderObject() {
	sliderBackground = nullptr;
	sliderFill = nullptr;
	sliderHandle = nullptr;

	objectsList.clear();
}

void SliderObject::update(float dt) {
	// Calculate scaled width for the fill bar
	float fillWidth = value * originalWidth.x;

	// Fill should scale in X and move to the right to stay left-aligned
	glm::vec3 fillScale(fillWidth, sliderFill->getTransform().getScale().y, 1.0f);
	sliderFill->getTransform().setScale(fillScale);

	// Calculate fill position: shifts right as width increases
	float fillX = basePosition.x - (originalWidth.x * 0.5f) + (fillWidth * 0.5f);
	glm::vec3 fillPos = sliderBackground->getTransform().getPosition();
	fillPos.x = fillX;
	sliderFill->getTransform().setPosition(fillPos);

	// Optional: Move handle to match value
	float handleX = basePosition.x - (originalWidth.x * 0.5f) + (fillWidth);
	glm::vec3 handlePos = sliderHandle->getTransform().getPosition();
	handlePos.x = handleX;
	sliderHandle->getTransform().setPosition(handlePos);
}

void SliderObject::setPosition(glm::vec3 position, int type) {
	//type 0 = background, type 1 = fill, type 2 = handle, else all
	basePosition = position;
	if (type == 0) {
		sliderBackground->getTransform().setPosition(position);
	}
	else if (type == 1) {
		sliderFill->getTransform().setPosition(position);
	}
	else if (type == 2) {
		sliderHandle->getTransform().setPosition(position);
	}
	else {
		sliderBackground->getTransform().setPosition(position);
		sliderFill->getTransform().setPosition(position);
		sliderHandle->getTransform().setPosition(position);
	}
}

void SliderObject::setColor(glm::vec3 color, int type) {
	if (type == 0) {
		sliderBackground->setColor(color.x, color.y, color.z);
	}
	else if (type == 1) {
		sliderFill->setColor(color.x, color.y, color.z);
	}
	else {
		sliderBackground->setColor(color.x, color.y, color.z);
		sliderFill->setColor(color.x, color.y, color.z);
	}
}

void SliderObject::setScale(glm::vec3 scale, int type) {
	//type 0 = background, type 1 = fill, type 2 = handle, else all
	if (type == 0) {
		sliderBackground->getTransform().setScale(scale);
		originalWidth = scale;
	}
	else if (type == 1) {
		sliderFill->getTransform().setScale(scale);
		originalWidth = scale;
	}
	else if (type == 2) {
		sliderHandle->getTransform().setScale(scale);
	}
	else {
		sliderBackground->getTransform().setScale(scale);
		sliderFill->getTransform().setScale(scale);
		sliderHandle->getTransform().setScale(scale);
	}
}

void SliderObject::setValue(float v) {
	value = glm::clamp(v, 0.0f, 1.0f);
}

float SliderObject::getValue() const {
	return value;
}

void SliderObject::setMenuState(MenuState state) {
	for (DrawableObject* obj : objectsList) {
		obj->setMenuState(state);
	}
}

list<DrawableObject*> SliderObject::getObjectsList() const {
	return objectsList;
}

DrawableObject* SliderObject::getObject(int index) {
	if (index < 0 || index >= objectsList.size()) {
		return nullptr;
	}

	auto it = objectsList.begin();
	std::advance(it, index);
	return *it;
}

glm::vec3 SliderObject::getOriginalWidth() const {
	return originalWidth;
}

string SliderObject::getName() const {
	return name;
}