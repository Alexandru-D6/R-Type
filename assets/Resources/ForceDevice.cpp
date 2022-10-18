#include "ForceDevice.h"
#include "Game.h"
#include "GeneralDefines.h"

ForceDevice::ForceDevice(glm::mat4 *project) {
    projection = project;
    collider = new Collision(project, Collision::Player);

    collisionSystem = CollisionSystem::getInstance();
    collisionSystem->addColliderIntoGroup(collider);
}

void ForceDevice::init(const glm::ivec2 &tileMapPos) {
    spritesheet.loadFromFile("images/player/force-pit-beam.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spritesheet.setWrapS(GL_CLAMP_TO_EDGE);
    spritesheet.setWrapT(GL_CLAMP_TO_EDGE);
    spritesheet.setMinFilter(GL_NEAREST);
    spritesheet.setMagFilter(GL_NEAREST);

    sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0f/10.0f, 1.0f/16.0f), &spritesheet, projection);
    sprite->setNumberAnimations(3);

        int offset = 1;
        float subX = 1.0f / 10.0f;
        float subY = 1.0f / 16.0f;
        sprite->setAnimationSpeed(ForceMK1, 8);
        sprite->addKeyframe(ForceMK1, glm::vec2(subX*0, subY*offset));
        sprite->addKeyframe(ForceMK1, glm::vec2(subX*1, subY*offset));
        sprite->addKeyframe(ForceMK1, glm::vec2(subX*2, subY*offset));
        sprite->addKeyframe(ForceMK1, glm::vec2(subX*3, subY*offset));
        sprite->addKeyframe(ForceMK1, glm::vec2(subX*4, subY*offset));
        sprite->addKeyframe(ForceMK1, glm::vec2(subX*5, subY*offset));

        offset = 2;
        sprite->setAnimationSpeed(ForceMK2, 8);
        sprite->addKeyframe(ForceMK2, glm::vec2(subX * 0, subY*offset));
        sprite->addKeyframe(ForceMK2, glm::vec2(subX * 1, subY*offset));
        sprite->addKeyframe(ForceMK2, glm::vec2(subX * 2, subY*offset));
        sprite->addKeyframe(ForceMK2, glm::vec2(subX * 3, subY*offset));

        offset = 4;
        sprite->setAnimationSpeed(ForceMK3, 8);
        sprite->addKeyframe(ForceMK3, glm::vec2(subX * 0, subY*offset));
        sprite->addKeyframe(ForceMK3, glm::vec2(subX * 1, subY*offset));
        sprite->addKeyframe(ForceMK3, glm::vec2(subX * 2, subY*offset));
        sprite->addKeyframe(ForceMK3, glm::vec2(subX * 3, subY*offset));

    sprite->changeAnimation(ForceMK3);

    collider->addCollider(glm::vec4(0, 4, 16, 32-4));
    collider->changePositionAbsolute(glm::vec2(posForce.x, posForce.y));

#ifdef SHOW_HIT_BOXES
    collider->showHitBox();
#endif // SHOW_HIT_BOXES

    sprite->setPosition(glm::vec2(posForce.x, posForce.y));
}

void ForceDevice::update(int deltaTime) {
    sprite->update(deltaTime);

    sprite->setPosition(glm::vec2(posForce.x, posForce.y));
}

void ForceDevice::render() {
    sprite->render();

#ifdef SHOW_HIT_BOXES
    collider->render();
#endif // SHOW_HIT_BOXES
}

void ForceDevice::setPosition(const glm::vec2 &pos) {
    posForce = pos;
    sprite->setPosition(glm::vec2(posForce.x, posForce.y));
    collider->changePositionAbsolute(glm::vec2(posForce.x, posForce.y));
}
