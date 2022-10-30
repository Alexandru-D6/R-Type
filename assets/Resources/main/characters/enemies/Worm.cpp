#include "Worm.h"

Worm::Worm(glm::mat4 *project, int id, const glm::ivec2 &tileMapPos) :Character(project, id, Collision::Enemy) {
	init(tileMapPos);
}

void Worm::init(const glm::ivec2 &tileMapPos) {
	bJumping = false;

	sprite = Sprite::createSprite(glm::ivec2(256, 128), glm::vec2(1 / 2.0, 1 / 2.0), &spritesheet, projection);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0625*0.0, 0.f));

	sprite->changeAnimation(0, false);
	tileMapDispl = tileMapPos;

	collider->addCollider(glm::ivec4(3, 3, 30, 14));
	collider->changePositionAbsolute(glm::vec2(tileMapDispl.x + pos.x, tileMapDispl.y + pos.y));

#ifdef SHOW_HIT_BOXES
	collider->showHitBox();
#endif // SHOW_HIT_BOXES

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Worm::update(int deltaTime)
{
	/*  sprite->update(deltaTime);
	pos.x += 2;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)))^*/
}




Part::Part(glm::mat4 *project, int id, const glm::ivec2 &tileMapPos) :Character(project, id, Collision::Enemy) {
	init(tileMapPos);
}

void Part::init(const glm::ivec2 &tileMapPos) {
	bJumping = false;
	spritesheet.loadFromFile("images/enemies/Boss.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setWrapS(GL_CLAMP_TO_EDGE);
	spritesheet.setWrapT(GL_CLAMP_TO_EDGE);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(256, 128), glm::vec2(1 / 2.0, 1 / 2.0), &spritesheet, projection);
	if (id = 0) {
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0625*0.0, 0.f));
	}
	else if (id =8) {
	}
	else {
	}
	

	sprite->changeAnimation(0, false);
	tileMapDispl = tileMapPos;

	collider->addCollider(glm::ivec4(3, 3, 30, 14));
	collider->changePositionAbsolute(glm::vec2(tileMapDispl.x + pos.x, tileMapDispl.y + pos.y));

#ifdef SHOW_HIT_BOXES
	collider->showHitBox();
#endif // SHOW_HIT_BOXES

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Part::update(int deltaTime)
{
	/*  sprite->update(deltaTime);
	pos.x += 2;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)))^*/
}
