#include "Animation.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "TexturedObject.h"

using namespace std;

Animation::Animation(unsigned int& texture): texture(texture) {
	offsetX = 0;
	offsetY = 0;
	currentFrame = 0;

	rowCount = 1;
	colCount = 1;
}

void Animation::render(glm::mat4 globalModelTransform, Transform& transform) {
	SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::getInstance()->getRenderer()->getMesh(SquareMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::getInstance()->getRenderer()->getModelMatrixAttrId();
	GLuint renderModeId = GameEngine::getInstance()->getRenderer()->getModeUniformId();
	GLuint offsetXId = GameEngine::getInstance()->getRenderer()->getOffsetXUniformId();
	GLuint offsetYId = GameEngine::getInstance()->getRenderer()->getOffsetYUniformId();
	GLuint scaleXId = GameEngine::getInstance()->getRenderer()->getScaleXUniformId();
	GLuint scaleYId = GameEngine::getInstance()->getRenderer()->getScaleYUniformId();

	GLuint hitEffectStrengthId = GameEngine::getInstance()->getRenderer()->getHitEffectUniformId();
	GLuint colorOverrideId = GameEngine::getInstance()->getRenderer()->getColorOverrideUniformId();
	GLuint alphaOverrideId = GameEngine::getInstance()->getRenderer()->getAlphaOverrideUniformId();

	if (modelMatixId == -1) {
		cout << "Error: Can't perform transformation " << endl;
		return;
	}
	if (renderModeId == -1) {
		cout << "Error: Can't set renderMode in TexturedObject " << endl;
		return;
	}
	if (offsetXId == -1) {
		cout << "Error: Can't set offsetXId in TexturedObject " << endl;
		return;
	}

	glUniform1f(hitEffectStrengthId, parent->getHitEffectStrength());
	glUniform1f(alphaOverrideId, parent->getAlpha());
	glUniform4f(colorOverrideId, parent->getNewColor().x, parent->getNewColor().y, parent->getNewColor().z, parent->getNewColor().a);

	vector <glm::mat4> matrixStack;

	glm::mat4 currentMatrix = transform.getTransformMat4();
	currentMatrix = glm::translate(currentMatrix, animOffset);

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform1i(renderModeId, 2);
		glUniform1f(offsetXId, offsetX);
		glUniform1f(offsetYId, offsetY);
		glUniform1f(scaleXId, 1.0f / this->rowCount); // bigger scale zoom out, small scale zoom in
		glUniform1f(scaleYId, 1.0f / this->colCount);
		glBindTexture(GL_TEXTURE_2D, texture);
		squareMesh->render();

	}
}

void Animation::setDimension(int row, int col) {
	this->rowCount = row;
	this->colCount = col;
}

void Animation::setFrame(int row, int column) {
	offsetX = (1.0f / this->rowCount) * column; // MA BRAIN SWITCH ROW AND COLUMN SO I SWITCH EM HERE
	offsetY = (1.0f / this->colCount) * row;
}

void Animation::addState(string name, int row, int frameCount) {
	if (states.find(name) != states.end()) {
		cout << "Error state: '" << name << "' already exists" << endl;
		return;
	}
	State newState(name, row, frameCount);
	states[name] = newState;
}

void Animation::setState(string name) {
	State nextState = states[name];
	/*if (nextState.name != currentState.name) {
		currentFrame = startingFrame;
		animationTimer = 0.0f;
		setFrame(currentState.row, currentFrame);
	}*/
	currentFrame = startingFrame;
	animationTimer = 0.0f;
	animationCompleted = false;
	setFrame(currentState.row, currentFrame);
	currentState = states[name];
}

void Animation::updateCurrentState(float dt) {
	const float frameDuration = 1.0f / 12.0f; //Based on animation 12 frames per second.

	animationTimer += dt;

	if (animationTimer >= frameDuration) {
		animationTimer -= frameDuration;
		currentFrame++;

		if (currentFrame >= currentState.frameCount) {
			if (loop) {
				currentFrame = startingFrame;
			}
			else {
				currentFrame = currentState.frameCount - 1;
				animationCompleted = true;
			}
		}

		setFrame(currentState.row, currentFrame);
	}
}

void Animation::setTexture(unsigned int newTexture) {
	texture = newTexture;
}

void Animation::setStartingFrame(int frame) {
	startingFrame = frame;
}

void Animation::setAnimOffset(glm::vec3 vector3) {
	animOffset = vector3;
}