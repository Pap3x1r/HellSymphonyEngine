
#include "TexturedObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"


TexturedObject::TexturedObject() {}

TexturedObject::TexturedObject(string name) {
	DrawableObject::setName(name);
}


TexturedObject::~TexturedObject() {
	if (animation != nullptr) {
		delete animation;
	}
}

void TexturedObject::setTexture(string path) {
	if (texture != 0) {
		glDeleteTextures(1, &texture);
	}
	texture = GameEngine::getInstance()->getRenderer()->LoadTexture(path);

	if (animation != nullptr) {
		animation->setTexture(texture);
	}
}

void TexturedObject::setTexture(string path, int row, int col, int startFrame) {
	if (texture != 0) {
		glDeleteTextures(1, &texture);
	}
	texture = GameEngine::getInstance()->getRenderer()->LoadTexture(path);

	if (animation != nullptr) {
		animation->setStartingFrame(startFrame);
		animation->setDimension(col, row); // switch because row and col is switched.
		animation->setTexture(texture);
	}
}

void TexturedObject::setTexture(string path, int row, int col, int startFrame, bool loop) {
	if (texture != 0) {
		glDeleteTextures(1, &texture);
	}
	texture = GameEngine::getInstance()->getRenderer()->LoadTexture(path);

	if (animation != nullptr) {
		animation->setStartingFrame(startFrame);
		animation->setDimension(col, row); // switch because row and col is switched.
		animation->setTexture(texture);
		animation->setLoop(loop);
	}
}

void TexturedObject::render(glm::mat4 globalModelTransform) {
	if (animation != nullptr) {
		animation->render(globalModelTransform, this->transform);
		return;
	}

	SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::getInstance()->getRenderer()->getMesh(SquareMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::getInstance()->getRenderer()->getModelMatrixAttrId();
	GLuint renderModeId = GameEngine::getInstance()->getRenderer()->getModeUniformId();
	/*GLuint offsetXId = GameEngine::getInstance()->getRenderer()->getOffsetXUniformId();
	GLuint offsetYId = GameEngine::getInstance()->getRenderer()->getOffsetYUniformId();*/
	GLuint scaleXId = GameEngine::getInstance()->getRenderer()->getScaleXUniformId();
	GLuint scaleYId = GameEngine::getInstance()->getRenderer()->getScaleYUniformId();

	if (modelMatixId == -1) {
		cout << "Error: Can't perform transformation " << endl;
		return;
	}
	if (renderModeId == -1) {
		cout << "Error: Can't set renderMode in TexturedObject " << endl;
		return;
	}
	/*if (offsetXId == -1) {
		cout << "Error: Can't set offsetXId in TexturedObject " << endl;
		return;
	}*/

	vector <glm::mat4> matrixStack;

	glm::mat4 currentMatrix = this->getTransformMat4();

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform1i(renderModeId, 1);
		glBindTexture(GL_TEXTURE_2D, texture);
		squareMesh->render();

	}
}

void TexturedObject::initAnimation(int rowCount, int colCount) {
	animation = new Animation(texture);
	animation->setDimension(rowCount, colCount);
}

Animation* TexturedObject::getAnimationComponent() {
	return animation;
}

bool TexturedObject::isAnimated() {
	return animation != nullptr;
}

//void TexturedObject::addAnimation(int rowCount, int colCount) {
//	animated = true;
//	this->rowCount = rowCount;
//	this->colCount = colCount;
//}
//
//void TexturedObject::setFrame(float row, float column) {
//	offsetX = (1.0f / this->rowCount) * row;
//	offsetY = (1.0f / this->colCount) * column;
//}