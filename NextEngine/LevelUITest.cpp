#include "LevelUITest.h"
#include "CollisionHandler.h"

int playerHealth = 0;

void LevelUITest::levelLoad() {
    SquareMeshVbo* square = new SquareMeshVbo();
    square->loadData();
    GameEngine::getInstance()->addMesh(SquareMeshVbo::MESH_NAME, square);

    SquareBorderMesh* border = new SquareBorderMesh();
    border->loadData();
    GameEngine::getInstance()->addMesh(SquareBorderMesh::MESH_NAME, border);
}

void LevelUITest::levelInit() {
    // Initialize the background
    background = new TexturedObject();
    background->setTexture("../Resource/Texture/TestBG.png");
    background->getTransform().setScale(glm::vec3(8.0f, -6.0f, 0)); // Adjust the scale to fit the screen
    background->getTransform().setPosition(glm::vec3(0.0f, 0.0f, -1.0f)); // Ensure it's behind other objects
    objectsList.push_back(background);


    // Initialize the player
    player = new PlayerObject("player", 100, 10);
    player->setTexture("../Resource/Texture/Zinzin.png");
    player->getTransform().setPosition(glm::vec3(0.0f, 2.0f, 0.0f));
    player->addColliderComponent();
    player->addPhysicsComponent();
    player->setDrawCollider(true);
    objectsList.push_back(player);

    // Initialize Enemy
    EnemyObject* enemy = new EnemyObject(80, 8);
    enemy->setTexture("../Resource/Texture/enemyTexture.png");
    enemy->getTransform().setPosition(glm::vec3(3.0f, 2.0f, 0.0f));
    enemy->addColliderComponent();
    enemy->setDrawCollider(true);
    objectsList.push_back(enemy);

    // Initialize the player's health bar
    SimpleObject* healthBar = new SimpleObject();
    healthBar->setColor(1.0f, 0.0f, 0.0f);  // Red color for health bar
    healthBar->getTransform().setScale(glm::vec3(2.0f, 0.2f, 0.0f));  // Initial size of the health bar
    healthBar->getTransform().setPosition(glm::vec3(player->getTransform().getPosition().x,
        player->getTransform().getPosition().y + 0.5f, 0.0f));  // Position above the player
    objectsList.push_back(healthBar);

    // Initialize other objects
    /*SimpleObject* obj2 = new SimpleObject();
    obj2->setColor(0.0, 0.0, 1.0);
    obj2->getTransform().setPosition(glm::vec3(2.0f, 2.0f, 0.0f));
    objectsList.push_back(obj2);

    SimpleObject* obj3 = new SimpleObject();
    obj3->setColor(0.0, 0.0, 1.0);
    obj3->getTransform().setPosition(glm::vec3(-2.0f, -2.0f, 0.0f));
    objectsList.push_back(obj3);*/

    player->addColliderComponent();
    player->getColliderComponent()->setWidth(10);
    //player->getColliderComponent()->setOffset(glm::vec3(0.0f, -5.0f, 0.0f));
    player->setDrawCollider(true);

    //GameEngine::getInstance()->getRenderer()->setClearColor(0.1, 0.1, 0.1);
    //quitButton = new Button("QuitButton", "Quit");
    //quitButton->getTransform().setPosition(glm::vec3(5.0f, 3.0f, 0.0f)); // Position
    //quitButton->getTransform().setScale(glm::vec3(1.0f, 0.5f, 0.0f));   // Size

    //quitButton->setOnClickCallback([]() {
    //    std::cout << "Quit Button Pressed! Quitting game..." << std::endl;
    //    GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_QUIT;
    //    });

    //objectsList.push_back(quitButton);

    player->setHP(100);
}


void LevelUITest::levelUpdate() {
    glm::vec3 playerPosition = player->getTransform().getPosition();
    GameEngine::getInstance()->getRenderer()->updateCamera(playerPosition);


    //// Update health bar based on player's current health
    //float healthPercentage = static_cast<float>(player->getHP()) / 100;
    //float healthBarWidth = healthPercentage * 2.0f;
    //objectsList[3]->getTransform().setScale(glm::vec3(healthBarWidth, 0.2f, 0.0f));
    //float offsetX = (2.0f - healthBarWidth) / 2.0f;
    //objectsList[3]->getTransform().setPosition(glm::vec3(playerPosition.x - offsetX, playerPosition.y + 0.5f, 0.0f));

    for (DrawableObject* obj : objectsList) {
        EnemyObject* enemy = dynamic_cast<EnemyObject*>(obj);
        if (enemy) {
            if (checkCollision(player->getColliderComponent(), player->getTransform(),
                enemy->getColliderComponent(), enemy->getTransform())) {
                player->takeDamage(1);  // Reduce player health by 1 on collision
                std::cout << "Player collided with enemy! Health: " << player->getHP() << std::endl;
            }
        }
    }
}

void LevelUITest::levelDraw() {
    GameEngine::getInstance()->render(objectsList);
}

void LevelUITest::levelFree() {
    for (DrawableObject* obj : objectsList) {
        delete obj;
    }
    objectsList.clear();
}

void LevelUITest::levelUnload() {
    GameEngine::getInstance()->clearMesh();
    //cout << "Unload Level" << endl;
}

void LevelUITest::handleKey(char key) {
    std::cout << "Key pressed: " << key << std::endl;
    switch (key) {
    case 'w': player->getTransform().translate(glm::vec3(0, 0.3, 0)); break;
    case 's': player->getTransform().translate(glm::vec3(0, -0.3, 0)); break;
    case 'a': player->getTransform().translate(glm::vec3(-0.3, 0, 0)); break;
    case 'd': player->getTransform().translate(glm::vec3(0.3, 0, 0)); break;
    case 'r': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART; break;
    case 'f': GameEngine::getInstance()->getRenderer()->toggleViewport(); break;
    case 'e': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_MAINMENU; break;
    case 'z': GameEngine::getInstance()->getRenderer()->increaseZoomRatio(zoomRatio); break;
    case 'x': GameEngine::getInstance()->getRenderer()->decreaseZoomRatio(zoomRatio); break;
    case 'h': player->takeDamage(1); break;  
    case 'j': player->setHP(100); break;  
    }

    glm::vec3 playerPosition = player->getTransform().getPosition();
    GameEngine::getInstance()->getRenderer()->updateCamera(playerPosition);
}

void LevelUITest::handleMouse(int type, int x, int y) {
    // Convert screen coordinates to world coordinates for 2D
    float realX = static_cast<float>(x) / GameEngine::getInstance()->getWindowWidth() * 2 - 1;
    float realY = 1 - static_cast<float>(y) / GameEngine::getInstance()->getWindowHeight() * 2;

    std::cout << "X : " << realX << " Y : " << realY << std::endl;

    // Set player position based on mouse click
    //player->getTransform().setPosition(glm::vec3(realX, realY, 0));

    if (checkCollisionPoint(player->getColliderComponent(), player->getTransform(), glm::vec2(realX, realY))) {
        cout << "detected" << endl;
    }

    /*if (checkCollisionPoint(quitButton->getColliderComponent(), quitButton->getTransform(), glm::vec2(realX, realY))) {
        quitButton->setState(Button::ButtonState::PRESSED);
    }*/

}

void LevelUITest::handleAnalogStick(int type, float amount) {

    if (type == 0) { // x axis
        player->getTransform().translate(glm::vec3(0.3 * amount, 0, 0));
    }
    else if (type == 1) { // y axis
        player->getTransform().translate(glm::vec3(0, -0.3 * amount, 0));
    }
}
