
#include "CombineObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "TriangleMeshVbo.h"


CombineObject::CombineObject() {
	color = glm::vec3(0.0, 0.0, 0.0);
}

CombineObject::CombineObject(string name) {
	color = glm::vec3(0.0, 0.0, 0.0);
	DrawableObject::setName(name);
}

CombineObject::~CombineObject() {}

void CombineObject::setColor(float r, float g, float b) {
	color = glm::vec3(r, g, b);
}

void CombineObject::setColor2(float r, float g, float b) {
	color2 = glm::vec3(r, g, b);
}

void CombineObject::render(glm::mat4 globalModelTransform) {
	SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::getInstance()->getRenderer()->getMesh(SquareMeshVbo::MESH_NAME));
	TriangleMeshVbo* triangleMesh = dynamic_cast<TriangleMeshVbo*> (GameEngine::getInstance()->getRenderer()->getMesh(TriangleMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::getInstance()->getRenderer()->getModelMatrixAttrId();
	GLuint colorId = GameEngine::getInstance()->getRenderer()->getColorUniformId();


	if (modelMatixId == -1) {
		cout << "Error: Can't perform transformation " << endl;
		return;
	}
	if (colorId == -1) {
		cout << "Error: Can't set color " << endl;
		return;
	}
	vector <glm::mat4> matrixStack;

	glm::mat4 currentMatrix = this->getTransformMat4();

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform3f(colorId, color.x, color.y, color.z);
		squareMesh->render();

	}

	if (triangleMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform3f(colorId, color2.x, color2.y, color2.z);
		triangleMesh->render();

	}
}

