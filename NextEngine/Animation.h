#pragma once

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Transform.h"
#include <string>
#include <unordered_map>

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

		// Animation
		unsigned int& texture;
		int rowCount;
		int colCount;
		float offsetX;
		float offsetY;

	public:
		//Animator
		void addState(string name, int row, int frameCount);
		void setState(string name);
		void updateCurrentState();

		//Animation
		Animation(unsigned int& texture);
		void render(glm::mat4 globalModelTransform, Transform& transform);
		void setFrame(int row, int column);
		void setDimension(int row, int col);
};