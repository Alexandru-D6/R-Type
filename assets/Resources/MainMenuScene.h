#ifndef _MAIN_MENU_SCENE_INCLUDE
#define _MAIN_MENU_SCENE_INCLUDE

#include <vector>

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

    vector<UI_Button> buttons;
    int selectedButton;

    float currentTime;
    glm::mat4 projection;

    bool latchKeys[256];

};

#endif // _MAIN_MENU_SCENE_INCLUDE
