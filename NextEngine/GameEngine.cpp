#include "GameEngine.h"
#include "Player.h"
#include <fstream>

GameEngine* GameEngine::instance = nullptr;

GameEngine::GameEngine() {
	renderer = nullptr;
}

GameEngine * GameEngine::getInstance() {
	if (instance == nullptr) {
		instance = new GameEngine();
	}
	return instance;
}

GLRenderer * GameEngine::getRenderer() {
	return this->renderer;
}

GameStateController* GameEngine::getStateController() {
	return this->stateController;
}

Time* GameEngine::getTime() {
	return this->time;
}

AudioEngine* GameEngine::getAudio() {
	return this->audio;
}

InputManager* GameEngine::getInputHandler() {
	return inputHandler;
}
void GameEngine::init(int width, int height) {
	winWidth = width;
	winHeight = height;

	renderer = new GLRenderer(width, height);
	renderer->initGL("../Resource/Shader/vertext.shd", "../Resource/Shader/fragment.shd");
	setDrawArea(-8, 8, -4.5, 4.5);
	setBackgroundColor(95.0f / 255, 110.0f / 255, 133.0f / 255);

	stateController = new GameStateController();
	stateController->init(GameState::GS_MAINMENU);

	time = new Time();
	inputHandler = new InputManager();  
	audio = new AudioEngine();
	TTF_Init();
}

void GameEngine::render(list<DrawableObject*> renderObjects) {
	this->getRenderer()->render(renderObjects);
}

void GameEngine::setDrawArea(float left, float right, float bottom, float top) {
	renderer->setOrthoProjection(left, right, bottom, top);
}

//void GameEngine::setBackgroundColor(float r, float g, float b) {
//	renderer->setClearColor(1.0f, 1.0f, 200.0f / 255);
//}

void GameEngine::setBackgroundColor(float r, float g, float b) {
	renderer->setClearColor(r, g, b);
}

void GameEngine::addMesh(string name, MeshVbo* mesh) {
	renderer->addMesh(name, mesh);
}

void GameEngine::clearMesh() {
	renderer->clearMesh();
}

int GameEngine::getWindowWidth() {
	return winWidth;
}

int GameEngine::getWindowHeight() {
	return winHeight;
}

void GameEngine::setWindowWidth(int w) {
	winWidth = w;
}
void GameEngine::setWindowHeight(int h) {
	winHeight = h;
}

void GameEngine::freezeGameForSecond(float duration) {
	while (duration > 0.0f) {
		time->updateTick(SDL_GetTicks());
		duration -= time->getDeltaTimeRealTime();
	}
}

void GameEngine::savePlayerData(const Player* player, const std::string& filename) {
	ofstream outFile(filename);
	if (!outFile) {
		cerr << "Error opening file for writing!" << endl;
		return;
	}

	if (player) {
		// Save player data with descriptions and line breaks
		outFile << "Player Health: " << player->getHealth()->getCurrentHP() << endl;
		outFile << "Player Wither Health: " << player->getHealth()->getWitherHP() << endl;
		outFile << "Player Lives: " << player->getLives() << endl;

		cout << "Saved Successful." << endl;
	}
	else {
		cerr << "Player is missing, save file does not write." << endl;
	}

	outFile.close();
}

Player* GameEngine::loadPlayerData(const string& filepath) {
	ifstream inFile(filepath);
	if (!inFile) {
		cerr << "Error opening file for reading! Using default values.\n";
		return new Player(100, 0, 3);
	}

	string line;

	float hp = 100.0f;
	float wither = 0.0f;
	int lives = 3;

	auto extractValue = [&inFile](const string& label, auto& value) {
		string line;
		if (getline(inFile, line)) {
			size_t pos = line.find(label);
			if (pos != string::npos) {
				try {
					value = stof(line.substr(pos + label.length()));  // Convert to float or int
				}
				catch (...) {
					cerr << "Error reading " << label << endl;
				}
			}
		}
		};

	extractValue("Player Health:", hp);
	extractValue("Player Wither Health:", wither);
	extractValue("Player Lives:", lives);


	inFile.close();
	cout << "Data loaded from text file.\n";

	cout << "Player health: " << hp << endl;
	cout << "Player wither health: " << wither << endl;
	cout << "Player lives: " << lives << endl;

	Player* player_ = new Player(hp, wither, lives);
	/*player_->getHealth()->setHP(hp);
	player_->getHealth()->setWitherHP(wither);
	player_->setLives(lives);*/

	return player_;
}