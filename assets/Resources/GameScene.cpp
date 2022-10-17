#include "GameScene.h"
#include "Game.h"
#include "GeneralDefines.h"

GameScene *GameScene::getGame() {
    GameScene *scene = new GameScene();
    return scene;
}

GameScene::GameScene() {
    map = NULL;
    player = NULL;
}

GameScene::~GameScene() {
    if(map != NULL)
        delete map;
    if(player != NULL)
        delete player;
}


void GameScene::init() {
    // 256.0f is the amount of pixel that has the map as height, it may need a rework to get that value directly from level.txt
    projection = glm::ortho(0.f, float((SCREEN_WIDTH / float(SCREEN_HEIGHT / 255.0f)) - 2), float((SCREEN_HEIGHT / float(SCREEN_HEIGHT / 255.0f)) - 2), 0.f);
    currentTime = 0.0f;

    initShaders();
    map = TileMap::createTileMap("levels/level00.txt", glm::vec2(SCREEN_X, SCREEN_Y), &projection);
    player = new Player(&projection);
    player->init(glm::ivec2(SCREEN_X, SCREEN_Y));
    player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
    player->setTileMap(map);

    power1 = new PowerUp(&projection);
    power1->init(PowerUp::ModifierMBlue);
    power1->setPosition(glm::vec2(0.0,0.0));

    power2 = new PowerUp(&projection);
    power2->init(PowerUp::ModifierMRed);
    power2->setPosition(glm::vec2(16.0, 0.0));

    power3 = new PowerUp(&projection);
    power3->init(PowerUp::ModifierS);
    power3->setPosition(glm::vec2(32.0, 0.0));

    power4 = new PowerUp(&projection);
    power4->init(PowerUp::PowerUpBlack);
    power4->setPosition(glm::vec2(48.0, 0.0));

    power5 = new PowerUp(&projection);
    power5->init(PowerUp::PowerUpBlue);
    power5->setPosition(glm::vec2(64.0, 0.0));

    power6 = new PowerUp(&projection);
    power6->init(PowerUp::PowerUpGreen);
    power6->setPosition(glm::vec2(80.0, 0.0));

    power7 = new PowerUp(&projection);
    power7->init(PowerUp::PowerUpRed);
    power7->setPosition(glm::vec2(96.0, 0.0));

    power8 = new PowerUp(&projection);
    power8->init(PowerUp::PowerUpYellow);
    power8->setPosition(glm::vec2(112.0, 0.0));
}

void GameScene::update(int deltaTime) {
    currentTime += deltaTime;
    player->update(deltaTime);

    power1->update(deltaTime);
    power2->update(deltaTime);
    power3->update(deltaTime);
    power4->update(deltaTime);
    power5->update(deltaTime);
    power6->update(deltaTime);
    power7->update(deltaTime);
    power8->update(deltaTime);
}

void GameScene::render() {
    map->render();

    player->render();

    power1->render();
    power2->render();
    power3->render();
    power4->render();
    power5->render();
    power6->render();
    power7->render();
    power8->render();
}

void GameScene::initShaders() {
    Shader vShader, fShader;

    vShader.initFromFile(VERTEX_SHADER, "shaders/level-obstacles.vert");
    if(!vShader.isCompiled())
    {
        cout << "Vertex Shader Error" << endl;
        cout << "" << vShader.log() << endl << endl;
    }
    fShader.initFromFile(FRAGMENT_SHADER, "shaders/level-obstacles.frag");
    if(!fShader.isCompiled())
    {
        cout << "Fragment Shader Error" << endl;
        cout << "" << fShader.log() << endl << endl;
    }
    texProgram.init();
    texProgram.addShader(vShader);
    texProgram.addShader(fShader);
    texProgram.link();
    if(!texProgram.isLinked())
    {
        cout << "Shader Linking Error" << endl;
        cout << "" << texProgram.log() << endl << endl;
    }
    texProgram.bindFragmentOutput("outColor");
    vShader.free();
    fShader.free();
}
