#pragma once
#include "..\TexturedObject.h"

class AnimatedObject : public TexturedObject {
private:
	int frameHeight;
	int frameWidth;
	int row;
	int column;
public:
	AnimatedObject(int frameHeight, int frameWidth, int row, int column);
	void setFrame(int row, int column);
};