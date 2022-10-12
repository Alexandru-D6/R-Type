#include "UI_Button.h"
#include "Game.h"
#include "GeneralDefines.h"

UI_Button::UI_Button(glm::mat4 *project) {
    projection = project;
}

void UI_Button::init(const glm::ivec2 &tileMapPos, const string &spriteFile) {
    spritesheet.loadFromFile(spriteFile, TEXTURE_PIXEL_FORMAT_RGBA);

    sprite = Sprite::createSprite(glm::ivec2(32, 8), glm::vec2(1.0f, 0.5f), &spritesheet, projection);
    sprite->setNumberAnimations(4);

        sprite->setAnimationSpeed(UNSELECTED, 8);
        sprite->addKeyframe(UNSELECTED, glm::vec2(0.f, 0.f));

    sprite->changeAnimation(UNSELECTED);
    tileMapDispl = tileMapPos;

    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posButton.x), float(tileMapDispl.y + posButton.y)));
}

void UI_Button::update(int deltaTime)
{
    sprite->update(deltaTime);
 
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posButton.x), float(tileMapDispl.y + posButton.y)));
}

void UI_Button::render() {
    sprite->render();
}

void UI_Button::setPosition(const glm::vec2 &pos) {
    posButton = pos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posButton.x), float(tileMapDispl.y + posButton.y)));
}
