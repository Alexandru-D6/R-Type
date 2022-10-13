#ifndef _MAIN_MENU_SCENE_INCLUDE
#define _MAIN_MENU_SCENE_INCLUDE

#include <glm/glm.hpp>

#include "ShaderProgram.h"
#include "TileMap.h"

#include "UI_Button.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.

class MainMenuScene {

public:

    MainMenuScene();
    ~MainMenuScene();

    void init();
    void update(int deltaTime);
    void render();

private:

    TileMap *map;
    UI_Button button;

    float currentTime;
    glm::mat4 projection;

};

#endif // _MAIN_MENU_SCENE_INCLUDE
