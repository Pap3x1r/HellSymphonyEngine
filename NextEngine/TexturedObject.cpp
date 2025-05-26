
#include "TexturedObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "Player.h"

class Player;

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
	/*if (texture != 0) {
		glDeleteTextures(1, &texture);
	}*/

	GLRenderer* renderer = GameEngine::getInstance()->getRenderer();

	texture = renderer->findTexture(path);

	if (animation != nullptr) {
		animation->setTexture(texture);
	}
}

void TexturedObject::setTexture(string path, int row, int col, int startFrame) {
	/*if (texture != 0) {
		glDeleteTextures(1, &texture);
	}*/
	//texture = GameEngine::getInstance()->getRenderer()->LoadTexture(path);

	GLRenderer* renderer = GameEngine::getInstance()->getRenderer();

	texture = renderer->findTexture(path);

	if (animation != nullptr) {
		animation->setStartingFrame(startFrame);
		animation->setDimension(col, row); // switch because row and col is switched.
		animation->setTexture(texture);
	}
}

void TexturedObject::setTexture(string path, int row, int col, int startFrame, bool loop) {
	/*if (texture != 0) {
		glDeleteTextures(1, &texture);
	}*/
	//texture = GameEngine::getInstance()->getRenderer()->LoadTexture(path);

	GLRenderer* renderer = GameEngine::getInstance()->getRenderer();

	texture = renderer->findTexture(path);

	if (animation != nullptr) {
		animation->setStartingFrame(startFrame);
		animation->setDimension(col, row); // switch because row and col is switched.
		animation->setTexture(texture);
		animation->setLoop(loop);
	}
}

void TexturedObject::render(glm::mat4 globalModelTransform) {
	if (hitEffectStrength > 0.0f) {
		hitEffectStrength -= 5.0f * GameEngine::getInstance()->getTime()->getDeltaTime();
		if (hitEffectStrength < 0.0f) {
			hitEffectStrength = 0.0f;
		}
	}

	if (animation != nullptr) {
		animation->render(globalModelTransform, this->transform);
		return;
	}

	SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::getInstance()->getRenderer()->getMesh(SquareMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::getInstance()->getRenderer()->getModelMatrixAttrId();
	GLuint renderModeId = GameEngine::getInstance()->getRenderer()->getModeUniformId();
	GLuint colorUniformId = GameEngine::getInstance()->getRenderer()->getColorUniformId();
	/*GLuint offsetXId = GameEngine::getInstance()->getRenderer()->getOffsetXUniformId();
	GLuint offsetYId = GameEngine::getInstance()->getRenderer()->getOffsetYUniformId();*/
	GLuint scaleXId = GameEngine::getInstance()->getRenderer()->getScaleXUniformId();
	GLuint scaleYId = GameEngine::getInstance()->getRenderer()->getScaleYUniformId();

	GLuint hitEffectStrengthId = GameEngine::getInstance()->getRenderer()->getHitEffectUniformId();
	GLuint alphaOverrideId = GameEngine::getInstance()->getRenderer()->getAlphaOverrideUniformId();
	GLuint colorOverrideId = GameEngine::getInstance()->getRenderer()->getColorOverrideUniformId();


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

	/*if (hitEffectStrength > 0.0f) {
		hitEffectStrength -= 0.2f * GameEngine::getInstance()->getTime()->getDeltaTime();
	}*/

	glUniform1f(alphaOverrideId, alpha);
	glUniform1f(hitEffectStrengthId, hitEffectStrength);
	//glUniform4f(colorUniformId, 1.0f, 1.0f, 1.0f, 1.0f);
	glUniform4f(colorOverrideId, this->newColor.x, this->newColor.y, this->newColor.z, this->newColor.a);

	vector <glm::mat4> matrixStack;	

	glm::mat4 currentMatrix = this->getTransformMat4();
	currentMatrix = glm::translate(currentMatrix, spriteOffset);

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		if (isAnimated()) {
			glUniform1i(renderModeId, 2);
		}
		else {
			glUniform1i(renderModeId, 1);
		}

		glBindTexture(GL_TEXTURE_2D, texture);
		squareMesh->render();

	}
}

void TexturedObject::initAnimation(int rowCount, int colCount) {
	animation = new Animation(texture);
	animation->setDimension(rowCount, colCount);
	animation->setParent(this);
}

Animation* TexturedObject::getAnimationComponent() {
	return animation;
}

bool TexturedObject::isAnimated() {
	return animation != nullptr;
}

void TexturedObject::setSpriteOffset(glm::vec3 vector3) {
	spriteOffset = vector3;
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

void TexturedObject::setHitEffectStrength(float value) {
	hitEffectStrength = value;
}

float TexturedObject::getHitEffectStrength() {
	return hitEffectStrength;
}

void TexturedObject::setAlpha(float value) {
	alpha = value;
}

float TexturedObject::getAlpha() const {
	return alpha;
}

void TexturedObject::setNewColor(glm::vec4 v4) {
	newColor = v4;
}

glm::vec4 TexturedObject::getNewColor() const {
	return newColor;
}