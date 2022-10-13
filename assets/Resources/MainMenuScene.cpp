#include "MainMenuScene.h"
#include "Game.h"
#include "UI_Button.h"
#include "GeneralDefines.h"

MainMenuScene::MainMenuScene() {
    map = NULL;
    buttons = vector<UI_Button>(4);
}

MainMenuScene::~MainMenuScene() {
    if (map != NULL)
        delete map;
}


void MainMenuScene::init() {
    // 256.0f is the amount of pixel that has the map as height, it may need a rework to get that value directly from level.txt
    projection = glm::ortho(0.f, float((SCREEN_WIDTH / float(SCREEN_HEIGHT / 256.0f)) - 1), float((SCREEN_HEIGHT / float(SCREEN_HEIGHT / 256.0f)) - 1), 0.f);
    currentTime = 0.0f;

    map = TileMap::createTileMap("levels/MainMenu.txt", glm::vec2(SCREEN_X, SCREEN_Y), &projection);

    buttons[0].init(glm::ivec2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f),          "Play",         32);
    buttons[1].init(glm::ivec2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f + 50),     "Instructions", 32);
    buttons[2].init(glm::ivec2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f + 100),    "Credits",      32);
    buttons[3].init(glm::ivec2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f + 150),    "Quit Game",    32);

    buttons[selectedButton].setState(UI_Button::Selected);
}

void MainMenuScene::update(int deltaTime) {
    currentTime += deltaTime;

    for (int i = 0; i < 4; i++) buttons[i].update(deltaTime);

    if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !latchKeys[GLUT_KEY_UP]) {
        latchKeys[GLUT_KEY_UP] = true;
        buttons[selectedButton].setState(UI_Button::Unselected);

        selectedButton--;
        if (selectedButton < 0) selectedButton = buttons.size() - 1;

        buttons[selectedButton].setState(UI_Button::Selected);

    } else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !latchKeys[GLUT_KEY_DOWN]) {
        latchKeys[GLUT_KEY_DOWN] = true;
        buttons[selectedButton].setState(UI_Button::Unselected);

        selectedButton++;
        if (selectedButton >= buttons.size()) selectedButton = 0;

        buttons[selectedButton].setState(UI_Button::Selected);
    }

    if (!Game::instance().getSpecialKey(GLUT_KEY_DOWN) && latchKeys[GLUT_KEY_DOWN]) latchKeys[GLUT_KEY_DOWN] = false;
    else if (!Game::instance().getSpecialKey(GLUT_KEY_UP) && latchKeys[GLUT_KEY_UP]) latchKeys[GLUT_KEY_UP] = false;
}

void MainMenuScene::render() {
    map->render();
    for (int i = 0; i < buttons.size(); i++) buttons[i].render();
}
