#include "CollisionHandler.h"
#include "LevelMapEditorTest.h"
#include "MapLoader.h"

static void loadMap(MapLoader& loader, int i, vector<DrawableObject*>& objList, DrawableObject*& player);
static void appendMap(MapLoader& loader, int i, vector<DrawableObject*>& objList, DrawableObject*& player);
static ostream& operator<<(ostream& out, glm::vec3 pos);

void LevelMapEditorTest::levelLoad() {
    SquareMeshVbo* square = new SquareMeshVbo();
    square->loadData();
    GameEngine::getInstance()->addMesh(SquareMeshVbo::MESH_NAME, square);

    SquareBorderMesh* border = new SquareBorderMesh();
    border->loadData();
    GameEngine::getInstance()->addMesh(SquareBorderMesh::MESH_NAME, border);
}

void LevelMapEditorTest::levelInit() {
    mapLoader.readData("map3.txt");
    mapLoader.loadDataToScene(objectsList, player);
    
    background = new TexturedObject("BG");
    background->setTexture("../Resource/Texture/BGParallax/Mountain1920.png");
    background->getTransform().setScale(glm::vec3(10.0f, 10.0f, 0)); // Adjust the scale to fit the screen
    background->getTransform().setPosition(glm::vec3(0.0f, 0.0f, -1.0f)); // Ensure it's behind other objects
    objectsList.emplace(objectsList.begin(), background);

    if (player != nullptr) {
        cout << "player not null" << endl;
    }

    cout << "player pos: " << player->getTransform().getPosition() << endl;
}

void LevelMapEditorTest::levelUpdate() {
    for (DrawableObject* obj : objectsList) {
        obj->update();
    }
    handleObjectCollision(objectsList);
    glm::vec3 playerPosition = player->getTransform().getPosition();
    GameEngine::getInstance()->getRenderer()->updateCamera(playerPosition);
}

void LevelMapEditorTest::levelDraw() {
    GameEngine::getInstance()->render(objectsList);
}

void LevelMapEditorTest::levelFree() {
    for (DrawableObject* obj : objectsList) {
        delete obj;
    }
    objectsList.clear();
}

void LevelMapEditorTest::levelUnload() {
    GameEngine::getInstance()->clearMesh();
    //cout << "Unload Level" << endl;
}

void LevelMapEditorTest::handleKey(char key) {
    float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
    //cout << dt << endl;
    switch (key) {
    case ' ': player->getPhysicsComponent()->setVelocity(glm::vec2(0, 25)); break;
    case 'w': player->getTransform().translate(glm::vec3(0, 5, 0) * dt); break;
    case 's': player->getTransform().translate(glm::vec3(0, -5, 0) * dt); break;
    case 'a': player->getTransform().translate(glm::vec3(-5, 0, 0) * dt); break;
    case 'd': player->getTransform().translate(glm::vec3(5, 0, 0) * dt); break;
    case 'f': GameEngine::getInstance()->getRenderer()->toggleViewport(); break;
    case 'c': player->getColliderComponent()->setTrigger(!player->getColliderComponent()->isTrigger()); break;
    case 'g': player->getPhysicsComponent()->setEnableGravity(!player->getPhysicsComponent()->isGravityEnable()); break;
    case 'q': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_QUIT; ; break;
    case 'r': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART; ; break;
    case 'e': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_MAINMENU; ; break;
    case 'z': GameEngine::getInstance()->getRenderer()->increaseZoomRatio(0.1f); break;
    case 'x': GameEngine::getInstance()->getRenderer()->decreaseZoomRatio(0.1f); break;
    /*case '1': loadMap(mapLoader, 1, objectsList, player); break;
    case '2': loadMap(mapLoader, 2, objectsList, player); break;
    case '3': loadMap(mapLoader, 3, objectsList, player); break;
    case '4': appendMap(mapLoader, 5, objectsList, player); break;*/
    }
}

void LevelMapEditorTest::handleMouse(int type, int x, int y) {
    /// Will be implemented in inherited level when used ///
}

void LevelMapEditorTest::handleAnalogStick(int type, float amount) {
    
    if (type == 0) { // x axis
        player->getTransform().translate(glm::vec3(0.3 * amount, 0, 0));
    }
    else if (type == 1) { // y axis
        player->getTransform().translate(glm::vec3(0, -0.3 * amount, 0));
    }
    
}

//static void loadMap(MapLoader& loader, int i, list<DrawableObject*>& objList, DrawableObject*& player) {
//    string name = "map" + to_string(i) + ".txt";
//    loader.readData(name);
//    loader.loadDataToScene(objList, player);
//
//    if (player != nullptr) {
//        cout << "player not null" << endl;
//    }
//}
//
//static void appendMap(MapLoader& loader, int i, list<DrawableObject*>& objList, DrawableObject*& player) {
//    string name = "map" + to_string(i) + ".txt";
//    loader.readData(name);
//    loader.appendDataToScene(objList, player);
//
//    if (player != nullptr) {
//        cout << "player not null" << endl;
//    }
//}

static ostream& operator<<(ostream& out, glm::vec3 pos) {
    out << pos.x << "," << pos.y;
    return out;
}