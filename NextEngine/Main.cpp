#define DEBUG_MODE // Launch in debug mode


// Imgui
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

// OpenGL headers
#include <GL/glew.h>

// SDL headers
#include <SDL_main.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include "GameEngine.h"
#include "InputManager.h"
#include "FrameRateCounter.h"
#include "QTEManager.h"
#include "LevelMainMenu.h"
#include "Ziz.h"
#include "Lucifer.h"
#include "SoundManager.h"

#ifndef DEBUG_MODE
GLint WIDTH = 1920, HEIGHT = 1080;
Uint32 windowScreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP;
#else
GLint WIDTH = 1600, HEIGHT = 900;
Uint32 windowScreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
#endif

using namespace std;
bool quit;
const unsigned int FPS = 200;
const unsigned int MIN_FPS = 24;
const int frameDelay = 1000 / FPS;
const int maxFrameDelay = 1000 / MIN_FPS;
uint64_t frameCount = 0;
uint64_t startTick;
uint64_t deltaTick;
//float test = 0.0f;

SDL_Window* window;
SDL_GLContext glContext;
SDL_Event sdlEvent;

SoundManager* soundManager = nullptr;
GameEngine * engine = nullptr;
QTEManager* qteManager = QTEManager::getInstance();

extern "C" {
	//high performance
	//_declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001; //nvidia
	//_declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; //amd

	//integrated
	//__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000000; //nvidia
	//__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0; //amd
}
	

