#ifndef _UI_BUTTON_INCLUDE
#define _UI_BUTTON_INCLUDE

#include "Sprite.h"

#include "GeneralDefines.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.
class UI_Button {

public:

    enum ButtonState { UNSELECTED, SELECTED, CLICKED };

public:

    UI_Button(glm::mat4 *project);

    void init(const glm::ivec2 &tileMapPos, const string &spriteFile);
    void update(int deltaTime);
    void render();

    void setPosition(const glm::vec2 &pos);

private:

    glm::ivec2 tileMapDispl, posButton;
    Texture spritesheet;
    Sprite *sprite;

    glm::mat4 *projection;

};

#endif // _UI_BUTTON_INCLUDE
