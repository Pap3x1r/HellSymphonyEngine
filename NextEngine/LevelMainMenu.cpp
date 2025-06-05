#include "LevelMainMenu.h"
#include "CollisionHandler.h"
#include "GameEngine.h"
#include "GLRenderer.h" 
#include <iostream>
#include <random>
using namespace std;




void LevelMainMenu::levelLoad() {
	SquareMeshVbo* square = new SquareMeshVbo();
	square->loadData();
	GameEngine::getInstance()->addMesh(SquareMeshVbo::MESH_NAME, square);

	SquareBorderMesh* border = new SquareBorderMesh();
	border->loadData();
	GameEngine::getInstance()->addMesh(SquareBorderMesh::MESH_NAME, border);

	//cout << "Load Level" << endl;
}

void LevelMainMenu::levelInit() {

	SoundManager::GetInstance()->StopAllSounds();
	//Value
	float audioSettingsOffsetY = 0.2f;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Background
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* background1 = new TexturedObject("Background1");
	background1->setTexture("../Resource/Texture/newMainMenuBG.png");
	background1->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	background1->setMenuState(MenuState::NONE);
	objectsList.push_back(background1);

	TexturedObject* background2 = new TexturedObject("Background2");
	background2->setTexture("../Resource/Texture/newMainMenuBGOnly.png");
	background2->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	background2->setMenuState(MenuState::OPTIONS);
	background2->addMenuStateToVec(MenuState::AUDIO);
	background2->addMenuStateToVec(MenuState::CREDITS);
	background2->addMenuStateToVec(MenuState::CONTROLLER);
	background2->addMenuStateToVec(MenuState::KEYBOARD);
	objectsList.push_back(background2);

	TexturedObject* background3 = new TexturedObject("Background3");
	background3->setTexture("../Resource/Texture/MenuController.png");
	background3->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	background3->setMenuState(MenuState::CONTROLLER);
	objectsList.push_back(background3);

	TexturedObject* background4 = new TexturedObject("Background4");
	background4->setTexture("../Resource/Texture/MenuMKB.png");
	background4->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	background4->setMenuState(MenuState::KEYBOARD);
	objectsList.push_back(background4);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Overlays
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* overlayMKB = new TexturedObject();
	overlayMKB->setTexture("../Resource/Texture/KB_Bundle.png");
	overlayMKB->getTransform().setPosition(glm::vec3(-4.8f, -4.0f, 1.0f));
	overlayMKB->getTransform().setScale(glm::vec3(2.382f * 2.2f, 0.277f * 2.2f, 1.0f));
	overlayMKB->setMenuState(MenuState::NONE);
	/*overlayMKB->addMenuStateToVec(MenuState::AUDIO);
	overlayMKB->addMenuStateToVec(MenuState::CREDITS);
	overlayMKB->addMenuStateToVec(MenuState::CONTROLLER);
	overlayMKB->addMenuStateToVec(MenuState::KEYBOARD);*/
	objectsList.push_back(overlayMKB);
	kbOverlay = overlayMKB;

	TexturedObject* overlayController = new TexturedObject();
	overlayController->setTexture("../Resource/Texture/Controller_Bundle.png");
	overlayController->getTransform().setPosition(glm::vec3(-4.8f, -4.0f, 1.0f));
	overlayController->getTransform().setScale(glm::vec3(2.382f * 2.2f, 0.277f * 2.2f, 1.0f));
	overlayController->setMenuState(MenuState::NONE);
	/*overlayController->addMenuStateToVec(MenuState::AUDIO);
	overlayController->addMenuStateToVec(MenuState::CREDITS);
	overlayController->addMenuStateToVec(MenuState::CONTROLLER);
	overlayController->addMenuStateToVec(MenuState::KEYBOARD);*/
	objectsList.push_back(overlayController);
	controllerOverlay = overlayController;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Lines
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SimpleObject* line1 = new SimpleObject();
	line1->setColor(1.0f, 1.0f, 1.0f);
	line1->getTransform().setScale(glm::vec3(14.0f, 0.01f, 0.0f));	
	line1->getTransform().setPosition(glm::vec3(0.0f, 3.3f, 0.0f));
	line1->setMenuState(MenuState::OPTIONS);
	line1->addMenuStateToVec(MenuState::AUDIO);
	line1->addMenuStateToVec(MenuState::CREDITS);
	objectsList.push_back(line1);

	SimpleObject* line2 = new SimpleObject();
	line2->setColor(1.0f, 1.0f, 1.0f);
	line2->getTransform().setScale(glm::vec3(14.0f, 0.01f, 0.0f));
	line2->getTransform().setPosition(glm::vec3(0.0f, -3.5f, 0.0f));
	line2->setMenuState(MenuState::OPTIONS);
	line2->addMenuStateToVec(MenuState::AUDIO);
	line2->addMenuStateToVec(MenuState::CREDITS);
	objectsList.push_back(line2);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Master Volume Slider
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SliderObject* masterVolumeSlider = new SliderObject("Master Volume Slider");
	masterVolumeSlider->setPosition(glm::vec3(-1.0f, 1.7f + audioSettingsOffsetY, 1.0f), -1);
	masterVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 0);
	masterVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 1);
	masterVolumeSlider->setScale(glm::vec3(0.35f, 0.35f, 1.0f), 2);
	masterVolumeSlider->setColor(glm::vec3(0.5f, 0.5f, 0.5f), -1);
	masterVolumeSlider->setColor(glm::vec3(0.75f, 0.75f, 0.75f), 1);
	masterVolumeSlider->setMenuState(MenuState::AUDIO);
	masterVolumeSlider->setValue(SoundManager::GetInstance()->getMasterVolume());
	for (DrawableObject* obj : masterVolumeSlider->getObjectsList()) {
		objectsList.push_back(obj);
	}
	UIButton* masterVolumeHandle = static_cast<UIButton*>(masterVolumeSlider->getObject(2));
	masterVolumeHandle->setTexture("../Resource/Texture/UI/SliderHandle.png");
	slidersList.push_back(masterVolumeSlider);
	buttonsList.push_back(static_cast<UIButton*>(masterVolumeSlider->getObject(2)));
	audioButtons.push_back(static_cast<UIButton*>(masterVolumeSlider->getObject(2)));
	masterSlider = masterVolumeSlider;

	//////////////////////////////////////

	UIText* masterVolumeText = new UIText("Master Volume Text");
	SDL_Color masterVolumeTextColor = { 255,255,255,255 };
	masterVolumeText->loadText("Master Volume", masterVolumeTextColor, 100);
	masterVolumeText->setText("Master Volume");
	masterVolumeText->setAlpha(1.0f);
	masterVolumeText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	masterVolumeText->getTransform().setPosition(glm::vec3(-3.65f, 2.1f + audioSettingsOffsetY, 0.0f));
	masterVolumeText->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	masterVolumeText->addColliderComponent();
	masterVolumeText->setMenuState(MenuState::AUDIO);
	/*masterVolumeText->setDrawCollider(true);
	masterVolumeText->setCanDrawColliderNew(true);*/
	objectsList.push_back(masterVolumeText);

	UIButton* masterVolumeButton = new UIButton("Master Volume Button");
	//masterVolumeButton->setTexture("../Resource/Texture/UI/SliderHandle.png");
	masterVolumeButton->getTransform().setPosition(glm::vec3(-4.5f, 2.35f + audioSettingsOffsetY, 0.0f));
	masterVolumeButton->getTransform().setScale(glm::vec3(2.35f, 0.35f, 0.0f));
	masterVolumeButton->addColliderComponent();
	//masterVolumeButton->setDrawCollider(true);
	//masterVolumeButton->setCanDrawColliderNew(true);
	masterVolumeButton->setDraw(false);
	masterVolumeButton->setLabel(masterVolumeText); // Link continueText
	masterVolumeButton->setMenuState(MenuState::AUDIO);
	masterVolumeButton->setSlider(masterVolumeSlider);
	objectsList.push_back(masterVolumeButton);
	buttonsList.push_back(masterVolumeButton);

	audioButtons.push_back(masterVolumeButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Music Volume Slider
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SliderObject* musicVolumeSlider = new SliderObject("Music Volume Slider");
	musicVolumeSlider->setPosition(glm::vec3(-1.0f, 0.2f + audioSettingsOffsetY, 1.0f), -1);
	musicVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 1);
	musicVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 0);
	musicVolumeSlider->setScale(glm::vec3(0.35f, 0.35f, 1.0f), 2);
	musicVolumeSlider->setColor(glm::vec3(0.5f, 0.5f, 0.5f), -1);
	musicVolumeSlider->setColor(glm::vec3(0.75f, 0.75f, 0.75f), 1);
	musicVolumeSlider->setMenuState(MenuState::AUDIO);
	musicVolumeSlider->setValue(SoundManager::GetInstance()->getMusicVolume());
	for (DrawableObject* obj : musicVolumeSlider->getObjectsList()) {
		objectsList.push_back(obj);
	}
	UIButton* musicVolumeHandle = static_cast<UIButton*>(musicVolumeSlider->getObject(2));
	musicVolumeHandle->setTexture("../Resource/Texture/UI/SliderHandle.png");
	slidersList.push_back(musicVolumeSlider);
	buttonsList.push_back(static_cast<UIButton*>(musicVolumeSlider->getObject(2)));
	audioButtons.push_back(static_cast<UIButton*>(musicVolumeSlider->getObject(2)));
	musicSlider = musicVolumeSlider;

	//////////////////////////////////////

	UIText* musicVolumeText = new UIText("Music Volume Text");
	SDL_Color musicVolumeTextColor = { 255,255,255,255 };
	musicVolumeText->loadText("Music Volume", musicVolumeTextColor, 100);
	musicVolumeText->setText("Music Volume");
	musicVolumeText->setAlpha(1.0f);
	musicVolumeText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	musicVolumeText->getTransform().setPosition(glm::vec3(-3.65f, 0.65f + audioSettingsOffsetY, 0.0f));
	musicVolumeText->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	musicVolumeText->addColliderComponent();
	musicVolumeText->setMenuState(MenuState::AUDIO);
	/*musicVolumeText->setDrawCollider(true);
	musicVolumeText->setCanDrawColliderNew(true);*/
	objectsList.push_back(musicVolumeText);

	UIButton* musicVolumeButton = new UIButton("Music Volume Button");
	//musicVolumeButton->setTexture("../Resource/Texture/UI/UIButton.png");
	musicVolumeButton->getTransform().setPosition(glm::vec3(-4.55f, 0.9f + audioSettingsOffsetY, 0.0f));
	musicVolumeButton->getTransform().setScale(glm::vec3(2.3f, 0.35f, 0.0f));
	musicVolumeButton->addColliderComponent();
	//musicVolumeButton->setDrawCollider(true);
	//musicVolumeButton->setCanDrawColliderNew(true);
	musicVolumeButton->setDraw(false);
	musicVolumeButton->setLabel(musicVolumeText); // Link continueText
	musicVolumeButton->setMenuState(MenuState::AUDIO);
	musicVolumeButton->setSlider(musicVolumeSlider);
	objectsList.push_back(musicVolumeButton);
	buttonsList.push_back(musicVolumeButton);

	audioButtons.push_back(musicVolumeButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Effect Volume Slider
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SliderObject* effectVolumeSlider = new SliderObject("Effect Volume Slider");
	effectVolumeSlider->setPosition(glm::vec3(-1.0f, -1.25f + audioSettingsOffsetY, 1.0f), -1);
	effectVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 1);
	effectVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 0);
	effectVolumeSlider->setScale(glm::vec3(0.35f, 0.35f, 1.0f), 2);
	effectVolumeSlider->setColor(glm::vec3(0.5f, 0.5f, 0.5f), -1);
	effectVolumeSlider->setColor(glm::vec3(0.75f, 0.75f, 0.75f), 1);
	effectVolumeSlider->setMenuState(MenuState::AUDIO);
	effectVolumeSlider->setValue(SoundManager::GetInstance()->getSoundEffectVolume());
	for (DrawableObject* obj : effectVolumeSlider->getObjectsList()) {
		objectsList.push_back(obj);
	}
	UIButton* effectVolumeHandle = static_cast<UIButton*>(effectVolumeSlider->getObject(2));
	effectVolumeHandle->setTexture("../Resource/Texture/UI/SliderHandle.png");
	slidersList.push_back(effectVolumeSlider);
	buttonsList.push_back(static_cast<UIButton*>(effectVolumeSlider->getObject(2)));
	audioButtons.push_back(static_cast<UIButton*>(effectVolumeSlider->getObject(2)));
	sfxSlider = effectVolumeSlider;

	//////////////////////////////////////

	UIText* effectVolumeText = new UIText("Effect Volume Text");
	SDL_Color effectVolumeTextColor = { 255,255,255,255 };
	effectVolumeText->loadText("Effect Volume", effectVolumeTextColor, 100);
	effectVolumeText->setText("Effect Volume");
	effectVolumeText->setAlpha(1.0f);
	effectVolumeText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	effectVolumeText->getTransform().setPosition(glm::vec3(-3.65f, -0.8f + audioSettingsOffsetY, 0.0f));
	effectVolumeText->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	effectVolumeText->addColliderComponent();
	effectVolumeText->setMenuState(MenuState::AUDIO);
	/*effectVolumeText->setDrawCollider(true);
	effectVolumeText->setCanDrawColliderNew(true);*/
	objectsList.push_back(effectVolumeText);

	UIButton* effectVolumeButton = new UIButton("Effect Volume Button");
	//effectVolumeButton->setTexture("../Resource/Texture/UI/UIButton.png");
	effectVolumeButton->getTransform().setPosition(glm::vec3(-4.6f, -0.55f + audioSettingsOffsetY, 0.0f));
	effectVolumeButton->getTransform().setScale(glm::vec3(2.15f, 0.35f, 0.0f));
	effectVolumeButton->addColliderComponent();
	//effectVolumeButton->setDrawCollider(true);
	//effectVolumeButton->setCanDrawColliderNew(true);
	effectVolumeButton->setDraw(false);
	effectVolumeButton->setLabel(effectVolumeText); // Link continueText
	effectVolumeButton->setMenuState(MenuState::AUDIO);
	effectVolumeButton->setSlider(effectVolumeSlider);
	objectsList.push_back(effectVolumeButton);
	buttonsList.push_back(effectVolumeButton);

	audioButtons.push_back(effectVolumeButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Ambient Volume Slider
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SliderObject* ambientVolumeSlider = new SliderObject("Ambient Volume Slider");
	ambientVolumeSlider->setPosition(glm::vec3(-1.0f, -2.68f + audioSettingsOffsetY, 1.0f), -1);
	ambientVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 1);
	ambientVolumeSlider->setScale(glm::vec3(10.0f, 0.2f, 1.0f), 0);
	ambientVolumeSlider->setScale(glm::vec3(0.35f, 0.35f, 1.0f), 2);
	ambientVolumeSlider->setColor(glm::vec3(0.5f, 0.5f, 0.5f), -1);
	ambientVolumeSlider->setColor(glm::vec3(0.75f, 0.75f, 0.75f), 1);
	ambientVolumeSlider->setMenuState(MenuState::AUDIO);
	ambientVolumeSlider->setValue(SoundManager::GetInstance()->getAmbientVolume());
	for (DrawableObject* obj : ambientVolumeSlider->getObjectsList()) {
		objectsList.push_back(obj);
	}
	UIButton* ambientVolumeHandle = static_cast<UIButton*>(ambientVolumeSlider->getObject(2));
	ambientVolumeHandle->setTexture("../Resource/Texture/UI/SliderHandle.png");
	slidersList.push_back(ambientVolumeSlider);
	buttonsList.push_back(static_cast<UIButton*>(ambientVolumeSlider->getObject(2)));
	audioButtons.push_back(static_cast<UIButton*>(ambientVolumeSlider->getObject(2)));
	ambientSlider = ambientVolumeSlider;

	//////////////////////////////////////

	UIText* ambientVolumeText = new UIText("Ambient Volume Text");
	SDL_Color ambientVolumeTextColor = { 255,255,255,255 };
	ambientVolumeText->loadText("Ambient Volume", ambientVolumeTextColor, 100);
	ambientVolumeText->setText("Ambient Volume");
	ambientVolumeText->setAlpha(1.0f);
	ambientVolumeText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	ambientVolumeText->getTransform().setPosition(glm::vec3(-3.65f, -2.25f + audioSettingsOffsetY, 0.0f));
	ambientVolumeText->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	ambientVolumeText->addColliderComponent();
	ambientVolumeText->setMenuState(MenuState::AUDIO);
	/*ambientVolumeText->setDrawCollider(true);
	ambientVolumeText->setCanDrawColliderNew(true);*/
	objectsList.push_back(ambientVolumeText);

	UIButton* ambientVolumeButton = new UIButton("Ambient Volume Button");
	//ambientVolumeButton->setTexture("../Resource/Texture/UI/UIButton.png");
	ambientVolumeButton->getTransform().setPosition(glm::vec3(-4.35f, -2.0f + audioSettingsOffsetY, 0.0f));
	ambientVolumeButton->getTransform().setScale(glm::vec3(2.65f, 0.35f, 0.0f));
	ambientVolumeButton->addColliderComponent();
	//ambientVolumeButton->setDrawCollider(true);
	//ambientVolumeButton->setCanDrawColliderNew(true);
	ambientVolumeButton->setDraw(false);
	ambientVolumeButton->setLabel(ambientVolumeText); // Link continueText
	ambientVolumeButton->setMenuState(MenuState::AUDIO);
	ambientVolumeButton->setSlider(ambientVolumeSlider);
	objectsList.push_back(ambientVolumeButton);
	buttonsList.push_back(ambientVolumeButton);

	audioButtons.push_back(ambientVolumeButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Texts
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* staticSettingsText = new UIText("Static Settings Text");
	SDL_Color staticSettingsTextColor = { 255,255,255,255 };
	staticSettingsText->loadText("SETTINGS", staticSettingsTextColor, 100, true);
	staticSettingsText->setText("SETTINGS");
	staticSettingsText->setAlpha(1.0f);
	staticSettingsText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	staticSettingsText->getTransform().setPosition(glm::vec3(0.05f, 3.6f, 0.0f));
	staticSettingsText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	staticSettingsText->addColliderComponent();
	staticSettingsText->setMenuState(MenuState::OPTIONS);
	/*staticSettingsText->setDrawCollider(true);
	staticSettingsText->setCanDrawColliderNew(true);*/
	objectsList.push_back(staticSettingsText);

	UIText* staticAudioText = new UIText("Static Audio Text");
	SDL_Color staticAudioTextColor = { 255,255,255,255 };
	staticAudioText->loadText("AUDIO", staticAudioTextColor, 100, true);
	staticAudioText->setText("AUDIO");
	staticAudioText->setAlpha(1.0f);
	staticAudioText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	staticAudioText->getTransform().setPosition(glm::vec3(0.29f, 3.6f, 0.0f));
	staticAudioText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	staticAudioText->addColliderComponent();
	staticAudioText->setMenuState(MenuState::AUDIO);
	/*staticAudioText->setDrawCollider(true);
	staticAudioText->setCanDrawColliderNew(true);*/
	objectsList.push_back(staticAudioText);

	UIText* staticCreditsText = new UIText("Static Credits Text");
	SDL_Color staticCreditsTextColor = { 255,255,255,255 };
	staticCreditsText->loadText("CREDITS", staticCreditsTextColor, 100, true);
	staticCreditsText->setText("CREDITS");
	staticCreditsText->setAlpha(1.0f);
	staticCreditsText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	staticCreditsText->getTransform().setPosition(glm::vec3(0.15f, 3.6f, 0.0f));
	staticCreditsText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	staticCreditsText->addColliderComponent();
	staticCreditsText->setMenuState(MenuState::CREDITS);
	/*staticCreditsText->setDrawCollider(true);
	staticCreditsText->setCanDrawColliderNew(true);*/
	objectsList.push_back(staticCreditsText);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Credits Texts
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* studioText = new UIText("Studio Text");
	SDL_Color studioTextColor = { 255,255,255,255 };
	studioText->loadText("BLEND 285 STUDIOS", studioTextColor, 100, true);
	studioText->setText("BLEND 285 STUDIOS");
	studioText->setAlpha(1.0f);
	studioText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	studioText->getTransform().setPosition(glm::vec3(0.175f, 2.65f, 0.0f));
	studioText->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	studioText->addColliderComponent();
	studioText->setMenuState(MenuState::CREDITS);
	/*studioText->setDrawCollider(true);
	studioText->setCanDrawColliderNew(true);*/
	objectsList.push_back(studioText);

	UIText* gameDirectorText = new UIText("Game Director Text");
	SDL_Color gameDirectorTextColor = { 200,200,200,255 };
	gameDirectorText->loadText("Game Director", gameDirectorTextColor, 100);
	gameDirectorText->setText("Game Director");
	gameDirectorText->setAlpha(1.0f);
	gameDirectorText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	gameDirectorText->getTransform().setPosition(glm::vec3(-0.8f, 2.1f, 0.0f));
	gameDirectorText->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	gameDirectorText->addColliderComponent();
	gameDirectorText->setMenuState(MenuState::CREDITS);
	/*gameDirectorText->setDrawCollider(true);
	gameDirectorText->setCanDrawColliderNew(true);*/
	objectsList.push_back(gameDirectorText);

	UIText* productionDirectorText = new UIText("Production Director Text");
	SDL_Color productionDirectorTextColor = { 200,200,200,255 };
	productionDirectorText->loadText("Production Director", productionDirectorTextColor, 100);
	productionDirectorText->setText("Production Director");
	productionDirectorText->setAlpha(1.0f);
	productionDirectorText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	productionDirectorText->getTransform().setPosition(glm::vec3(-1.65f, 1.4f, 0.0f));
	productionDirectorText->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	productionDirectorText->addColliderComponent();
	productionDirectorText->setMenuState(MenuState::CREDITS);
	/*productionDirectorText->setDrawCollider(true);
	productionDirectorText->setCanDrawColliderNew(true);*/
	objectsList.push_back(productionDirectorText);

	UIText* artDirectorText = new UIText("Art Director Text");
	SDL_Color artDirectorTextColor = { 200,200,200,255 };
	artDirectorText->loadText("Art Director", artDirectorTextColor, 100);
	artDirectorText->setText("Art Director");
	artDirectorText->setAlpha(1.0f);
	artDirectorText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	artDirectorText->getTransform().setPosition(glm::vec3(-1.45f, 0.7f, 0.0f));
	artDirectorText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	artDirectorText->addColliderComponent();
	artDirectorText->setMenuState(MenuState::CREDITS);
	/*artDirectorText->setDrawCollider(true);
	artDirectorText->setCanDrawColliderNew(true);*/
	objectsList.push_back(artDirectorText);

	UIText* designersText = new UIText("Designers Text");
	SDL_Color designersTextColor = { 200,200,200,255 };
	designersText->loadText("Designers", designersTextColor, 100);
	designersText->setText("Designers");
	designersText->setAlpha(1.0f);
	designersText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	designersText->getTransform().setPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
	designersText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	designersText->addColliderComponent();
	designersText->setMenuState(MenuState::CREDITS);
	/*designersText->setDrawCollider(true);
	designersText->setCanDrawColliderNew(true);*/
	objectsList.push_back(designersText);

	UIText* artistsText = new UIText("Artists Text");
	SDL_Color artistsTextColor = { 200,200,200,255 };
	artistsText->loadText("Artists", artistsTextColor, 100);
	artistsText->setText("Artists");
	artistsText->setAlpha(1.0f);
	artistsText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	artistsText->getTransform().setPosition(glm::vec3(-1.05f, -1.1f, 0.0f));
	artistsText->getTransform().setScale(glm::vec3(1.0f, 1.0f, 0.0f));
	artistsText->addColliderComponent();
	artistsText->setMenuState(MenuState::CREDITS);
	/*artistsText->setDrawCollider(true);
	artistsText->setCanDrawColliderNew(true);*/
	objectsList.push_back(artistsText);

	UIText* programmersText = new UIText("Programmers Text");
	SDL_Color programmersTextColor = { 200,200,200,255 };
	programmersText->loadText("Programmers", programmersTextColor, 100);
	programmersText->setText("Programmers");
	programmersText->setAlpha(1.0f);
	programmersText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	programmersText->getTransform().setPosition(glm::vec3(-0.55f, -2.6f, 0.0f));
	programmersText->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	programmersText->addColliderComponent();
	programmersText->setMenuState(MenuState::CREDITS);
	/*programmersText->setDrawCollider(true);
	programmersText->setCanDrawColliderNew(true);*/
	objectsList.push_back(programmersText);

	UIText* putawan1Text = new UIText("putawan1 Text");
	SDL_Color putawan1TextColor = { 255,255,255,255 };
	putawan1Text->loadText("Putawan Bunnate", putawan1TextColor, 100);
	putawan1Text->setText("Putawan Bunnate");
	putawan1Text->setAlpha(1.0f);
	putawan1Text->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	putawan1Text->getTransform().setPosition(glm::vec3(2.5f, 2.1f, 0.0f));
	putawan1Text->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	putawan1Text->addColliderComponent();
	putawan1Text->setMenuState(MenuState::CREDITS);
	/*putawan1Text->setDrawCollider(true);
	putawan1Text->setCanDrawColliderNew(true);*/
	objectsList.push_back(putawan1Text);

	UIText* karanyaphat1Text = new UIText("karanyaphat1 Text");
	SDL_Color karanyaphat1TextColor = { 255,255,255,255 };
	karanyaphat1Text->loadText("Karanyaphat Phuphong", karanyaphat1TextColor, 100);
	karanyaphat1Text->setText("Karanyaphat Phuphong");
	karanyaphat1Text->setAlpha(1.0f);
	karanyaphat1Text->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	karanyaphat1Text->getTransform().setPosition(glm::vec3(2.5f, 1.4f, 0.0f));
	karanyaphat1Text->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	karanyaphat1Text->addColliderComponent();
	karanyaphat1Text->setMenuState(MenuState::CREDITS);
	/*karanyaphat1Text->setDrawCollider(true);
	karanyaphat1Text->setCanDrawColliderNew(true);*/
	objectsList.push_back(karanyaphat1Text);

	UIText* pasipong1Text = new UIText("pasipong1 Text");
	SDL_Color pasipong1TextColor = { 255,255,255,255 };
	pasipong1Text->loadText("Pasipong Sirithanikawet", pasipong1TextColor, 100);
	pasipong1Text->setText("Pasipong Sirithanikawet");
	pasipong1Text->setAlpha(1.0f);
	pasipong1Text->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	pasipong1Text->getTransform().setPosition(glm::vec3(2.5f, 0.7f, 0.0f));
	pasipong1Text->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	pasipong1Text->addColliderComponent();
	pasipong1Text->setMenuState(MenuState::CREDITS);
	/*pasipong1Text->setDrawCollider(true);
	pasipong1Text->setCanDrawColliderNew(true);*/
	objectsList.push_back(pasipong1Text);

	UIText* napas1Text = new UIText("napas1 Text");
	SDL_Color napas1TextColor = { 255,255,255,255 };
	napas1Text->loadText("Napas Rakkarnpatch", napas1TextColor, 100);
	napas1Text->setText("Napas Rakkarnpatch");
	napas1Text->setAlpha(1.0f);
	napas1Text->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	napas1Text->getTransform().setPosition(glm::vec3(2.5f, 0.0f, 0.0f));
	napas1Text->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	napas1Text->addColliderComponent();
	napas1Text->setMenuState(MenuState::CREDITS);
	/*napas1Text->setDrawCollider(true);
	napas1Text->setCanDrawColliderNew(true);*/
	objectsList.push_back(napas1Text);

	UIText* putawan2Text = new UIText("putawan2 Text");
	SDL_Color putawan2TextColor = { 255,255,255,255 };
	putawan2Text->setText("Putawan Bunnate");
	putawan2Text->loadText("Putawan Bunnate", putawan2TextColor, 100);
	putawan2Text->setAlpha(1.0f);
	putawan2Text->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	putawan2Text->getTransform().setPosition(glm::vec3(2.5f, -0.4f, 0.0f));
	putawan2Text->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	putawan2Text->addColliderComponent();
	putawan2Text->setMenuState(MenuState::CREDITS);
	/*putawan2Text->setDrawCollider(true);
	putawan2Text->setCanDrawColliderNew(true);*/
	objectsList.push_back(putawan2Text);

	UIText* akkarawin1Text = new UIText("akkarawin1 Text");
	SDL_Color akkarawin1TextColor = { 255,255,255,255 };
	akkarawin1Text->setText("Akkarawin Charoenwitworakul");
	akkarawin1Text->loadText("Akkarawin Charoenwitworakul", akkarawin1TextColor, 100);
	akkarawin1Text->setAlpha(1.0f);
	akkarawin1Text->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	akkarawin1Text->getTransform().setPosition(glm::vec3(4.5f, -1.1f, 0.0f));
	akkarawin1Text->getTransform().setScale(glm::vec3(8.0f, 1.0f, 0.0f));
	akkarawin1Text->addColliderComponent();
	akkarawin1Text->setMenuState(MenuState::CREDITS);
	/*putawan2Text->setDrawCollider(true);
	putawan2Text->setCanDrawColliderNew(true);*/
	objectsList.push_back(akkarawin1Text);

	UIText* nathadech1Text = new UIText("nathadech1 Text");
	SDL_Color nathadech1TextColor = { 255,255,255,255 };
	nathadech1Text->setText("Nathadech Koboonchuay");
	nathadech1Text->loadText("Nathadech Koboonchuay", nathadech1TextColor, 100);
	nathadech1Text->setAlpha(1.0f);
	nathadech1Text->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	nathadech1Text->getTransform().setPosition(glm::vec3(2.5f, -1.5f, 0.0f));
	nathadech1Text->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	nathadech1Text->addColliderComponent();
	nathadech1Text->setMenuState(MenuState::CREDITS);
	/*nathadech1Text->setDrawCollider(true);
	nathadech1Text->setCanDrawColliderNew(true);*/
	objectsList.push_back(nathadech1Text);

	UIText* pasipong2Text = new UIText("pasipong2 Text");
	SDL_Color pasipong2TextColor = { 255,255,255,255 };
	pasipong2Text->setText("Pasipong Sirithanikawet");
	pasipong2Text->loadText("Pasipong Sirithanikawet", pasipong2TextColor, 100);
	pasipong2Text->setAlpha(1.0f);
	pasipong2Text->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	pasipong2Text->getTransform().setPosition(glm::vec3(2.5f, -1.9f, 0.0f));
	pasipong2Text->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	pasipong2Text->addColliderComponent();
	pasipong2Text->setMenuState(MenuState::CREDITS);
	/*pasipong2Text->setDrawCollider(true);
	pasipong2Text->setCanDrawColliderNew(true);*/
	objectsList.push_back(pasipong2Text);

	UIText* karanyaphat2Text = new UIText("karanyaphat2 Text");
	SDL_Color karanyaphat2TextColor = { 255,255,255,255 };
	karanyaphat2Text->setText("Karanyaphat Phuphong");
	karanyaphat2Text->loadText("Karanyaphat Phuphong", karanyaphat2TextColor, 100);
	karanyaphat2Text->setAlpha(1.0f);
	karanyaphat2Text->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	karanyaphat2Text->getTransform().setPosition(glm::vec3(2.5f, -2.6f, 0.0f));
	karanyaphat2Text->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	karanyaphat2Text->addColliderComponent();
	karanyaphat2Text->setMenuState(MenuState::CREDITS);
	/*karanyaphat2Text->setDrawCollider(true);
	karanyaphat2Text->setCanDrawColliderNew(true);*/
	objectsList.push_back(karanyaphat2Text);

	UIText* sarun1Text = new UIText("sarun1 Text");
	SDL_Color sarun1TextColor = { 255,255,255,255 };
	sarun1Text->setText("Sarun Pachiyanukoon");
	sarun1Text->loadText("Sarun Pachiyanukoon", sarun1TextColor, 100);
	sarun1Text->setAlpha(1.0f);
	sarun1Text->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	sarun1Text->getTransform().setPosition(glm::vec3(2.5f, -3.0f, 0.0f));
	sarun1Text->getTransform().setScale(glm::vec3(4.0f, 1.0f, 0.0f));
	sarun1Text->addColliderComponent();
	sarun1Text->setMenuState(MenuState::CREDITS);
	/*sarun1Text->setDrawCollider(true);
	pasipong2sarun1TextText->setCanDrawColliderNew(true);*/
	objectsList.push_back(sarun1Text);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Continue Button
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* continueText = new UIText("Continue Text");
	SDL_Color continueTextColor = { 255,255,255,255 };
	continueText->loadText("Continue", continueTextColor, 100);
	continueText->setText("Continue");
	continueText->setAlpha(1.0f);
	continueText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	continueText->getTransform().setPosition(glm::vec3(0.25f, 0.0f - 0.6f, 0.0f));
	continueText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	continueText->addColliderComponent();
	continueText->setMenuState(MenuState::MAIN);
	/*continueText->setDrawCollider(true);
	continueText->setCanDrawColliderNew(true);*/
	objectsList.push_back(continueText);

	UIButton* continueButton_ = new UIButton("Continue Button");
	//continueButton_->setTexture("../Resource/Texture/UI/UIButton.png");
	continueButton_->getTransform().setPosition(glm::vec3(0.0f, 0.25f - 0.6f, 0.0f));
	continueButton_->getTransform().setScale(glm::vec3(1.6f, 0.35f, 0.0f));
	continueButton_->addColliderComponent();
	continueButton_->setDrawCollider(true);
	continueButton_->setCanDrawColliderNew(false);
	continueButton_->setDraw(false);
	continueButton_->setLabel(continueText); // Link continueText
	continueButton_->setMenuState(MenuState::MAIN);
	continueButton_->setFunction([this]() {
		loadGame();
		});
	if (fileExists("../Resource/Saves/PlayerData/playerGameState.txt")) {
		objectsList.push_back(continueButton_);
		buttonsList.push_back(continueButton_);

		mainButtons.push_back(continueButton_);

	}
	else {
		objectsList.push_back(continueButton_);
		continueButton_->setActive(false);
	}

	continueButton = continueButton_;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										New Game Button
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* playText = new UIText("New Game Text");
	SDL_Color playTextColor = { 255,255,255,255 };
	playText->loadText("New Game", playTextColor, 100);
	playText->setText("New Game");
	playText->setAlpha(1.0f);
	playText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	playText->getTransform().setPosition(glm::vec3(0.15f, -0.525f - 0.7f, 0.0f));
	playText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	playText->addColliderComponent();
	playText->setMenuState(MenuState::MAIN);
	/*playText->setDrawCollider(true);
	playText->setCanDrawColliderNew(true);*/
	objectsList.push_back(playText);

	UIButton* playButton = new UIButton("New Game Button");
	//playButton->setTexture("../Resource/Texture/UI/UIButton.png");
	playButton->getTransform().setPosition(glm::vec3(0.0f, -0.28f - 0.7f, 0.0f));
	playButton->getTransform().setScale(glm::vec3(1.8f, 0.35f, 0.0f));
	playButton->addColliderComponent();
	playButton->setDrawCollider(true);
	playButton->setCanDrawColliderNew(false);
	playButton->setDraw(false);
	playButton->setLabel(playText); // Link playText
	playButton->setMenuState(MenuState::MAIN);
	playButton->setFunction([this]() {
		startNewGameTransition();
	});

	objectsList.push_back(playButton);
	buttonsList.push_back(playButton);

	mainButtons.push_back(playButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Settings Button
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* settingsText = new UIText("Settings Text");
	SDL_Color settingsTextColor = { 255,255,255,255 };
	settingsText->loadText("Settings", settingsTextColor, 100);
	settingsText->setText("Settings");
	settingsText->setAlpha(1.0f);
	settingsText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	settingsText->getTransform().setPosition(glm::vec3(0.41f, -1.05f - 0.8f, 0.0f));
	settingsText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	settingsText->addColliderComponent();
	settingsText->setMenuState(MenuState::MAIN);
	/*settingsText->setDrawCollider(true);
	settingsText->setCanDrawColliderNew(true);*/
	objectsList.push_back(settingsText);

	UIButton* settingsButton = new UIButton("Settings Button");
	//settingsButton->setTexture("../Resource/Texture/UI/UIButton.png");
	settingsButton->getTransform().setPosition(glm::vec3(0.0f, -0.81f - 0.8f, 0.0f));
	settingsButton->getTransform().setScale(glm::vec3(1.3f, 0.35f, 0.0f));
	settingsButton->addColliderComponent();
	settingsButton->setDrawCollider(true);
	settingsButton->setCanDrawColliderNew(false);
	settingsButton->setDraw(false);
	settingsButton->setLabel(settingsText); // Link playText
	settingsButton->setMenuState(MenuState::MAIN);
	settingsButton->setFunction([this]() { changeMenuState(MenuState::OPTIONS);});
	objectsList.push_back(settingsButton);
	buttonsList.push_back(settingsButton);

	mainButtons.push_back(settingsButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Credits Button
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* creditsText = new UIText("Credits Text");
	SDL_Color creditsTextColor = { 255,255,255,255 };
	creditsText->loadText("Credits", creditsTextColor, 100);
	creditsText->setText("Credits");
	creditsText->setAlpha(1.0f);
	creditsText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	creditsText->getTransform().setPosition(glm::vec3(0.45f, -1.58f - 0.9f, 0.0f));
	creditsText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	creditsText->addColliderComponent();
	creditsText->setMenuState(MenuState::MAIN);
	/*creditsText->setDrawCollider(true);
	creditsText->setCanDrawColliderNew(true);*/
	objectsList.push_back(creditsText);

	UIButton* creditsButton = new UIButton("Credits Button");
	//creditsButton->setTexture("../Resource/Texture/UI/UIButton.png");
	creditsButton->getTransform().setPosition(glm::vec3(0.0f, -1.34f - 0.9f, 0.0f));
	creditsButton->getTransform().setScale(glm::vec3(1.2f, 0.35f, 0.0f));
	creditsButton->addColliderComponent();
	creditsButton->setDrawCollider(true);
	creditsButton->setCanDrawColliderNew(false);
	creditsButton->setDraw(false);
	creditsButton->setLabel(creditsText); // Link playText
	creditsButton->setMenuState(MenuState::MAIN);
	creditsButton->setFunction([this]() { changeMenuState(MenuState::CREDITS);});
	objectsList.push_back(creditsButton);
	buttonsList.push_back(creditsButton);

	mainButtons.push_back(creditsButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Quit Button
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* quitText = new UIText("Quit Text");
	SDL_Color quitTextColor = { 255,255,255,255 };
	quitText->loadText("Quit", quitTextColor, 100);
	quitText->setText("Quit");
	quitText->setAlpha(1.0f);
	quitText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	quitText->getTransform().setPosition(glm::vec3(0.14f, -2.1f - 1.0f, 0.0f));
	quitText->getTransform().setScale(glm::vec3(1.0f, 1.0f, 0.0f));
	quitText->addColliderComponent();
	quitText->setMenuState(MenuState::MAIN);
	/*quitText->setDrawCollider(true);
	quitText->setCanDrawColliderNew(true);*/
	objectsList.push_back(quitText);

	UIButton* quitButton = new UIButton("Quit Button");
	//creditsButton->setTexture("../Resource/Texture/UI/UIButton.png");
	quitButton->getTransform().setPosition(glm::vec3(0.0f, -1.85f - 1.0f, 0.0f));
	quitButton->getTransform().setScale(glm::vec3(0.8f, 0.35f, 0.0f));
	quitButton->addColliderComponent();
	quitButton->setDrawCollider(true);
	quitButton->setCanDrawColliderNew(false);
	quitButton->setDraw(false);
	quitButton->setLabel(quitText); // Link playText
	quitButton->setMenuState(MenuState::MAIN);
	quitButton->setFunction([this]() { quitGame();});
	objectsList.push_back(quitButton);
	buttonsList.push_back(quitButton);

	mainButtons.push_back(quitButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Audio Button (Settings)
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* audioText = new UIText("Audio Text");
	SDL_Color audioTextColor = { 255,255,255,255 };
	audioText->loadText("Audio", audioTextColor, 100);
	audioText->setText("Audio");
	audioText->setAlpha(1.0f);
	audioText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	audioText->getTransform().setPosition(glm::vec3(-5.5f, 2.15f, 0.0f));
	audioText->getTransform().setScale(glm::vec3(1.0f, 1.0f, 0.0f));
	audioText->addColliderComponent();
	audioText->setMenuState(MenuState::OPTIONS);
	/*audioText->setDrawCollider(true);
	audioText->setCanDrawColliderNew(true);*/
	objectsList.push_back(audioText);

	UIButton* audioButton = new UIButton("Audio Button");
	//audioButton->setTexture("../Resource/Texture/UI/UIButton.png");
	audioButton->getTransform().setPosition(glm::vec3(-5.5f, 2.4f, 0.0f));
	audioButton->getTransform().setScale(glm::vec3(1.0f, 0.35f, 0.0f));
	audioButton->addColliderComponent();
	audioButton->setDrawCollider(true);
	audioButton->setCanDrawColliderNew(false);
	audioButton->setDraw(false);
	audioButton->setLabel(audioText); // Link playText
	audioButton->setMenuState(MenuState::OPTIONS);
	audioButton->setFunction([this]() { changeMenuState(MenuState::AUDIO);});
	objectsList.push_back(audioButton);
	buttonsList.push_back(audioButton);

	optionsButtons.push_back(audioButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Controller Button (Settings)
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* controllerText = new UIText("Controller Text");
	SDL_Color controllerTextColor = { 255,255,255,255 };
	controllerText->loadText("Controller", controllerTextColor, 100);
	controllerText->setText("Controller");
	controllerText->setAlpha(1.0f);
	controllerText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	controllerText->getTransform().setPosition(glm::vec3(-5.0f, 1.5f, 0.0f));
	controllerText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	controllerText->addColliderComponent();
	controllerText->setMenuState(MenuState::OPTIONS);
	/*controllerText->setDrawCollider(true);
	controllerText->setCanDrawColliderNew(true);*/
	objectsList.push_back(controllerText);

	UIButton* controllerButton = new UIButton("Controller Button");
	//controllerButton->setTexture("../Resource/Texture/UI/UIButton.png");
	controllerButton->getTransform().setPosition(glm::vec3(-5.2f, 1.75f, 0.0f));
	controllerButton->getTransform().setScale(glm::vec3(1.6f, 0.35f, 0.0f));
	controllerButton->addColliderComponent();
	controllerButton->setDrawCollider(true);
	controllerButton->setCanDrawColliderNew(false);
	controllerButton->setDraw(false);
	controllerButton->setLabel(controllerText); // Link playText
	controllerButton->setMenuState(MenuState::OPTIONS);
	controllerButton->setFunction([this]() { changeMenuState(MenuState::CONTROLLER);});
	objectsList.push_back(controllerButton);
	buttonsList.push_back(controllerButton);

	optionsButtons.push_back(controllerButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Keyboard Button (Settings)
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UIText* keyboardText = new UIText("Keyboard Text");
	SDL_Color keyboardTextColor = { 255,255,255,255 };
	keyboardText->loadText("Keyboard", keyboardTextColor, 100);
	keyboardText->setText("Keyboard");
	keyboardText->setAlpha(1.0f);
	keyboardText->setOffset(glm::vec3(0.0f, 0.0f, 0.0f));
	keyboardText->getTransform().setPosition(glm::vec3(-5.0f, 0.85f, 0.0f));
	keyboardText->getTransform().setScale(glm::vec3(2.0f, 1.0f, 0.0f));
	keyboardText->addColliderComponent();
	keyboardText->setMenuState(MenuState::OPTIONS);
	/*keyboardText->setDrawCollider(true);
	keyboardText->setCanDrawColliderNew(true);*/
	objectsList.push_back(keyboardText);

	UIButton* keyboardButton = new UIButton("Keyboard Button");
	//keyboardButton->setTexture("../Resource/Texture/UI/UIButton.png");
	keyboardButton->getTransform().setPosition(glm::vec3(-5.25f, 1.1f, 0.0f));
	keyboardButton->getTransform().setScale(glm::vec3(1.5f, 0.35f, 0.0f));
	keyboardButton->addColliderComponent();
	keyboardButton->setDrawCollider(true);
	keyboardButton->setCanDrawColliderNew(false);
	keyboardButton->setDraw(false);
	keyboardButton->setLabel(keyboardText); // Link playText
	keyboardButton->setMenuState(MenuState::OPTIONS);
	keyboardButton->setFunction([this]() { changeMenuState(MenuState::KEYBOARD);});
	objectsList.push_back(keyboardButton);
	buttonsList.push_back(keyboardButton);

	optionsButtons.push_back(keyboardButton);

	TexturedObject* textMes = new TexturedObject("Intro");
	textMes->setTexture("../Resource/Texture/IntroScreen.png");
	textMes->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	textMes->setMenuState(MenuState::IGNORE);
	textMes->setAlpha(0.0f);
	textMes->drawLayer = 1;
	objectsList.push_back(textMes);
	TextMessage = textMes;
	newGameTransitionTime = 0.0f;
	newGameTransitioning = false;
	newGameTransitioningComplete = false;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										Black Fading Transition
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TexturedObject* blackFade_ = new TexturedObject("Black Fade");
	blackFade_->setTexture("../Resource/Texture/blackFade.png");
	blackFade_->getTransform().setScale(glm::vec3(1.6f * 10, 0.9f * 10, 1.0f));
	blackFade_->setMenuState(MenuState::IGNORE);
	objectsList.push_back(blackFade_);
	blackFade = blackFade_;
	blackFade->setAlpha(1.0f);
	firstStart = true;

	SoundManager::GetInstance()->PlayMusic("MainMenu-SoundTrack");

	isHolding = false;
	//GameEngine::getInstance()->freezeGameForSecond(1.6f);
}

void LevelMainMenu::levelUpdate() {
	dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	timeK += dt;

	if (newGameTransitioning) {
		newGameTransitionTime += dt;
		float t = newGameTransitionTime / newGameTransitionDurationFirst;

		TextMessage->setAlpha(t);
		blackFade->setAlpha(t);

		if (newGameTransitionTime >= newGameTransitionDurationSecond) {
			newGameTransitioningComplete = true;
			newGameTransitioning = false;
			newGameTransitionTime = 0.0f;
			newGame();
		}

		selectedIndex = -1;
		focusedButton = nullptr;

		cout << "in" << endl;

		return;
	}

	cout << "out" << endl;

	updateObjects(objectsList);

	static float soundElapsed = 0.0f;
	float soundTimer = 2.0f;
	soundElapsed += dt;

	if (soundElapsed >= soundTimer) {
		soundElapsed -= soundTimer;
		//SoundManager::GetInstance()->playSoundEffectByName("Dante-Sword_LightAttack-1.wav");
	}

	if (!fileExists("../Resource/Saves/PlayerData/playerGameState.txt")) {
		continueButton->setActive(false);
	}

	if (firstStart) {
		blackFadeTransitionTime += dt;
		float t = blackFadeTransitionTime / blackFadeTransitionDuration;
		bool finishBlackFade = false;
		if (t >= 1.0f) {
			t = 1.0f;
			finishBlackFade = true;
		}

		blackFade->setAlpha(1.0f - t);

		if (finishBlackFade) {
			firstStart = false;
		}
	}


	bool anyButtonHovered = false;
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	list<UIButton*>* currentList = nullptr;

	switch (currentMenuState) {
	case MenuState::MAIN:
		currentList = &mainButtons;
		break;
	case MenuState::OPTIONS:
		currentList = &optionsButtons;
		break;
	case MenuState::AUDIO:
		currentList = &audioButtons;
		break;
	case MenuState::CONTROLLER:
		currentList = &controllerButtons;
		break;
	case MenuState::KEYBOARD:
		currentList = &keyboardButtons;
		break;
	case MenuState::CREDITS:
		currentList = &creditsButton;
		break;
	default:
		return;
	}

	int index = 0; 
	for (auto it = currentList->begin(); it != currentList->end(); ++it, ++index) {
		UIButton* button = *it;
		bool isHovered = button->isHovered(mouseX, mouseY);

		if (selectedIndex != index) {
			button->setMouseOver(isHovered);
		}

		if (isHovered) {
			hoveredIndex = index;  
			selectedIndex = hoveredIndex;
			anyButtonHovered = true;
		}
	}

	// Handle control source switching
	if (anyButtonHovered) {
		controlByMouse = true;
	}
	else {
		hoveredIndex = -1;

		if (controlByMouse) {
			focusedButton = nullptr;
			controlByMouse = false;
			selectedIndex = -1;
		}
	}


	for (DrawableObject* obj : objectsList) {
		UIText* text = dynamic_cast<UIText*>(obj);
		if (text) {
			text->update(dt);
		}

		UIButton* button = dynamic_cast<UIButton*>(obj);
		if (button) {
			button->update(dt);
		}

		if (obj->getName() == "Background") {
			//cout << obj->getName() << "'s Alpha:" << obj->getAlpha() << endl;
		}
	}

	if (transitioning) {
		transitionTime += dt;
		float t = transitionTime / transitionDuration;
		bool finish = false;
		if (t >= 1.0f) {
			t = 1.0f;
			finish = true;
		}

		for (DrawableObject* obj : objectsList) {
			MenuState objState = obj->getMenuState();
			vector<MenuState> objStateVec = obj->getMenuStateVec();

			if (find(objStateVec.begin(), objStateVec.end(), MenuState::IGNORE) != objStateVec.end()) {
				UIButton* button = dynamic_cast<UIButton*>(obj);
				if (button) {
					button->setEnable(true);
				}
				continue;
			}

			if (find(objStateVec.begin(), objStateVec.end(), MenuState::NONE) != objStateVec.end()) {
				obj->setAlpha(1.0f);
				continue;
			}

			bool inCurrent = objState == currentMenuState ||
				find(objStateVec.begin(), objStateVec.end(), currentMenuState) != objStateVec.end();
			bool inNext = objState == nextMenuState ||
				find(objStateVec.begin(), objStateVec.end(), nextMenuState) != objStateVec.end();
			
			if (inCurrent && inNext) { //If the object has many states.
				obj->setAlpha(1.0f);
			}
			else if (inCurrent) {
				obj->setAlpha(1.0f - t);
			}
			else if (inNext) {
				obj->setAlpha(t);
			}
			else {
				obj->setAlpha(0.0f);
			}
		}

		if (finish) {
			transitioning = false;
			currentMenuState = nextMenuState;
		}
	}
	else {
		for (DrawableObject* obj : objectsList) {
			MenuState objState = obj->getMenuState();
			vector<MenuState> objStateVec = obj->getMenuStateVec();

			if (find(objStateVec.begin(), objStateVec.end(), MenuState::IGNORE) != objStateVec.end()) {
				UIButton* button = dynamic_cast<UIButton*>(obj);
				if (button) {
					button->setEnable(true);
				}
				continue;
			}

			if (find(objStateVec.begin(), objStateVec.end(), MenuState::NONE) != objStateVec.end()) {//Doesn't affect by any states
				obj->setAlpha(1.0f);
				continue;
			}

			bool inCurrent = objState == currentMenuState ||
				find(objStateVec.begin(), objStateVec.end(), currentMenuState) != objStateVec.end();

			obj->setAlpha(inCurrent ? 1.0f : 0.0f);

			/*if (inCurrent) {
				cout << obj->getName() << "'s MenuState:" << obj->getMenuState() << " Alpha:" << obj->getAlpha() << endl;
				for (auto o : obj->getMenuStateVec()) {
					cout << o << endl;
				}
			}*/
			
			UIButton* button = dynamic_cast<UIButton*>(obj);

			if (button) {
				button->setEnable(inCurrent ? true : false);
			}
		}
	}

	for (SliderObject* obj : slidersList) {
		obj->update(dt);

		if (SoundManager::GetInstance()) {
			if (obj == masterSlider) {
				SoundManager::GetInstance()->setMasterVolume(masterSlider->getValue());
			}
			else if (obj == musicSlider) {
				SoundManager::GetInstance()->setMusicVolume(musicSlider->getValue());
			}
			else if (obj == sfxSlider) {
				SoundManager::GetInstance()->setSoundEffectVolume(sfxSlider->getValue());
			}
			else if (obj == ambientSlider) {
				SoundManager::GetInstance()->setAmbientVolume(ambientSlider->getValue());
			}
		}
	}

	InputManager* inputManager = GameEngine::getInstance()->getInputHandler();

	if (inputManager) {
		if (inputManager->getLastInput() == InputDevice::KEYBOARD) {
			kbOverlay->setDraw(true);
			controllerOverlay->setDraw(false);
		}
		else {
			kbOverlay->setDraw(false);
			controllerOverlay->setDraw(true);
		}
	}
	

	//cout << "SelectedIndex: " << selectedIndex << " HoveredIndex: " << hoveredIndex << endl;

	//handleObjectCollision(objectsList);

}

void LevelMainMenu::levelDraw() {
	GameEngine::getInstance()->render(objectsList);
}

void LevelMainMenu::levelFree() {
	
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}

	for (SliderObject*& obj : slidersList) {
		delete obj;
	}

	for (UIButton*& button : buttonsList) {
		button = nullptr;
	}

	for (UIButton*& button : mainButtons) {
		button = nullptr;
	}

	for (UIButton*& button : optionsButtons) {
		button = nullptr;
	}

	for (UIButton*& button : audioButtons) {
		button = nullptr;
	}

	for (UIButton*& button : controllerButtons) {
		button = nullptr;
	}

	for (UIButton*& button : keyboardButtons) {
		button = nullptr;
	}

	for (UIButton*& button : creditsButton) {
		button = nullptr;
	}

	slidersList.clear();
	objectsList.clear();
	buttonsList.clear();
	mainButtons.clear();
	optionsButtons.clear();
	audioButtons.clear();
	controllerButtons.clear();
	keyboardButtons.clear();
	creditsButton.clear();
}

void LevelMainMenu::levelUnload() {
	GameEngine::getInstance()->clearMesh();
}

void LevelMainMenu::isReceivingNoInputs() {
	
}

void LevelMainMenu::handleKey(char key) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();
	
	list<UIButton*>* currentList = nullptr;

	switch (currentMenuState) {
	case MenuState::MAIN:
		currentList = &mainButtons;
		break;
	case MenuState::OPTIONS:
		currentList = &optionsButtons;
		break;
	case MenuState::AUDIO:
		currentList = &audioButtons;
		break;
	case MenuState::CONTROLLER:
		currentList = &controllerButtons;
		break;
	case MenuState::KEYBOARD:
		currentList = &keyboardButtons;
		break;
	case MenuState::CREDITS:
		currentList = &creditsButton;
		break;
	default:
		return;
	}

	/*UIButton* selectedButton = nullptr;

	if (selectedIndex >= 0 && selectedIndex < currentList->size()) {
		auto it = buttonsList.begin();
		std::advance(it, selectedIndex);

		selectedButton = *it;
	}*/

	/*switch (currentMenuState) {
	case MAIN:
		switch (key) {
		case 'w':
			changeSelection(-1);
			break;
		case 's':
			changeSelection(1);
			break;
		case 'S':
			if (selectedButton && selectedButton->getMouseOver()) {
				selectedButton->OnClick();
			}
			break;
		}
		break;
	case OPTIONS:

		break;
	case AUDIO:
		break;
	case CONTROLS:
		break;
	case CREDITS:
		break;
	default:
		break;
	}*/

	switch (key) {
	case 'r': GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART; ; break;
	case 'a':
		if (isHolding == false) {
			if (focusedButton) {
				SliderObject* slider = focusedButton->getSlider();
				if (slider) {
					slider->setValue(slider->getValue() - 0.025f);
				}
			}
			isHolding = true;
		}

		if (isHolding == true) {
			holdButtonTimer += dt;
			if (holdButtonTimer >= holdButtonThreshold) {
				if (focusedButton) {
					SliderObject* slider = focusedButton->getSlider();
					if (slider) {
						slider->setValue(slider->getValue() - 0.005f);
					}
				}
			}
		}

		
		break;
	case 'd':

		if (isHolding == false){
			if (focusedButton) {
				SliderObject* slider = focusedButton->getSlider();
				if (slider) {
					slider->setValue(slider->getValue() + 0.025f);
				}
			}
			isHolding = true;
		}

		if (isHolding == true) {
			holdButtonTimer += dt;
			if (holdButtonTimer >= holdButtonThreshold) {
				if (focusedButton) {
					SliderObject* slider = focusedButton->getSlider();
					if (slider) {
						slider->setValue(slider->getValue() + 0.005f);
					}
				}
			}
		}

		
		break;
	case 'w':
		changeSelection(-1);
		break;
	case 's':
		changeSelection(1);
		break;
	case 'q':
		if (currentMenuState == OPTIONS) {
			changeMenuState(MenuState::MAIN);
		}
		else if (currentMenuState == AUDIO) {
			changeMenuState(MenuState::OPTIONS);
		}
		else if (currentMenuState == CONTROLLER) {
			changeMenuState(MenuState::OPTIONS);
		}
		else if (currentMenuState == KEYBOARD) {
			changeMenuState(MenuState::OPTIONS);
		}
		else if (currentMenuState == CREDITS) {
			changeMenuState(MenuState::MAIN);
		}
		break;
	case 'S':
		/*if (selectedButton && selectedButton->getMouseOver()) {
			selectedButton->OnClick();
		}*/

		if (focusedButton && focusedButton->getMouseOver()) {
			focusedButton->OnClick();
			SoundManager::GetInstance()->PlaySFX("Misc-ButtonClick");
		}

		break;
	case 'I':
		if (isHolding == true) {
			isHolding = false;
		}
		if (holdButtonTimer > 0){
			holdButtonTimer = 0;
		}
		break;
	}
}

void LevelMainMenu::handleControllerButton(SDL_GameControllerButton button) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();

	bool input = false;

	list<UIButton*>* currentList = nullptr;

	switch (currentMenuState) {
	case MenuState::MAIN:
		currentList = &mainButtons;
		break;
	case MenuState::OPTIONS:
		currentList = &optionsButtons;
		break;
	case MenuState::AUDIO:
		currentList = &audioButtons;
		break;
	case MenuState::CONTROLLER:
		currentList = &controllerButtons;
		break;
	case MenuState::KEYBOARD:
		currentList = &keyboardButtons;
		break;
	case MenuState::CREDITS:
		currentList = &creditsButton;
		break;
	default:
		return;
	}

	switch (button) {
	case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
		if (isHolding == false) {
			if (focusedButton) {
				SliderObject* slider = focusedButton->getSlider();
				if (slider) {
					slider->setValue(slider->getValue() - 0.025f);
				}
			}
			isHolding = true;
			input = true;
		}

		if (isHolding == true) {
			holdButtonTimer += dt;
			if (holdButtonTimer >= holdButtonThreshold) {
				if (focusedButton) {
					SliderObject* slider = focusedButton->getSlider();
					if (slider) {
						slider->setValue(slider->getValue() - 0.005f);
					}
				}
			}
			input = true;
		}


		break;
	case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:

		if (isHolding == false) {
			if (focusedButton) {
				SliderObject* slider = focusedButton->getSlider();
				if (slider) {
					slider->setValue(slider->getValue() + 0.025f);
				}
			}
			isHolding = true;
			input = true;
		}

		if (isHolding == true) {
			holdButtonTimer += dt;
			if (holdButtonTimer >= holdButtonThreshold) {
				if (focusedButton) {
					SliderObject* slider = focusedButton->getSlider();
					if (slider) {
						slider->setValue(slider->getValue() + 0.005f);
					}
				}
			}
			input = true;
		}


		break;
	case SDL_CONTROLLER_BUTTON_DPAD_UP:
		changeSelection(-1);
		input = true;
		break;
	case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
		changeSelection(1);
		input = true;
		break;
	case SDL_CONTROLLER_BUTTON_B:
		if (currentMenuState == OPTIONS) {
			changeMenuState(MenuState::MAIN);
		}
		else if (currentMenuState == AUDIO) {
			changeMenuState(MenuState::OPTIONS);
		}
		else if (currentMenuState == CONTROLLER) {
			changeMenuState(MenuState::OPTIONS);
		}
		else if (currentMenuState == KEYBOARD) {
			changeMenuState(MenuState::OPTIONS);
		}
		else if (currentMenuState == CREDITS) {
			changeMenuState(MenuState::MAIN);
		}
		input = true;
		break;
	case SDL_CONTROLLER_BUTTON_A:
		/*if (selectedButton && selectedButton->getMouseOver()) {
			selectedButton->OnClick();
		}*/

		if (focusedButton && focusedButton->getMouseOver()) {
			focusedButton->OnClick();
			SoundManager::GetInstance()->PlaySFX("Misc-ButtonClick");
			input = true;
		}

		break;
	}
	

	if (!input) {
		if (isHolding == true) {
			isHolding = false;
		}
		if (holdButtonTimer > 0) {
			holdButtonTimer = 0;
		}
	}
}


void LevelMainMenu::handleMouse(int type, int x, int y) {
	float realX, realY;

	// Calculate Real X Y 
	realX = x;
	realY = y;

	GameEngine::getInstance()->getWindowWidth();
	GameEngine::getInstance()->getWindowHeight();

	//cout << "X : " << realX << " Y : " << realY << endl;

	/*for (UIButton* button : buttonsList) {
		if (button->getMouseOver()) {
			if (type == 0) {
				GameEngine::getInstance()->getStateController()->gameStateNext = GameState::GS_RESTART;
			}
		}
	}*/

	list<UIButton*>* currentList = nullptr;

	switch (currentMenuState) {
	case MenuState::MAIN:
		currentList = &mainButtons;
		break;
	case MenuState::OPTIONS:
		currentList = &optionsButtons;
		if (type == 1) {
			changeMenuState(MenuState::MAIN);
		}
		break;
	case MenuState::AUDIO:
		currentList = &audioButtons;
		if (type == 1) {
			changeMenuState(MenuState::OPTIONS);
		}
		break;   
	case MenuState::CONTROLLER:
		currentList = &controllerButtons;
		if (type == 1) {
			changeMenuState(MenuState::OPTIONS);
		}
		break;
	case MenuState::KEYBOARD:
		currentList = &keyboardButtons;
		if (type == 1) {
			changeMenuState(MenuState::OPTIONS);
		}
		break;
	case MenuState::CREDITS:
		currentList = &creditsButton;
		if (type == 1) {
			changeMenuState(MenuState::MAIN);
		}
		break;
	default:
		return;
	}


	if (selectedIndex >= 0 && selectedIndex < currentList->size()) {
		auto it = currentList->begin();
		std::advance(it, selectedIndex);

		UIButton* onButton = *it;

		if (onButton && onButton->getMouseOver()) {
			if (type == 0) {
				onButton->OnClick();
				if (onButton->getHandle()) {
					focusedHandle = *it;
				}
				else {
					SoundManager::GetInstance()->PlaySFX("Misc-ButtonClick");
				}
			}
		}
	}

	if (focusedHandle) {
		//cout << focusedHandle->getName() << endl;
		if (type == 2) {
			focusedHandle = nullptr;
		}

		if (type == 4) {

			SliderObject* handleSlider = focusedHandle->getSlider();

			if (handleSlider) {
				//cout << "has slider" << endl;
			}

			glm::vec2 gamePos = convertMouseToGameSpace(x, y);

			for (SliderObject* slider : slidersList) {

				if (focusedHandle->getSlider() == slider) {
					//cout << "Button's Slider: " << focusedHandle->getSlider()->getName() << " Slider:" << slider->getName() << endl;

					glm::vec3 handlePos = slider->getObject(2)->getTransform().getPosition(); // 2 = handle
					glm::vec3 bgPos = slider->getObject(0)->getTransform().getPosition(); // 0 = background

					float sliderLeft = bgPos.x - slider->getOriginalWidth().x * 0.5f;
					float sliderRight = bgPos.x + slider->getOriginalWidth().x * 0.5f;

					//cout << "Mouse Pos: " << gamePos.x << "," << gamePos.y << "Slider X Left:" << sliderLeft << ", Slider X Right:" << sliderRight << endl;


					if (gamePos.x <= sliderLeft) {
						slider->setValue(0.0f);
					}
					else if (gamePos.x >= sliderRight) {
						slider->setValue(1.0f);
					}
					else if (gamePos.x >= sliderLeft && gamePos.x <= sliderRight) {
						float newValue = (gamePos.x - sliderLeft) / (sliderRight - sliderLeft);
						slider->setValue(newValue);
					}
					slider->update(dt);
				}
			}
		}
	}
}

void LevelMainMenu::handleAnalogStick(int type, char key) {
	float dt = GameEngine::getInstance()->getTime()->getDeltaTime();


}

void LevelMainMenu::addObject(DrawableObject* obj) {
	objectsList.push_back(obj);
}

void LevelMainMenu::changeMenuState(MenuState targetState) {
	if (targetState == currentMenuState || transitioning) return;

	selectedIndex = -1;

	nextMenuState = targetState;
	transitionTime = 0.0f;
	transitioning = true;
}

MenuState LevelMainMenu::getMenuState() const {
	return currentMenuState;
}

void LevelMainMenu::changeSelection(int direction) {

	list<UIButton*>* currentList = nullptr;

	switch (currentMenuState) {
	case MenuState::MAIN:
		currentList = &mainButtons;
		break;
	case MenuState::OPTIONS:
		currentList = &optionsButtons;
		break;
	case MenuState::AUDIO:
		currentList = &audioButtons;
		break;
	case MenuState::CONTROLLER:
		currentList = &controllerButtons;
		break;
	case MenuState::KEYBOARD:
		currentList = &keyboardButtons;
		break;
	case MenuState::CREDITS:
		currentList = &creditsButton;
		break;
	default:
		return;
	}


	if (!currentList || currentList->empty()) {
		return;
	}

	for (UIButton* btn : buttonsList) { // Deselect
		btn->setMouseOver(false);
	}

	if (selectedIndex == -1) {
		selectedIndex = 0;
	}
	else {
		selectedIndex += direction;
	}

	if (selectedIndex < 0) {
		selectedIndex = currentList->size() - 1;
	}
	else if (selectedIndex >= currentList->size()) {
		selectedIndex = 0;
	}

	auto it = currentList->begin();
	advance(it, selectedIndex);

	focusedButton = *it;

	if (!focusedButton->getEnable()) {
		selectedIndex += direction;
	}

	if (focusedButton->getHandle()) {
		selectedIndex += direction;
	}

	if (selectedIndex < 0) {
		selectedIndex = currentList->size() - 1;
	}
	else if (selectedIndex >= currentList->size()) {
		selectedIndex = 0;
	}

	it = currentList->begin();	
	advance(it, selectedIndex);

	focusedButton = *it;
	focusedButton->setMouseOver(true);
	//cout << focusedButton->getName() << endl;
}

glm::vec2 LevelMainMenu::convertMouseToGameSpace(int mouseX, int mouseY) {
	int windowWidth = GameEngine::getInstance()->getWindowWidth();
	int windowHeight = GameEngine::getInstance()->getWindowHeight();

	const float targetAspect = 16.0f / 9.0f;
	float windowAspect = static_cast<float>(windowWidth) / windowHeight;

	float gameWidth = 16.0f;
	float gameHeight = 9.0f;

	float scale;
	float offsetX = 0;
	float offsetY = 0;

	if (windowAspect > targetAspect) {
		// Black bars on left/right
		scale = windowHeight / gameHeight;
		offsetX = (windowWidth - gameWidth * scale) / 2.0f;
	}
	else {
		// Black bars on top/bottom
		scale = windowWidth / gameWidth;
		offsetY = (windowHeight - gameHeight * scale) / 2.0f;
	}

	// Convert to normalized game coordinates
	float gameX = (mouseX - offsetX) / scale;
	float gameY = (mouseY - offsetY) / scale;

	// Flip Y if window origin is top-left but game origin is center
	gameY = gameHeight - gameY;

	// Shift origin to center
	gameX -= gameWidth / 2.0f;
	gameY -= gameHeight / 2.0f;

	return glm::vec2(gameX, gameY);
}