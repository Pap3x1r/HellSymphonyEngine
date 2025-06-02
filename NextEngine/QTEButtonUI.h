#pragma once
#include "TexturedObject.h"
#include <iostream>


using namespace std;

class QTEButtonUI : public TexturedObject {
private:
	int target;

public:
	QTEButtonUI();

	QTEButtonUI(int target);

	void update(float dt);

	void expire();

	void changeTextureDefault(int target);
	void changeTextureFailure(int target);
	void changeTextureSuccess(int target);
};