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

	position[0] = glm::vec2(270.0f, 128.0f);
	position[1] = glm::vec2(220.0f, 178.0f);
	position[2] = glm::vec2(170.0f, 128.0f);
	position[3] = glm::vec2(220.0f, 78.0f);

	targetPosition = position[currentTarget];

	//<------<
	pos = glm::vec2(220.0f, 128.0f);
	for (int i = 1; i <= 8; ++i) {
		parts[i]->setPosition(parts[i - 1]->getPosition() + parts[i - 1]->anchorPoint - parts[i]->anchorPoint + glm::vec2(16.0f, 0.0f));
	}

}

void Worm::update(int deltaTime)
{
	changeTarget();

	glm::vec2 dir = getDir(pos, targetPosition);
	setPosition(dir);
	
}

void Worm::render()
{
	for (int i = 0; i < (int)parts.size(); ++i) {
		parts[i]->render();
	}
}

void Worm::rotateSprite(Part *part, const glm::vec2 &vector) {
	float angle = atan2(vector.y, vector.x) * (180.0f / PI);
	angle += 180.0f;

	part->rotateSprite(glm::vec3(0.0f, 0.0f, angle));
}

void Worm::setPosition(const glm::vec2 &movement) {
	for (int i = (int)parts.size() - 1; i > 0; --i) {
		glm::vec2 dir = getDir(	parts[i]->getPosition() + parts[i]->anchorPoint,
								parts[i - 1]->getPosition() + parts[i - 1]->anchorPoint);
		parts[i]->setPosition(parts[i - 1]->getPosition());
		rotateSprite(parts[i], dir);
	}

	this->pos = this->pos + movement;
	parts[0]->setPosition(pos);
	rotateSprite(parts[0], movement);
}

void Worm::changeTarget() {

	if (abs(distance(targetPosition, pos)) <= 5.0f) {
		currentTarget++;
		if (currentTarget > 3) currentTarget = 0;
		targetPosition = position[currentTarget];
	}
}

glm::vec2 Worm::getDir(const glm::vec2 &posA, const glm::vec2 &posB) {
	glm::vec2 vector = posB - posA;
	float angle = atan2(vector.y, vector.x);
	glm::vec2 dir = glm::vec2(cos(angle), sin(angle));
	return dir;
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

		anchorPoint = glm::vec2(18.0f, 11.0f);

	}
	else if (idBody == 8) {
		sprite = Sprite::createSprite(glm::ivec2(26, 22), glm::vec2(1.f / 9.34f, 1.f / 11.f), spritesheet, projection);
		sprite->setNumberAnimations(1);

		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(1.f / 9.34f*0.f, 1.f / 11.f*5.f));

		collider->addCollider(glm::ivec4(0, 0, 26, 22));
		collider->changePositionAbsolute(glm::vec2(tileMapDispl.x + pos.x, tileMapDispl.y + pos.y));

		anchorPoint = glm::vec2(8.0f, 11.0f);
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

		anchorPoint = glm::vec2(8.0f, 8.0f);

	}
	

	sprite->changeAnimation(0, false);

	

#ifdef SHOW_HIT_BOXES
	collider->showHitBox();
#endif // SHOW_HIT_BOXES

	sprite->setPosition(this->pos);
}

void Part::update(int deltaTime) {
	
}

void Part::setPosition(const glm::vec2 &pos) {
	this->pos = pos;
	sprite->setPosition(this->pos);
	collisionSystem->updateCollider(collider, this->pos);
	collider->changePositionAbsolute(this->pos);
}

void Part::rotateSprite(glm::vec3 rotation) {
	rotate(rotation.x, rotation.y, rotation.z);
}
