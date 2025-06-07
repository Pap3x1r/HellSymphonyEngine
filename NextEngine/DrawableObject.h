#pragma once
#include "glm.hpp"
#include "Collider.h"
#include "Physics.h"
#include "Transform.h"
#include <string>
#include <list>
#include <vector>

using namespace std;

class Collider; // forward declaration

/**
 * @enum MenuState
 * @brief Represents different UI or game menu states an object may be linked to.
 */
enum MenuState {
	NONE,
	MAIN,
	PAUSE,
	OPTIONS,
	AUDIO,
	CONTROLLER,
	KEYBOARD,
	CREDITS,
	QUITCONFIRM,
	SAVECONFIRM,
	DEATH,
	VICTORY,
	IGNORE
};

/**
 * @enum Tag
 * @brief Represents categories/types for game objects (used for filtering logic).
 */
enum class Tag {
	Player,
	PlayerAttack,
	Enemy,
	EnemyAttack,
	Floor,
	GroundChecker,
	UI,
	Default
};

/**
 * @class DrawableObject
 * @brief Base class for any renderable and interactable game object.
 *
 * Contains logic for drawing, updating, collision, physics, and menu state tracking.
 */
class DrawableObject {
private:
	bool canDrawColliderNew;
	bool canDrawCollider;
	bool canDraw;
	void processCollider();

	bool isActive;
	bool isMarkedForDelete;

	MenuState menuState = MenuState::NONE;
	vector<MenuState> menuStateVec;
	float alpha = 1.0f; // Default alpha (visible)
	float maximumAlpha = 1.0f;

protected:
	string name = "Object";
	Tag tag;
	Transform transform;
	Physics* physics;
	Collider* collider;

	// --- Collision Events ---
	virtual void onCollisionEnter(Collider* collider);
	virtual void onCollisionStay(Collider* collider);
	virtual void onCollisionExit(Collider* collider);

	virtual void onTriggerEnter(Collider* collider);
	virtual void onTriggerStay(Collider* collider);
	virtual void onTriggerExit(Collider* collider);

public:
	int drawLayer = 0; ///< Draw layer priority (higher = drawn first)

	// --- Tag and Name ---
	string getName();
	void setName(string name);

	Tag getTag() const {
		return tag;
	}

	void setTag(Tag newTag) {
		tag = newTag;
	}

	// --- Transform and Components ---
	Transform& getTransform();
	glm::mat4 getTransformMat4();

	Physics* getPhysicsComponent();
	Collider* getColliderComponent();

	void addPhysicsComponent();
	void addPhysicsComponent(Physics& physics);
	void addColliderComponent();
	void addColliderComponent(Collider& collider);

	// --- Update ---
	virtual void updateBehavior();
	virtual void update();
	void update(float dt);

	/** @brief Default constructor */
	DrawableObject();

	/** @brief Constructor with name parameter */
	DrawableObject(string name);

	/** @brief Virtual destructor */
	virtual ~DrawableObject();

	/** @brief Abstract render function to be overridden by derived classes */
	virtual void render(glm::mat4 globalModelTransform) = 0;

	// --- Drawing ---
	void setDrawCollider(bool value);
	void setDraw(bool value);
	void drawCollider();

	void setActive(bool value);

	bool getIsActive();
	bool getMarkedForDelete();

	bool getCanDraw();

	void setCanDrawColliderNew(bool value) {
		canDrawColliderNew = value;
	}

	bool getCanDrawCollider() {
		return canDrawCollider;
	}

	bool* getCanDrawColliderAddress() {
		return &canDrawColliderNew;
	}

	// --- Menu State ---
	void setMenuState(MenuState newMenuState) {
		menuState = newMenuState;
		menuStateVec.push_back(newMenuState);
	}

	MenuState getMenuState() const {
		return menuState;
	}

	void addMenuStateToVec(MenuState newMenuState) {
		menuStateVec.push_back(newMenuState);
	}

	vector<MenuState> getMenuStateVec() const {
		return menuStateVec;
	}

	// --- Alpha/Transparency ---
	virtual void setAlpha(float value);

	virtual float getAlpha() const;

	void setMaximumAlpha(float alpha) {
		maximumAlpha = alpha;
	}

	float getMaximumAlpha() const {
		return maximumAlpha;
	}

	/**
	 * @brief Marks the object for deletion and destroys it.
	 * @param obj Pointer to DrawableObject to destroy.
	 */
	static void destroyObject(DrawableObject* obj);
};