int main(int argc, char *argv[]) {
	quit = false;
	srand(time(NULL));

	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Initialize video subsystem
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		// Display error message
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}

	// Create window
	window = SDL_CreateWindow("Hell Symphony", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, windowScreenFlag);
	if (window == NULL) {
		// Display error message
		cout << "Window could not be created! SDL_Error" << SDL_GetError() << endl;
		return false;
	}
	
	// Create OpenGL context
	glContext = SDL_GL_CreateContext(window);

	if (glContext == NULL) {
		// Display error message
		cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << endl;
		return false;
	}
	
	// Initialize glew
	GLenum glewError = glewInit();
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION);   // version as a string

	std::cout << "Renderer: " << renderer << std::endl;
	std::cout << "OpenGL version supported: " << version << std::endl;

	if (glewError != GLEW_OK) {
		cout << "Error initializing GLEW! " << glewGetErrorString(glewError) << endl;
		return false;
	}
	if (SDL_GL_SetSwapInterval(1) < 0) {
		cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << endl;
	}
	
	// imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(window, glContext);
	ImGui_ImplOpenGL3_Init();

	engine = GameEngine::getInstance();
	engine->init(WIDTH, HEIGHT);

	soundManager = SoundManager::GetInstance();
	soundManager->LoadSFX("Dante-Bow_HeavyAttack", "../Resource/Audio/SoundEffect/Dante-Bow_HeavyAttack.wav", false);
	soundManager->LoadSFX("Dante-Bow_LightAttack", "../Resource/Audio/SoundEffect/Dante-Bow_LightAttack.wav", false);
	soundManager->LoadSFX("Dante-Bow_UltBig", "../Resource/Audio/SoundEffect/Dante-Bow_UltBig.wav", false);
	soundManager->LoadSFX("Dante-Bow_UltSmall", "../Resource/Audio/SoundEffect/Dante-Bow_UltSmall.wav", false);
	soundManager->LoadSFX("Dante-Dash", "../Resource/Audio/SoundEffect/Dante-Dash.wav", false);
	soundManager->LoadSFX("Dante-Jump", "../Resource/Audio/SoundEffect/Dante-Jump.wav", false);
	soundManager->LoadSFX("Dante-QTE_Parry", "../Resource/Audio/SoundEffect/Dante-QTE_Parry.wav", false);
	soundManager->LoadSFX("Dante-Shield_Attack-1", "../Resource/Audio/SoundEffect/Dante-Shield_Attack-1.wav", false);
	soundManager->LoadSFX("Dante-Shield_Attack-2", "../Resource/Audio/SoundEffect/Dante-Shield_Attack-2.wav", false);
	soundManager->LoadSFX("Dante-Shield_Block", "../Resource/Audio/SoundEffect/Dante-Shield_Block.wav", false);
	soundManager->LoadSFX("Dante-Shield_BlockPerfect", "../Resource/Audio/SoundEffect/Dante-Shield_BlockPerfect.wav", false);
	soundManager->LoadSFX("Dante-Shield_UltBig", "../Resource/Audio/SoundEffect/Dante-Shield_UltBig.wav", false);
	soundManager->LoadSFX("Dante-Shield_UltSmall", "../Resource/Audio/SoundEffect/Dante-Shield_UltSmall.wav", false);
	soundManager->LoadSFX("Dante-Sword_HeavyAttack", "../Resource/Audio/SoundEffect/Dante-Sword_HeavyAttack.wav", false);
	soundManager->LoadSFX("Dante-Sword_LightAttack-1", "../Resource/Audio/SoundEffect/Dante-Sword_LightAttack-1.wav", false);
	soundManager->LoadSFX("Dante-Sword_LightAttack-2", "../Resource/Audio/SoundEffect/Dante-Sword_LightAttack-2.wav", false);
	soundManager->LoadSFX("Dante-Sword_LightAttack-3", "../Resource/Audio/SoundEffect/Dante-Sword_LightAttack-3.wav", false);
	soundManager->LoadSFX("Dante-Sword_UltBig", "../Resource/Audio/SoundEffect/Dante-Sword_UltBig.wav", false);
	soundManager->LoadSFX("Dante-Sword_UltSmall", "../Resource/Audio/SoundEffect/Dante-Sword_UltSmall.wav", false);

	soundManager->LoadSFX("Ziz_ClawSlash", "../Resource/Audio/SoundEffect/Ziz_ClawSlash.wav", false);
	soundManager->LoadSFX("Ziz_Gust", "../Resource/Audio/SoundEffect/Ziz_Gust.wav", false);
	soundManager->LoadSFX("Ziz_Idle", "../Resource/Audio/SoundEffect/Ziz_Idle.wav", false);
	soundManager->LoadSFX("Ziz_Impale", "../Resource/Audio/SoundEffect/Ziz_Impale.wav", false);
	soundManager->LoadSFX("Ziz_Lightning", "../Resource/Audio/SoundEffect/Ziz_Lightning.wav", false);
	soundManager->LoadSFX("Ziz_Storm", "../Resource/Audio/SoundEffect/Ziz_Storm.wav", false);
	soundManager->LoadSFX("Ziz_StormRise", "../Resource/Audio/SoundEffect/Ziz_StormRise.wav", false);
	soundManager->LoadSFX("Ziz_WingSweep", "../Resource/Audio/SoundEffect/Ziz_WingSweep.wav", false);
	soundManager->LoadSFX("Ziz_GroundSlam", "../Resource/Audio/SoundEffect/Ziz_GroundSlam.wav", false);
	soundManager->LoadSFX("Ziz_FlyUp", "../Resource/Audio/SoundEffect/Ziz_FlyUp.wav", false);

	soundManager->LoadSFX("Lucifer_CloseoutBeams", "../Resource/Audio/SoundEffect/Lucifer_CloseoutBeams.wav", false);
	soundManager->LoadSFX("Lucifer_HeartBeat", "../Resource/Audio/SoundEffect/Lucifer_HeartBeat.wav", false);
	soundManager->LoadSFX("Lucifer_SequenceExplosion", "../Resource/Audio/SoundEffect/Lucifer_SequenceExplosion.wav", false);
	soundManager->LoadSFX("Lucifer-Barrage_Release", "../Resource/Audio/SoundEffect/Lucifer-Barrage_Release.wav", false);
	soundManager->LoadSFX("Lucifer-BeamRadiant_Beam", "../Resource/Audio/SoundEffect/Lucifer-BeamRadiant_Beam.wav", false);
	soundManager->LoadSFX("Lucifer-BeamRadiant_Summon", "../Resource/Audio/SoundEffect/Lucifer-BeamRadiant_Summon.wav", false);
	soundManager->LoadSFX("Lucifer-HitPlayer_Beam", "../Resource/Audio/SoundEffect/Lucifer-HitPlayer_Beam.wav", false);
	soundManager->LoadSFX("Lucifer-HitPlayer_IceSpear", "../Resource/Audio/SoundEffect/Lucifer-HitPlayer_IceSpear.wav", false);
	soundManager->LoadSFX("Lucifer-HomingSpear_Release", "../Resource/Audio/SoundEffect/Lucifer-HomingSpear_Release.wav", false);
	soundManager->LoadSFX("Lucifer-DiamondDust", "../Resource/Audio/SoundEffect/Lucifer-DiamondDust.wav", false);
	soundManager->LoadSFX("Lucifer-HorizontalBeam", "../Resource/Audio/SoundEffect/Lucifer-HorizontalBeam.wav", false);

	soundManager->LoadSFX("Misc-ButtonClick", "../Resource/Audio/SoundEffect/Misc-ButtonClick.wav", false);
	soundManager->LoadSFX("Misc-ChooseWeapon", "../Resource/Audio/SoundEffect/Misc-ChooseWeapon.wav", false);
	soundManager->LoadSFX("Misc-Die+DeathScreen", "../Resource/Audio/SoundEffect/Misc-Die+DeathScreen.wav", false);
	soundManager->LoadSFX("Misc-HitDummy", "../Resource/Audio/SoundEffect/Misc-HitDummy.wav", false);
	soundManager->LoadSFX("Misc-HitEnemy", "../Resource/Audio/SoundEffect/Misc-HitEnemy.wav", false);
	soundManager->LoadSFX("Misc-PortalEnter", "../Resource/Audio/SoundEffect/Misc-PortalEnter.wav", false);
	soundManager->LoadSFX("Misc-VictoryScreen", "../Resource/Audio/SoundEffect/Misc-VictoryScreen.wav", false);

	/*soundManager->LoadSFX("Ziz_Lust-Ambient", "../Resource/Audio/SoundEffect/Ziz_Lust-Ambient.wav", true);
	soundManager->LoadSFX("Ziz_Gluttony-Ambient", "../Resource/Audio/SoundEffect/Ziz_Gluttony-Ambient.wav", true);
	soundManager->LoadSFX("Lucifer-Ambient", "../Resource/Audio/SoundEffect/Lucifer-Ambient.wav", true);*/

	soundManager->LoadMusic("Limbo-SoundTrack", "../Resource/Audio/Music/Limbo-Soundtrack.mp3", false);
	soundManager->LoadMusic("MainMenu-SoundTrack", "../Resource/Audio/Music/MainMenu-Soundtrack.mp3", false);
	soundManager->LoadMusic("Ziz_Lust-Soundtrack", "../Resource/Audio/Music/Ziz_Lust-Soundtrack.mp3", false);
	soundManager->LoadMusic("Ziz_Gluttony-Soundtrack", "../Resource/Audio/Music/Ziz_Gluttony-Soundtrack.mp3", false);
	soundManager->LoadMusic("Lucifer-Soundtrack", "../Resource/Audio/Music/Lucifer-Soundtrack.mp3", false);



	FrameRateCounter fpsCounter;

	// Game loop
	while (engine->getStateController()->gameStateCurr != GameState::GS_QUIT) {

		if (engine->getStateController()->gameStateCurr != GS_RESTART) {
			engine->getStateController()->loadLevel();
		}
		else {
			engine->getStateController()->gameStateNext =
			engine->getStateController()->gameStateCurr = engine->getStateController()->gameStatePrev;
		}

		// Initialize the gamestate
		engine->getStateController()->initLevel();
		Ziz* ziz = Ziz::getInstance();
		Lucifer* lucifer = Lucifer::getInstance();

		while (engine->getStateController()->gameStateCurr == engine->getStateController()->gameStateNext) {
			/*SDL_GetWindowSize(window, &WIDTH, &HEIGHT);
			engine->setWindowWidth(WIDTH);
			engine->setWindowHeight(HEIGHT);*/

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();

			Level* currentLevel = engine->getStateController()->getLevel();
			InputManager* inputManager = engine->getInputHandler();

			soundManager->update();

			//GameEngine::getInstance()->getAudio()->update();



			// toggle fullscreen
			if (inputManager->getButtonDown(SDLK_F11)) {
				cout << "Window Before (Width,Height): " << engine->getWindowWidth() << "," << engine->getWindowHeight() << endl;
				windowScreenFlag ^= SDL_WINDOW_FULLSCREEN_DESKTOP;
				SDL_SetWindowFullscreen(window, windowScreenFlag);
				int newWidth, newHeight;
				SDL_GetWindowSize(window, &newWidth, &newHeight);
				engine->setWindowWidth(newWidth);
				engine->setWindowHeight(newHeight);
				engine->getRenderer()->setViewPort(0, 0, engine->getWindowWidth(), engine->getWindowHeight());
				cout << "Window After (Width,Height): " << engine->getWindowWidth() << "," << engine->getWindowHeight() << endl;
			}

			startTick = SDL_GetTicks();

			//quit
			if (inputManager->getButtonDown(SDLK_ESCAPE)) {
				LevelMainMenu* mainMenu = dynamic_cast<LevelMainMenu*>(currentLevel);
				if (mainMenu) {
					engine->getStateController()->gameStateNext = GameState::GS_QUIT;
				}
				engine->getStateController()->handleKeyLevel('E');
			}

			if (ziz->getQTEMode() == true || (lucifer->getQTEMode() == true)) {
				if (inputManager->getButtonDown(SDLK_a)) {
					engine->getStateController()->handleKeyLevel('a');  
				}
				if (inputManager->getButtonDown(SDLK_d)) {
					engine->getStateController()->handleKeyLevel('d');
				}
			}
			else {
				if (inputManager->getButton(SDLK_a)) {
					engine->getStateController()->handleKeyLevel('a');  
				}
				if (inputManager->getButton(SDLK_d)) {
					engine->getStateController()->handleKeyLevel('d');
				}
			}
			
			

			LevelMainMenu* mainMenu = dynamic_cast<LevelMainMenu*>(currentLevel);
			if (mainMenu) {
				if (inputManager->getButtonDown(SDLK_w)) {
					engine->getStateController()->handleKeyLevel('w');
				}
				if (inputManager->getButtonDown(SDLK_s)) {
					engine->getStateController()->handleKeyLevel('s');
				}
			}
			else {
				if (inputManager->getButtonDown(SDLK_w)) {
					engine->getStateController()->handleKeyLevel('w');
				}
				if (inputManager->getButtonDown(SDLK_s)) {
					engine->getStateController()->handleKeyLevel('s');
				}
			}
			
			if (inputManager->getButtonDown(SDLK_SPACE)) {
				engine->getStateController()->handleKeyLevel('S');
			}
			if (inputManager->getButtonDown(SDLK_LSHIFT)) {
				engine->getStateController()->handleKeyLevel('P');
			}

			

			if (inputManager->getButtonDown(SDL_CONTROLLER_AXIS_TRIGGERLEFT)) {
				cout << "L2" << endl;
			}

			//controller

			if (ziz->getQTEMode() == true || lucifer->getQTEMode() == true) {
				if (inputManager->getControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
					engine->getStateController()->handleControllerButtonLevel(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
				}
				if (inputManager->getControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
					engine->getStateController()->handleControllerButtonLevel(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
				}
			}
			else {
				if (inputManager->getControllerButton(SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
					engine->getStateController()->handleControllerButtonLevel(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
				}
				if (inputManager->getControllerButton(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
					engine->getStateController()->handleControllerButtonLevel(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
				}
			}

			if (mainMenu) {
				if (inputManager->getControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_UP)) {
					engine->getStateController()->handleControllerButtonLevel(SDL_CONTROLLER_BUTTON_DPAD_UP);
				}
				if (inputManager->getControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
					engine->getStateController()->handleControllerButtonLevel(SDL_CONTROLLER_BUTTON_DPAD_DOWN);
				}
			}
			else {
				if (inputManager->getControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_UP)) {
					engine->getStateController()->handleControllerButtonLevel(SDL_CONTROLLER_BUTTON_DPAD_UP);
				}
				if (inputManager->getControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
					engine->getStateController()->handleControllerButtonLevel(SDL_CONTROLLER_BUTTON_DPAD_DOWN);
				}
			}
			
			



			if (inputManager->getControllerButtonDown(SDL_CONTROLLER_BUTTON_X)) {
				//cout << "X Pressed" << endl;
				engine->getStateController()->handleControllerButtonLevel(SDL_CONTROLLER_BUTTON_X);
			}
			if (inputManager->getControllerButtonDown(SDL_CONTROLLER_BUTTON_Y)) {
				//cout << "Y Pressed" << endl;
				engine->getStateController()->handleControllerButtonLevel(SDL_CONTROLLER_BUTTON_Y);
			}
			if (inputManager->getControllerButtonUp(SDL_CONTROLLER_BUTTON_Y)) {
				engine->getStateController()->handleMouseLevel(3, 0, 0);
			}
			if (inputManager->getControllerButtonDown(SDL_CONTROLLER_BUTTON_A)) {
				//cout << "A Pressed" << endl;
				engine->getStateController()->handleControllerButtonLevel(SDL_CONTROLLER_BUTTON_A);
			}
			if (inputManager->getControllerButtonDown(SDL_CONTROLLER_BUTTON_B)) {
				//cout << "B Pressed" << endl;
				engine->getStateController()->handleControllerButtonLevel(SDL_CONTROLLER_BUTTON_B);
			}
			if (inputManager->getControllerButtonDown(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
				//cout << "B Pressed" << endl;
				engine->getStateController()->handleControllerButtonLevel(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
			}

			// Get the current trigger values
			float leftTriggerValue = inputManager->getControllerLeftTrigger();
			float rightTriggerValue = inputManager->getControllerRightTrigger();

			// Check if the triggers are being pressed (you can define a threshold)
			float triggerThreshold = 0.1f; // Example threshold

			if (leftTriggerValue > triggerThreshold) {
				// L2 is being pressed
				cout << setprecision(2) << "L2: " << leftTriggerValue << endl;
				engine->getStateController()->handleAnalogLevel(SDL_CONTROLLER_AXIS_TRIGGERLEFT, '5');
			}

			if (rightTriggerValue > triggerThreshold) {
				// R2 is being pressed
				cout << setprecision(2) << "R2: " << rightTriggerValue << endl;
				engine->getStateController()->handleAnalogLevel(SDL_CONTROLLER_AXIS_TRIGGERRIGHT, '6');
			}



			

			//if (!inputManager.getButton(SDLK_a) && !inputManager.getButton(SDLK_d) && !inputManager.getButton(SDLK_w) && !inputManager.getButton(SDLK_s)) { // Not pressing any movement key -> idle
			//	engine->getStateController()->handleKeyLevel('I');
			//}

			if (inputManager->isMovementInputIdle()) { // Not pressing any movement key or controller direction -> idle
				//cout << "not receieving input" << endl;
				engine->getStateController()->handleKeyLevel('I');
			}

			//Camera Controls
			if (inputManager->getButtonDown(SDLK_f)) {
				engine->getStateController()->handleKeyLevel('f');
			}
			if (inputManager->getButton(SDLK_z)) {
				engine->getStateController()->handleKeyLevel('z');
			}
			if (inputManager->getButton(SDLK_x)) {
				engine->getStateController()->handleKeyLevel('x');
			}

			//UI test
			if (inputManager->getButton(SDLK_h)) {
				engine->getStateController()->handleKeyLevel('h');
			}
			if (inputManager->getButton(SDLK_j)) {
				engine->getStateController()->handleKeyLevel('j');
			}

			// Handle other specific keys (R, E)
			if (inputManager->getButtonDown(SDLK_r)) {
				engine->getStateController()->handleKeyLevel('r');
			}
			if (inputManager->	getButtonDown(SDLK_e)) {
				engine->getStateController()->handleKeyLevel('e');
			}
			
			if (inputManager->getButtonDown(SDLK_c)) {
				engine->getStateController()->handleKeyLevel('c');
			}
			if (inputManager->getButtonDown(SDLK_g)) {
				engine->getStateController()->handleKeyLevel('g');
			}
			if (inputManager->getButton(SDLK_SPACE)) {
				engine->getStateController()->handleKeyLevel(' ');
			}
			if (inputManager->getButtonDown(SDLK_q)) {
				engine->getStateController()->handleKeyLevel('q');
			}
			if (inputManager->getButtonDown(SDLK_t)) {
				engine->getStateController()->handleKeyLevel('t');
			}
			if (inputManager->getButtonDown(SDLK_l)) {
				engine->getStateController()->handleKeyLevel('l');
			}
			if (inputManager->getButtonDown(SDLK_m)) {
				engine->getStateController()->handleKeyLevel('m');
			}

			if (inputManager->getButtonDown(SDLK_1)) {
				engine->getStateController()->handleKeyLevel('1');
			}
			if (inputManager->getButtonDown(SDLK_2)) {
				engine->getStateController()->handleKeyLevel('2');
			}
			if (inputManager->getButtonDown(SDLK_3)) {
				engine->getStateController()->handleKeyLevel('3');
			}
			if (inputManager->getButtonDown(SDLK_4)) {
				engine->getStateController()->handleKeyLevel('4');
			}

			// Handle mouse button clicks (changed)
			if (inputManager->getMouseButtonDown(SDL_BUTTON_LEFT)) {
				int mouseX = inputManager->getMouseX();
				int mouseY = inputManager->getMouseY();
				engine->getStateController()->handleMouseLevel(0, mouseX, mouseY);  // Handle mouse click at (x, y)
			}

			if (inputManager->getMouseButtonDown(SDL_BUTTON_RIGHT)) {
				int mouseX = inputManager->getMouseX();
				int mouseY = inputManager->getMouseY();
				engine->getStateController()->handleMouseLevel(1, mouseX, mouseY);  // Handle mouse click at (x, y)
			}

			if (inputManager->getMouseButtonUp(SDL_BUTTON_LEFT)) {
				int mouseX = inputManager->getMouseX();
				int mouseY = inputManager->getMouseY();
				engine->getStateController()->handleMouseLevel(2, mouseX, mouseY);  // Handle mouse click at (x, y)
			}

			if (inputManager->getMouseButtonUp(SDL_BUTTON_RIGHT)) {
				int mouseX = inputManager->getMouseX();
				int mouseY = inputManager->getMouseY();
				engine->getStateController()->handleMouseLevel(3, mouseX, mouseY);  // Handle mouse click at (x, y)
			}

			if (inputManager->getMouseButton(SDL_BUTTON_LEFT)) {
				int mouseX = inputManager->getMouseX();
				int mouseY = inputManager->getMouseY();
				engine->getStateController()->handleMouseLevel(4, mouseX, mouseY);  // Handle mouse click at (x, y)
			}

			if (inputManager->getMouseButton(SDL_BUTTON_RIGHT)) {
				int mouseX = inputManager->getMouseX();
				int mouseY = inputManager->getMouseY();
				engine->getStateController()->handleMouseLevel(5, mouseX, mouseY);  // Handle mouse click at (x, y)
			}

			

			if (inputManager->getControllerButtonDown(SDL_CONTROLLER_BUTTON_START)) {
				//engine->getStateController()->gameStateNext = GameState::GS_RESTART;
				engine->getStateController()->handleControllerButtonLevel(SDL_CONTROLLER_BUTTON_START);
			}

			if (inputManager->getControllerAnalogStickX() > 0.15) {
				engine->getStateController()->handleAnalogLevel(0, 'r');
			}

			if (inputManager->getControllerAnalogStickX() < -0.15) {
				engine->getStateController()->handleAnalogLevel(0, 'l');
			}

			


			if ((inputManager->getControllerAnalogStickY() > 0.05) || (inputManager->getControllerAnalogStickY() < -0.05)) {
				engine->getStateController()->handleAnalogLevel(1, inputManager->getControllerAnalogStickY());
			}

			//while (SDL_PollEvent(&sdlEvent) != 0) {
			//	// Esc button is pressed
			//	if (sdlEvent.type == SDL_QUIT) {
			//		engine->getStateController()->gameStateNext = GameState::GS_QUIT;
			//	}
			//	else if (sdlEvent.type == SDL_KEYDOWN) {
			//		switch (sdlEvent.key.keysym.sym) {
			//		case SDLK_LEFT:
			//		case SDLK_a:	engine->getStateController()->handleKeyLevel('a'); break;
			//		case SDLK_RIGHT:
			//		case SDLK_d:	engine->getStateController()->handleKeyLevel('d'); break;
			//		case SDLK_UP:
			//		case SDLK_w:	engine->getStateController()->handleKeyLevel('w'); break;
			//		case SDLK_DOWN:
			//		case SDLK_s:	engine->getStateController()->handleKeyLevel('s'); break;
			//		case SDLK_ESCAPE: engine->getStateController()->handleKeyLevel('q'); break;
			//		case SDLK_r: engine->getStateController()->handleKeyLevel('r'); break;
			//		case SDLK_e: engine->getStateController()->handleKeyLevel('e'); break;
			//		case SDLK_z: engine->getStateController()->handleKeyLevel('z'); break;
			//		case SDLK_x: engine->getStateController()->handleKeyLevel('x'); break;
			//		}
			//	}
			//	else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
			//		if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
			//			engine->getStateController()->handleMouseLevel(0, sdlEvent.button.x, sdlEvent.button.y);
			//		}
			//	}
			//}

			deltaTick = SDL_GetTicks() - startTick;

			if (deltaTick < frameDelay) {
				SDL_Delay(frameDelay - deltaTick);
			}

			if (deltaTick < maxFrameDelay) {
				engine->getTime()->updateTick(SDL_GetTicks());
			}
			else {
				engine->getTime()->updateTickCounterOnly(SDL_GetTicks());
			}

			//engine->getTime()->updateTick(SDL_GetTicks());
			inputManager->updateInput(); // Update input states

			qteManager->update();

			engine->getStateController()->updateLevel();

			engine->getStateController()->drawLevel();
			fpsCounter.update();
			//fpsCounter.displayFPS();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			SDL_GL_SwapWindow(window);
			// Limiting the FPS to 60
			

			//cout << "Next " << GameData::GetInstance()->gGameStateNext << endl;
			//cout << "FPS: " << 1.0f / engine->getTime()->getDeltaTimeRealTime() << endl;
			
		}

		engine->getStateController()->freelevel();

		if (engine->getStateController()->gameStateNext != GS_RESTART) {

			engine->getStateController()->unloadLevel();
		}

		engine->getStateController()->gameStatePrev = engine->getStateController()->gameStateCurr;
		engine->getStateController()->gameStateCurr = engine->getStateController()->gameStateNext;	
	}

	//engine->getAudio()->saveVolumeToFile();
	soundManager->saveVolumeToFile();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	TTF_Quit();

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}


