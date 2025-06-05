#include "GameEngine.h"
#include "Player.h"
#include <fstream>
#include <filesystem>

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

//AudioEngine* GameEngine::getAudio() {
//	return this->audio;
//}

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
	//audio = new AudioEngine();
	//audio->init("../Resource/Audio/SoundEffect", "../Resource/Audio/Music");
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
	ofstream outFile(filename, ios::out | ios::trunc);  // Ensures file is created or overwritten
	if (!outFile) {
		cerr << "Error opening file for writing!" << endl;
		return;
	}

	if (player) {
		outFile << "Player Health: " << player->getHealth()->getCurrentHP() << endl;
		outFile << "Player Wither Health: " << player->getHealth()->getWitherHP() << endl;
		outFile << "Player Lives: " << player->getLives() << endl;
		cout << "Saved Successfully." << endl;
	}
	else {
		cerr << "Player is missing, save file does not write." << endl;
	}

	outFile.close();
}

void GameEngine::savePlayerData(int currentHP, int witherHP, int lives, const std::string& filename) {
	std::ofstream outFile(filename, std::ios::out | std::ios::trunc);  // Overwrites file

	if (!outFile) {
		std::cerr << "Error opening file for writing!" << std::endl;
		return;
	}

	outFile << "Player Health: " << currentHP << std::endl;
	outFile << "Player Wither Health: " << witherHP << std::endl;
	outFile << "Player Lives: " << lives << std::endl;

	std::cout << "Saved Successfully." << std::endl;

	outFile.close();
}

Player* GameEngine::loadPlayerData(const std::string& filepath) {
	float hp = 100.0f;
	float wither = 0.0f;
	int lives = 3;

	ifstream inFile(filepath);
	if (!inFile) {
		cerr << "Player data file not found. Creating new file with default values.\n";

		ofstream outFile(filepath);
		if (outFile) {
			outFile << "Player Health: " << hp << endl;
			outFile << "Player Wither Health: " << wither << endl;
			outFile << "Player Lives: " << lives << endl;
			outFile.close();
		}
		else {
			cerr << "Failed to create player data file.\n";
		}

		return new Player(hp, wither, lives);
	}

	// Parse all lines once
	std::string line;
	while (std::getline(inFile, line)) {
		if (line.find("Player Health:") != std::string::npos) {
			try {
				hp = std::stof(line.substr(line.find(":") + 1));
			}
			catch (...) {
				cerr << "Failed to parse Player Health\n";
			}
		}
		else if (line.find("Player Wither Health:") != std::string::npos) {
			try {
				wither = std::stof(line.substr(line.find(":") + 1));
			}
			catch (...) {
				cerr << "Failed to parse Player Wither Health\n";
			}
		}
		else if (line.find("Player Lives:") != std::string::npos) {
			try {
				lives = std::stoi(line.substr(line.find(":") + 1));
			}
			catch (...) {
				cerr << "Failed to parse Player Lives\n";
			}
		}
	}

	inFile.close();

	cout << "Player data loaded from file:\n";
	cout << "Health: " << hp << ", Wither: " << wither << ", Lives: " << lives << endl;

	return new Player(hp, wither, lives);
}

void GameEngine::saveGameState(GameState state, const std::string& filename) {
	ofstream outFile(filename, ios::out | ios::trunc);
	if (!outFile) {
		cerr << "Error opening game state file for writing!" << endl;
		return;
	}

	outFile << "Game State: " << static_cast<int>(state) << endl;
	cout << "Game state saved successfully." << endl;

	outFile.close();
}

GameState GameEngine::loadGameState(const std::string& filename, bool newGame) {
	ifstream inFile(filename);
	if (!inFile || newGame) {
		if (newGame) {
			if (inFile.is_open()) inFile.close();
			cout << "Creating new game state file" << endl;

			string playerDataFile = "../Resource/Saves/PlayerData/playerData.txt";
			if (filesystem::exists(playerDataFile)) {
				filesystem::remove(playerDataFile);
				cout << "Deleted " << playerDataFile << "\n";
			}
			else {
				cout << "No player data file to delete.\n";
			}
		}
		else {
			cerr << "Game state file not found. Creating new file with default state (GS_MAINMENU)." << endl;
		}

		// Create a new file with default game state
		ofstream outFile(filename, ios::out | ios::trunc);
		if (outFile) {
			outFile << "Game State: " << static_cast<int>(GameState::GS_LIMBO1) << endl;
			outFile.close();
		}
		else {
			cerr << "Failed to create game state file." << endl;
		}

		return GameState::GS_LIMBO1;
	}

	std::string line;
	if (std::getline(inFile, line)) {
		size_t pos = line.find("Game State:");
		if (pos != std::string::npos) {
			try {
				int stateInt = stoi(line.substr(pos + std::string("Game State:").length()));
				inFile.close();
				return static_cast<GameState>(stateInt);
			}
			catch (...) {
				cerr << "Error parsing game state. Using GS_MAINMENU." << endl;
			}
		}
	}

	inFile.close();
	return GameState::GS_LIMBO1;
}

void GameEngine::savePlayerWeaponType(Player* player, const std::string& filepath) {
	if (!player) return;

	std::ofstream outFile(filepath, std::ios::out | std::ios::trunc);
	if (!outFile) {
		std::cerr << "Failed to open weapon type save file.\n";
		return;
	}

	WeaponType currentWeapon = player->getWeaponType();
	outFile << "Weapon Type: " << static_cast<int>(currentWeapon) << std::endl;

	std::cout << "Weapon type saved: " << static_cast<int>(currentWeapon) << std::endl;
	outFile.close();
}

WeaponType GameEngine::loadPlayerWeaponType(const std::string& filename, bool newGame) {
	ifstream inFile(filename);

	if (!inFile || newGame) {
		if (newGame) {
			if (inFile.is_open()) inFile.close();
			std::cout << "Creating new weapon type save file\n";

			// Delete existing file if it exists
			if (filesystem::exists(filename)) {
				filesystem::remove(filename);
				std::cout << "Deleted " << filename << "\n";
			}
			else {
				std::cout << "No weapon type file to delete.\n";
			}
		}
		else {
			std::cerr << "Weapon type file not found. Creating new file with default (NONE).\n";
		}

		// Create a new file with default weapon type
		ofstream outFile(filename, ios::out | ios::trunc);
		if (outFile) {
			outFile << "Weapon Type: " << static_cast<int>(WeaponType::None_) << endl;
			outFile.close();
		}
		else {
			std::cerr << "Failed to create weapon type file.\n";
		}

		return WeaponType::None_;
	}

	std::string line;
	if (std::getline(inFile, line)) {
		size_t pos = line.find("Weapon Type:");
		if (pos != std::string::npos) {
			try {
				int typeInt = std::stoi(line.substr(pos + std::string("Weapon Type:").length()));
				inFile.close();
				return static_cast<WeaponType>(typeInt);
			}
			catch (...) {
				std::cerr << "Error parsing weapon type. Using None_.\n";
			}
		}
	}

	inFile.close();
	return WeaponType::None_;
}