#include "Player.h"
#include "Game.h"
#include "GeneralDefines.h"

Player::Player(glm::mat4 *project) {
    projection = project;
    collider = new Collision(project, Collision::Player);

    collisionSystem = CollisionSystem::getInstance();
    collisionSystem->addColliderIntoGroup(collider);
}

void Player::init(const glm::ivec2 &tileMapPos) {
    bJumping = false;
    spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, projection);
    sprite->setNumberAnimations(4);

        sprite->setAnimationSpeed(STAND_LEFT, 8);
        sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

        sprite->setAnimationSpeed(STAND_RIGHT, 8);
        sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));

        sprite->setAnimationSpeed(MOVE_LEFT, 8);
        sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
        sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
        sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

        sprite->setAnimationSpeed(MOVE_RIGHT, 8);
        sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
        sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
        sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));

    sprite->changeAnimation(0);
    tileMapDispl = tileMapPos;

    collider->addCollider(glm::ivec4(0, 0, 27, 32));
    collider->changePositionAbsolute(glm::ivec2(tileMapDispl.x + posPlayer.x, tileMapDispl.y + posPlayer.y));

#ifdef SHOW_HIT_BOXES
    collider->showHitBox();
#endif // SHOW_HIT_BOXES

    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

    forceDevice = new ForceDevice(projection);
    forceDevice->init(glm::ivec2(SCREEN_X, SCREEN_Y));
    forceDevice->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)), true);
}

void Player::update(int deltaTime)
{
    sprite->update(deltaTime);
    if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
        if(sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);

        if (collisionSystem->isColliding(Player::collider, glm::ivec2(-2, 0)) || collisionSystem->isColliding(forceDevice->getCollider(), glm::ivec2(-2, 0))) {
            sprite->changeAnimation(STAND_LEFT);
        } else {
            posPlayer.x -= 2;
            collider->changePositionRelative(glm::vec2(-2, 0));
            //map->moveMap(2);
        }
    }
    else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
        if(sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);

        if(collisionSystem->isColliding(Player::collider, glm::ivec2(2, 0)) || collisionSystem->isColliding(forceDevice->getCollider(), glm::ivec2(2, 0))) {
            sprite->changeAnimation(STAND_RIGHT);
        } else {
            posPlayer.x += 2;
            collider->changePositionRelative(glm::vec2(2, 0));
            //map->moveMap(-2);
        }
    }
    else {
        if(sprite->animation() == MOVE_LEFT)
            sprite->changeAnimation(STAND_LEFT);
        else if(sprite->animation() == MOVE_RIGHT)
            sprite->changeAnimation(STAND_RIGHT);
    }

    if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
        if (!(collisionSystem->isColliding(Player::collider, glm::ivec2(0, 2)) || collisionSystem->isColliding(forceDevice->getCollider(), glm::ivec2(0, 2)))) {
            posPlayer.y += 2;
            collider->changePositionRelative(glm::vec2(0, 2));
        }
    }else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
        if (!(collisionSystem->isColliding(Player::collider, glm::vec2(0, -2)) || collisionSystem->isColliding(forceDevice->getCollider(), glm::ivec2(0, -2)))) {
            posPlayer.y -= 2;
            collider->changePositionRelative(glm::vec2(0, -2));
        }
    }

    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

    forceDevice->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)), false);
    forceDevice->update(deltaTime);
}

void Player::render() {
    sprite->render();

#ifdef SHOW_HIT_BOXES
    collider->render();
#endif // SHOW_HIT_BOXES

    forceDevice->render();
}

void Player::setTileMap(TileMap *tileMap) {
    map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos) {
    posPlayer = pos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
    forceDevice->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)), true);
    collider->changePositionAbsolute(glm::ivec2(tileMapDispl.x + posPlayer.x, tileMapDispl.y + posPlayer.y));
}
