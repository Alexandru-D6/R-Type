#include "MainMenuScene.h"
#include "Game.h"
#include "GeneralDefines.h"

MainMenuScene::MainMenuScene() {
    map = NULL;
    button = NULL;
}

MainMenuScene::~MainMenuScene() {
    if (map != NULL)
        delete map;
    if (button != NULL)
        delete button;
}


void MainMenuScene::init() {
    // 256.0f is the amount of pixel that has the map as height, it may need a rework to get that value directly from level.txt
    projection = glm::ortho(0.f, float((SCREEN_WIDTH / float(SCREEN_HEIGHT / 256.0f)) - 1), float((SCREEN_HEIGHT / float(SCREEN_HEIGHT / 256.0f)) - 1), 0.f);
    currentTime = 0.0f;

    map = TileMap::createTileMap("levels/MainMenu.txt", glm::vec2(SCREEN_X, SCREEN_Y), &projection);

}

void MainMenuScene::update(int deltaTime) {
    currentTime += deltaTime;
}

void MainMenuScene::render() {
    map->render();
    button->render();
}
