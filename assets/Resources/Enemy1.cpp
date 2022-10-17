#include "Enemy1.h"
#include "Game.h"
#include "GeneralDefines.h"

Enemy1::Enemy1(glm::mat4 *project) {
    projection = project;
    collider = new Collision(project, Collision::Enemy);

    collisionSystem = CollisionSystem::getInstance();
    collisionSystem->addColliderIntoGroup(collider);
}

void Enemy1::init(const glm::ivec2 &tileMapPos) {
    bJumping = false;
    spritesheet.loadFromFile("images/Enemies/basic-enemies.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(16,24), glm::vec2(1/32.0, 1/64.0), &spritesheet, projection);
    sprite->setNumberAnimations(8);

        sprite->setAnimationSpeed(STAND_LEFT, 8);
        sprite->addKeyframe(STAND_LEFT, glm::vec2(1/32*4.0, 1/64*5.0));

		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(1 / 32 * 3.0, 1 / 64 * 5.0));

		sprite->setAnimationSpeed(STAND_UP, 8);
		sprite->addKeyframe(STAND_UP, glm::vec2(0.0625*2.0, 0.0625*2.0f));
		
		sprite->setAnimationSpeed(MOVE_UP, 3);
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.0625*0.0, 0.0625*2.0f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.0625*1.0, 0.0625*2.0f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.0625*2.0, 0.0625*2.0f));

		sprite->setAnimationSpeed(STAND_DOWN, 8);
		sprite->addKeyframe(STAND_DOWN, glm::vec2(0.0625*3.0, 0.0625*4.0f));

		sprite->setAnimationSpeed(MOVE_DOWN, 8);
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.0625*5.0, 0.0625*2.0f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.0625*4.0, 0.0625*2.0f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.0625*3.0, 0.0625*2.0f));

		sprite->setAnimationSpeed(UP_RETURN, 8);
		sprite->addKeyframe(UP_RETURN, glm::vec2(0.0625*2.0, 0.0625*2.0f));
		sprite->addKeyframe(UP_RETURN, glm::vec2(0.0625*1.0, 0.0625*2.0f));
		sprite->addKeyframe(UP_RETURN, glm::vec2(0.0625*0.0, 0.0625*2.0f));
		sprite->addKeyframe(UP_RETURN, glm::vec2(0.0625*2.0, 0.0625*2.0f));


		sprite->setAnimationSpeed(DOWN_RETURN, 8);
		sprite->addKeyframe(DOWN_RETURN, glm::vec2(0.0625*3.0, 0.0625*2.0f));
		sprite->addKeyframe(DOWN_RETURN, glm::vec2(0.0625*4.0, 0.0625*2.0f));
		sprite->addKeyframe(DOWN_RETURN, glm::vec2(0.0625*5.0, 0.0625*2.0f));
		sprite->addKeyframe(DOWN_RETURN, glm::vec2(0.0625*2.0, 0.0625*2.0f));




    sprite->changeAnimation(0, false);
    tileMapDispl = tileMapPos;

    collider->addCollider(glm::ivec4(3, 3, 30, 14));
    collider->changePositionAbsolute(glm::ivec2(tileMapDispl.x + posEnemy1.x, tileMapDispl.y + posEnemy1.y));

#ifdef SHOW_HIT_BOXES
    collider->showHitBox();
#endif // SHOW_HIT_BOXES

    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy1.x), float(tileMapDispl.y + posEnemy1.y)));
}

void Enemy1::update(int deltaTime)
{
    sprite->update(deltaTime);
        if(sprite->animation() != STAND_LEFT)
            sprite->changeAnimation(MOVE_LEFT, false);
        posEnemy1.x -= 0.5;
        collider->changePositionRelative(glm::ivec2(-0.5, 0));
        if(collisionSystem->isColliding(Enemy1::collider)) {
            posEnemy1.x += 0.5;
            collider->changePositionRelative(glm::ivec2(0.5, 0));
            sprite->changeAnimation(STAND_LEFT, false);
        }

    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy1.x), float(tileMapDispl.y + posEnemy1.y)));
}

void Enemy1::render() {
    sprite->render();

#ifdef SHOW_HIT_BOXES
    collider->render();
#endif // SHOW_HIT_BOXES
}

void Enemy1::setTileMap(TileMap *tileMap) {
    map = tileMap;
}

void Enemy1::setPosition(const glm::vec2 &pos) {
    posEnemy1 = pos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy1.x), float(tileMapDispl.y + posEnemy1.y)));
    collider->changePositionAbsolute(glm::ivec2(tileMapDispl.x + posEnemy1.x, tileMapDispl.y + posEnemy1.y));
}
