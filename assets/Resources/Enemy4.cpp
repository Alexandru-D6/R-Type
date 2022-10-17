#include "Enemy4.h"
#include "Game.h"
#include "GeneralDefines.h"

Enemy4::Enemy4(glm::mat4 *project) {
    projection = project;
    collider = new Collision(project, Collision::Enemy);

    collisionSystem = CollisionSystem::getInstance();
    collisionSystem->addColliderIntoGroup(collider);
}

void Enemy4::init(const glm::ivec2 &tileMapPos) {
    bJumping = false;
    spritesheet.loadFromFile("images/Enemies/basic-enemies.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(32, 16), glm::vec2(1/16.0, 1/16.0), &spritesheet, projection);
    sprite->setNumberAnimations(7);

        sprite->setAnimationSpeed(STAND_RIGHT, 8);
        sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0625*8.0, 0.f));

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
    collider->changePositionAbsolute(glm::vec2(tileMapDispl.x + posEnemy4.x, tileMapDispl.y + posEnemy4.y));

#ifdef SHOW_HIT_BOXES
    collider->showHitBox();
#endif // SHOW_HIT_BOXES

    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy4.x), float(tileMapDispl.y + posEnemy4.y)));
}

void Enemy4::update(int deltaTime)
{
    sprite->update(deltaTime);
    if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
        if(sprite->animation() != STAND_RIGHT)
            sprite->changeAnimation(STAND_RIGHT, false);
        //posEnemy4.x -= 2;
        //collider.changePositionRelative(glm::vec2(-2, 0));
        map->moveMap(1);
        if(collisionSystem->isColliding(Enemy4::collider)) {
            //posEnemy4.x += 2;
            //collider.changePositionRelative(glm::vec2(2, 0));
            map->moveMap(-1);
            sprite->changeAnimation(STAND_RIGHT,false);
        }
    }
    else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
        if(sprite->animation() == STAND_UP)sprite->changeAnimation(UP_RETURN, false);

        //posEnemy4.x += 2;
        //collider.changePositionRelative(glm::vec2(2, 0));
        map->moveMap(-2);
        if(collisionSystem->isColliding(Enemy4::collider)) {
            //posEnemy4.x -= 2;
            //collider.changePositionRelative(glm::vec2(-2, 0));
            map->moveMap(2);
            sprite->changeAnimation(STAND_RIGHT, false);
        }
    }

    if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
        posEnemy4.y += 2;
        collider->changePositionRelative(glm::vec2(0, 2));
        if (collisionSystem->isColliding(Enemy4::collider))
        {
            posEnemy4.y -= 2;
            collider->changePositionRelative(glm::vec2(0, -2));
        }
    }
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
        posEnemy4.y -= 2;
		if (sprite->animation() == STAND_RIGHT) {
			sprite->changeAnimation(MOVE_UP, false);
			sprite->setFinishedAnimation(false);
		}
		else if (sprite->animation() == STAND_DOWN || sprite->animation() == MOVE_DOWN)sprite->changeAnimation(DOWN_RETURN, false);
        collider->changePositionRelative(glm::vec2(0, -2));
        if (collisionSystem->isColliding(Enemy4::collider))
        {
            posEnemy4.y += 2;
            collider->changePositionRelative(glm::vec2(0, 2));
        }
    }
	if (sprite->animation() == MOVE_UP && sprite->isFinidhedAnimation() == true) {
		sprite->changeAnimation(STAND_UP, false);
	} 

    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy4.x), float(tileMapDispl.y + posEnemy4.y)));
}

void Enemy4::render() {
    sprite->render();

#ifdef SHOW_HIT_BOXES
    collider->render();
#endif // SHOW_HIT_BOXES
}

void Enemy4::setTileMap(TileMap *tileMap) {
    map = tileMap;
}

void Enemy4::setPosition(const glm::vec2 &pos) {
    posEnemy4 = pos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy4.x), float(tileMapDispl.y + posEnemy4.y)));
    collider->changePositionAbsolute(glm::vec2(tileMapDispl.x + posEnemy4.x, tileMapDispl.y + posEnemy4.y));
}
