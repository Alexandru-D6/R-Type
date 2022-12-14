#include "LoadingScene.h"
#include "Game.h"
#include "GeneralDefines.h"

LoadingScene *LoadingScene::getLoading() {
    LoadingScene *scene = new LoadingScene();
    return scene;
}

LoadingScene::LoadingScene() {
    map = NULL;
    nextScreenName = "";
	waitingTime = 50;
}

LoadingScene::~LoadingScene() {
    if (map != NULL)
        delete map;
}

void LoadingScene::init() {
    // 256.0f is the amount of pixel that has the map as height, it may need a rework to get that value directly from level.txt
    projection = glm::ortho(0.f, float((SCREEN_WIDTH / float(SCREEN_HEIGHT / 255.0f)) - 2), float((SCREEN_HEIGHT / float(SCREEN_HEIGHT / 255.0f)) - 2), 0.f);
    currentTime = 0.0f;

    map = TileMap::createTileMap("levels/Loading.txt", glm::vec2(SCREEN_X, SCREEN_Y), &projection);

	if (!text.init("fonts/OpenSans-Bold.ttf"))
		cout << "Could not load font!!!" << endl;
}

void LoadingScene::update(int deltaTime) {
    currentTime += deltaTime;
    waitingTime -= deltaTime;
}

void LoadingScene::render() {
    map->render();

	if (waitingTime < 0 && nextScreenName == "GAME") Game::instance().changeToGame(false);
	else if (waitingTime < 0 && nextScreenName == "INSTRUCTIONS") Game::instance().changeToInstructions(false);
	else if (waitingTime < 0 && nextScreenName == "MAIN_MENU") Game::instance().changeToMainMenu(false);
    else if (waitingTime < 0 && nextScreenName == "CREDITS") Game::instance().changeToCredits(false);

	text.render("Loading...", glm::vec2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), 64, glm::vec4(1, 1, 1, 1), Text::Center);

}

void LoadingScene::buttonCallback(int id) {
    return;
}

void LoadingScene::nextScreen(string screen) {
    nextScreenName = screen;

}
