#include "LevelParallax.h"



void LevelParallax::levelLoad() {
    SquareMeshVbo* square = new SquareMeshVbo();
    square->loadData();
    GameEngine::getInstance()->addMesh(SquareMeshVbo::MESH_NAME, square);

    SquareBorderMesh* border = new SquareBorderMesh();
    border->loadData();
    GameEngine::getInstance()->addMesh(SquareBorderMesh::MESH_NAME, border);
}

void LevelParallax::levelInit() {
    // Initialize the background
    //background = new TexturedObject();
    //background->setTexture("../Resource/Texture/TestBG.png");
    //background->getTransform().setScale(glm::vec3(8.0f, -6.0f, 0)); // Adjust the scale to fit the screen
    //background->getTransform().setPosition(glm::vec3(0.0f, 0.0f, -1.0f)); // Ensure it's behind other objects
    //objectsList.push_back(background);
    spaceShip = new ParallaxObject(10.0f, false);
    spaceShip->setTexture("../Resource/Texture/BGParallax/Spaceship.png");
    spaceShip->getTransform().setScale(glm::vec3(8.0f, -6.0f, 0));
    spaceShip->setPlane(0.3f, 300.0f);
    objectsList.push_back(spaceShip);

    midGround = new ParallaxObject(50.0f, false);
    midGround->setTexture("../Resource/Texture/BGParallax/Midground2.png");
    midGround->getTransform().setScale(glm::vec3(8.0f, -6.0f, 0));
    midGround->setPlane(0.3f, 300.0f);
    objectsList.push_back(midGround);

    // Initialize the player
    SimpleObject* obj = new SimpleObject();
    obj->setColor(0.0, 1.0, 0.0);
    objectsList.push_back(obj);
    player = obj;

    // Initialize other objects
    SimpleObject* obj2 = new SimpleObject();
    obj2->setColor(0.0, 0.0, 1.0);
    obj2->getTransform().setPosition(glm::vec3(2.0f, 2.0f, 0.0f));
    objectsList.push_back(obj2);

    SimpleObject* obj3 = new SimpleObject();
    obj3->setColor(0.0, 0.0, 1.0);
    obj3->getTransform().setPosition(glm::vec3(-2.0f, -2.0f, 0.0f));
    objectsList.push_back(obj3);

    player->addColliderComponent();
    player->getColliderComponent()->setWidth(10);
    player->setDrawCollider(true);
    
    GameEngine::getInstance()->getRenderer()->setClearColor(0.1, 0.1, 0.1);
}


void LevelParallax::levelUpdate() {
    glm::vec3 playerPosition = player->getTransform().getPosition(); 
    GameEngine::getInstance()->getRenderer()->updateCamera(playerPosition);
    spaceShip->updateParallax(GameEngine::getInstance()->getRenderer()->camPos(), playerPosition);
    midGround->updateParallax(GameEngine::getInstance()->getRenderer()->camPos(), playerPosition);
}

void LevelParallax::levelDraw() {
    GameEngine::getInstance()->render(objectsList);
}


void LevelParallax::levelFree() {
    for (DrawableObject* obj : objectsList) {
        delete obj;
    }
    objectsList.clear();
}
void LevelParallax::levelUnload() {
    GameEngine::getInstance()->clearMesh();
    //cout << "Unload Level" << endl;
}

void LevelParallax::handleKey(char key) {
    std::cout << "Key pressed: " << key << std::endl;
    switch (key) {
    case 'w': player->getTransform().translate(glm::vec3(0, 0.3, 0)); break;
    case 's': player->getTransform().translate(glm::vec3(0, -0.3, 0)); break;
    case 'a': player->getTransform().translate(glm::vec3(-0.3, 0, 0)); break;
    case 'd': player->getTransform().translate(glm::vec3(0.3, 0, 0)); break;
    case 'r': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART; break;
    case 'f': GameEngine::getInstance()->getRenderer()->toggleViewport();player->setColor(255, 255, 255); break;
    case 'e': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_MAINMENU; break;
    case 'z': GameEngine::getInstance()->getRenderer()->increaseZoomRatio(zoomRatio); break;
    case 'x': GameEngine::getInstance()->getRenderer()->decreaseZoomRatio(zoomRatio); break;
    }

    glm::vec3 playerPosition = player->getTransform().getPosition(); 
    GameEngine::getInstance()->getRenderer()->updateCamera(playerPosition);

}

void LevelParallax::handleMouse(int type, int x, int y) {
    // Convert screen coordinates to world coordinates for 2D
    float realX = static_cast<float>(x) / GameEngine::getInstance()->getWindowWidth() * 2 - 1;
    float realY = 1 - static_cast<float>(y) / GameEngine::getInstance()->getWindowHeight() * 2;

    std::cout << "X : " << realX << " Y : " << realY << std::endl;

    // Set player position based on mouse click
    player->getTransform().setPosition(glm::vec3(realX, realY, 0));
}

void LevelParallax::handleAnalogStick(int type, float amount) {

    if (type == 0) {//x axis
        player->getTransform().translate(glm::vec3(0.3 * amount, 0, 0));
    }
    else if (type == 1) {//y axis
        player->getTransform().translate(glm::vec3(0, -0.3 * amount, 0));
    }
}