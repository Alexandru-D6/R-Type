#include "Enemy1.h"

 
Enemy1::Enemy1(glm::mat4 *project,int id, Collision::CollisionGroups type, const glm::ivec2 &tileMapPos):Character(project,id, type){
	init(tileMapPos);
}

void Enemy1::init(const glm::ivec2 &tileMapPos) {
    bJumping = false;
	jumpDelay = 200;
    spritesheet.loadFromFile("images/Enemies/basic-enemies.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spritesheet.setWrapS(GL_CLAMP_TO_EDGE);
    spritesheet.setWrapT(GL_CLAMP_TO_EDGE);
    spritesheet.setMinFilter(GL_NEAREST);
    spritesheet.setMagFilter(GL_NEAREST);

    sprite = Sprite::createSprite(glm::ivec2(24,24), glm::vec2(1/16.0, 1/10.0), &spritesheet, projection);
    sprite->setNumberAnimations(4);

        sprite->setAnimationSpeed(STAND_LEFT, 8);
        sprite->addKeyframe(STAND_LEFT, glm::vec2((1.0/16.0)*0.0, (1.0/10.0)*7.0));

		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2((1.0/16.0)*3.0, (1.0/10.0)*7.0));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2((1.0/16.0)*4.0, (1.0/10.0)*7.0));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2((1.0/16.0)*5.0, (1.0/10.0)*7.0));
		
		sprite->setAnimationSpeed(FLY_LEFT, 8);
		sprite->addKeyframe(FLY_LEFT, glm::vec2((1.0 / 16.0)*2.0, (1.0 / 10.0)*7.0));

		sprite->setAnimationSpeed(LANDING_LEFT, 8);
		sprite->addKeyframe(LANDING_LEFT, glm::vec2((1.0 / 16.0)*1.0, (1.0 / 10.0)*7.0));
		sprite->addKeyframe(LANDING_LEFT, glm::vec2((1.0 / 16.0)*0.0, (1.0 / 10.0)*7.0));


    sprite->changeAnimation(STAND_LEFT, false);
    tileMapDispl = tileMapPos;

    collider->addCollider(glm::ivec4(5, 8, 21, 23));
    collider->changePositionAbsolute(glm::vec2(tileMapDispl.x + pos.x, tileMapDispl.y + pos.y));

#ifdef SHOW_HIT_BOXES
    collider->showHitBox();
#endif // SHOW_HIT_BOXES

    sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Enemy1::update(int deltaTime)
{
	if (!bJumping)jumpDelay -= 1;

	sprite->update(deltaTime);

    if(sprite->animation() == STAND_LEFT) 
		sprite->changeAnimation(MOVE_LEFT, false);

    CollisionSystem::CollisionInfo info = collisionSystem->isColliding(Enemy1::collider, glm::vec2(-0.5, 0));

    if(info.colliding) {
        sprite->changeAnimation(STAND_LEFT, false);
    } else {
        pos.x -= 0.5;
        collider->changePositionRelative(glm::vec2(-0.5, 0));
    }


	if (jumpDelay <= 0 && landed) {
		jumpDelay = 200;
		bJumping = true;
	}

	if (bJumping) {
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180) {
			bJumping = false;
			collider->changePositionRelative(glm::vec2(0, startY-pos.y));
			pos.y = startY;
		} else {
            CollisionSystem::CollisionInfo info = collisionSystem->isColliding(Enemy1::collider, glm::vec2(0, (startY - 96.0f * sin(3.14159f * jumpAngle / 180.f)) - pos.y));

			if (info.colliding) {
				bJumping = false;
            } else {
                collider->changePositionRelative(glm::vec2(0, (startY - 96.0f * sin(3.14159f * jumpAngle / 180.f)) - pos.y));
                pos.y = startY - 96.0f * sin(3.14159f * jumpAngle / 180.f);
            }
		}
	} else {
        CollisionSystem::CollisionInfo info = collisionSystem->isColliding(Enemy1::collider, glm::vec2(0, FALL_STEP));

		if (info.colliding) {
				bJumping = false;
				landed = true;
				jumpAngle = 0;
				startY = pos.y;
        } else {
            landed = false;
            pos.y += FALL_STEP;
            collider->changePositionRelative(glm::vec2(0, FALL_STEP));
        }
	}


    sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}