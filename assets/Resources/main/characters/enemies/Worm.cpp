#include "Worm.h"

Worm::Worm(glm::mat4 *project, int id) :Character(project, id, Collision::Enemy) {
	init();
}

void Worm::init() {

	for (int i = 0; i <= 8; ++i) {
		parts.push_back(new Part(projection,id,i));
	}

#pragma region DummySprite
	spritesheet = TextureManager::getInstance()->getSpriteSheet(TextureManager::Textures::Boss);

	sprite = Sprite::createSprite(glm::ivec2(26, 22), glm::vec2(1 / 2.0, 1 / 2.0), spritesheet, projection);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0625*1.0, 0.f));

	sprite->changeAnimation(0, false);
#pragma endregion


}

void Worm::update(int deltaTime)
{
	float mov = -1.f;
	CollisionSystem::CollisionInfo info = collisionSystem->isColliding(Worm::collider, glm::vec2(mov, 0));

	if (!info.colliding) {
		pos.x += mov;
		//collider->changePositionRelative(glm::vec2(mov,0.f));
		//sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
		for (int i = 0; i < ((int)parts.size() - 1); ++i) {
			//parts[i]->setPosition(parts[i + 1]->getPosition());
		}
		//parts[(parts.size() - 1)]->setPosition(pos);
	}

	setPosition(glm::vec2(0.0f,0.0f));
	
}

void Worm::render()
{
	for (int i = 0; i < (int)parts.size(); ++i) {
		parts[i]->render();
	}
}

void Worm::setPosition(const glm::vec2 &pos) {
	for (int i = 1; i < (int)parts.size(); ++i) {
		parts[i]->setPosition(parts[i-1]->getPosition() + glm::vec2(16.0f,0.0f));
	}
	parts[0]->setPosition(pos);

}



Part::Part(glm::mat4 *project, int id, int idBody) :Character(project, id, Collision::Enemy) {
	this->idBody = idBody;
	init();
}

void Part::init() {
	bJumping = false;

	spritesheet = TextureManager::getInstance()->getSpriteSheet(TextureManager::Textures::Boss);

	if (idBody == 0) {
		sprite = Sprite::createSprite(glm::ivec2(26, 22), glm::vec2(1.f / 9.34f, 1.f / 11.f), spritesheet, projection);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(1.f / 9.34f*0.f, 1.f / 11.f*6.f));

		collider->addCollider(glm::ivec4(0, 0, 26, 22));
		collider->changePositionAbsolute(glm::vec2(tileMapDispl.x + pos.x, tileMapDispl.y + pos.y));
	}
	else if (idBody == 8) {
		sprite = Sprite::createSprite(glm::ivec2(26, 22), glm::vec2(1.f / 9.34f, 1.f / 11.f), spritesheet, projection);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(1.f / 9.34f*0.f, 1.f / 11.f*6.f));
		rotate(0.f,180.f, 0.f);

		collider->addCollider(glm::ivec4(0, 0, 26, 22));
		collider->changePositionAbsolute(glm::vec2(tileMapDispl.x + pos.x, tileMapDispl.y + pos.y));
	}
	else {
		sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16.f, 1 / 16.0), spritesheet, projection);
		sprite->setNumberAnimations(2);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(1.f/16.f*2.f, 1.f / 16.f*9.f));
		
		sprite->setAnimationSpeed(1, 8);
		sprite->addKeyframe(1, glm::vec2(1.f / 16.f*3.f, 1.f / 16.f*9.f));

		collider->addCollider(glm::ivec4(0, 0, 16, 16));
		collider->changePositionAbsolute(glm::vec2(tileMapDispl.x + pos.x, tileMapDispl.y + pos.y));
	}
	

	sprite->changeAnimation(0, false);

	

#ifdef SHOW_HIT_BOXES
	collider->showHitBox();
#endif // SHOW_HIT_BOXES

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Part::update(int deltaTime) {
	
}

void Part::setPosition(const glm::vec2 &pos) {

	/*if (idBody >= 1 && idBody <= 7) {
		pos
	}*/

	this->pos = pos;
	sprite->setPosition(this->pos);
	collisionSystem->updateCollider(collider, this->pos);
	collider->changePositionAbsolute(this->pos);
}
