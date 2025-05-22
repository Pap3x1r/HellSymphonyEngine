#pragma once

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Transform.h"
#include <string>
#include <unordered_map>

class TexturedObject;

using namespace std;

struct State {
	State() : name(""), row(-1), frameCount(1) {}
	State(string name, int row, int frameCount) : name(name), row(row), frameCount(frameCount) {}
	string name;
	int row;
	int frameCount;
};

class Animation {
	private:
		//Animator
		unordered_map<string, State> states;
		State currentState;
		int currentFrame;
		int startingFrame;
		bool loop = true;
		bool animationCompleted = false; //For object without loop;

		// Animation
		unsigned int& texture;
		int rowCount;
		int colCount;
		float offsetX;
		float offsetY;

		float animationTimer = 0.0f;

		glm::vec3 animOffset = { 0.0f,0.0f,0.0f };

		TexturedObject* parent = nullptr;

	public:
		//Animator
		void addState(string name, int row, int frameCount);
		void setState(string name);
		void updateCurrentState(float dt);

		//Animation
		Animation(unsigned int& texture);
		void render(glm::mat4 globalModelTransform, Transform& transform);
		void setFrame(int row, int column);
		void setDimension(int row, int col);
		void setTexture(unsigned int newTexture);
		void setStartingFrame(int frame);

		void setAnimOffset(glm::vec3 offset);
		void setLoop(bool value) {
			loop = value;
		}
		void setOffsetX(float offset) {
			offsetX = offset;
		}
		void setOffsetY(float offset) {
			offsetY = offset;
		}
		void setParent(TexturedObject* obj) {
			parent = obj;
		}

		bool getAnimationCompleted() const {
			return animationCompleted;
		}
};