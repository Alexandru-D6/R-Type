#include "Enemy3.h"
#include "Game.h"

Enemy3::Enemy3(glm::mat4 *project, int id, const glm::ivec2 &tileMapPos) :Character(project, id, Collision::Enemy) {

	init(tileMapPos);
}

void Enemy3::init(const glm::ivec2 &tileMapPos) {
	landed = false;
	shootDelay = 60;
	spritesheet = TextureManager::getInstance()->getSpriteSheet(TextureManager::Textures::Enemies);

	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(1 / 16.0, 1 / 10.0), spritesheet, projection);
	sprite->setNumberAnimations(5);

	sprite->setAnimationSpeed(POS_0, 8);//0-18/162-180
	sprite->addKeyframe(POS_0, glm::vec2((1.0 / 16.0)*0.0, (1.0 / 10.0)*4.0));
	sprite->setAnimationSpeed(POS_1, 8);//18-36/144-162
	sprite->addKeyframe(POS_1, glm::vec2((1.0 / 16.0)*1.0, (1.0 / 10.0)*4.0));
	sprite->setAnimationSpeed(POS_2, 8);//36-54/126-144
	sprite->addKeyframe(POS_2, glm::vec2((1.0 / 16.0)*2.0, (1.0 / 10.0)*4.0));
	sprite->setAnimationSpeed(POS_3, 8);//54-72/108-126
	sprite->addKeyframe(POS_3, glm::vec2((1.0 / 16.0)*3.0, (1.0 / 10.0)*4.0));
	sprite->setAnimationSpeed(POS_4, 8);//70-108
	sprite->addKeyframe(POS_4, glm::vec2((1.0 / 16.0)*4.0, (1.0 / 10.0)*4.0));


	sprite->changeAnimation(POS_0, false);
	tileMapDispl = tileMapPos;

	collider->addCollider(glm::ivec4(5, 8, 21, 23));
	collisionSystem->updateCollider(collider, glm::vec2(tileMapDispl.x + pos.x, tileMapDispl.y + pos.y));
	collider->changePositionAbsolute(glm::vec2(tileMapDispl.x + pos.x, tileMapDispl.y + pos.y));

#ifdef SHOW_HIT_BOXES
	collider->showHitBox();
#endif // SHOW_HIT_BOXES

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));

	poscanon =  {	{0, glm::vec2(0.0f, 3.0f)},
					{1, glm::vec2(0.0f, 3.0f)},
					{2, glm::vec2(6.0f, 2.0f)},
					{3, glm::vec2(8.0f, 0.0f)},
					{4, glm::vec2(8.0f, 0.0f)},
					{-1, glm::vec2(8.0f, 0.0f)},
					{-2, glm::vec2(8.0f, 0.0f)},
					{-3, glm::vec2(10.0f, 2.0f)},
					{-4, glm::vec2(14.0f, 3.0f)},
					{-5, glm::vec2(14.0f, 3.0f)},
				};
}

void Enemy3::update(int deltaTime) {
	sprite->update(deltaTime);

	float vel = CharacterFactory::getInstance()->mapSpeed;
	CollisionSystem::CollisionInfo mov = collisionSystem->isColliding(Enemy3::collider, glm::vec2(vel, 0.f));

	if (mov.colliding) {
		if (mov.collider->collisionGroup == Collision::CollisionGroups::Map) {
			pos.x -= vel;
			collider->changePositionRelative(glm::vec2(-vel, 0));
		}
		else if (mov.collider->collisionGroup == Collision::CollisionGroups::Player) {
			CharacterFactory::getInstance()->damageCharacter(mov.collider->getId(), 1);
			CharacterFactory::getInstance()->damageCharacter(id, 1);
		}
	}
	else {
		pos.x += vel;
		collider->changePositionRelative(glm::vec2(vel, 0));
	}

	if(!landed){
		CollisionSystem::CollisionInfo info = collisionSystem->isColliding(Enemy3::collider, glm::vec2(0, FALL_STEP));
		if (info.colliding) {
			if (info.collider->collisionGroup == Collision::CollisionGroups::Player) {
				CharacterFactory::getInstance()->damageCharacter(info.collider->getId(), 1);
				CharacterFactory::getInstance()->damageCharacter(id, 1);
			}

			landed = true;
			startY = pos.y;
        } else {
            pos.y += FALL_STEP;
            collider->changePositionRelative(glm::vec2(0, FALL_STEP));
        }
	}
	glm::vec2 playerpos;
	bool existsPlayer = CharacterFactory::getInstance()->getPlayerPos(playerpos);

	if (existsPlayer) {
		glm::vec2 dir = (playerpos + glm::vec2(16.f, 7.f)) - (pos + glm::vec2(6.0f, 9.0f));

		float angle = -1 * atan2(dir.y, dir.x);

		if (72.f * PI / 180.f < angle && 108.f * PI / 180.f > angle) {
			sprite->changeAnimation(POS_4, false);
		}
		else if (54.f * PI / 180.f < angle && 126.f * PI / 180.f > angle) {
			sprite->changeAnimation(POS_3, false);
		}
		else if (36.f * PI / 180.f < angle && 144.f * PI / 180.f > angle) {
			sprite->changeAnimation(POS_2, false);
		}
		else if (18.f * PI / 180.f < angle && 162.f * PI / 180.f > angle) {
			sprite->changeAnimation(POS_1, false);
		}
		else {
			sprite->changeAnimation(POS_0, false);
		}
		if (angle > 90.f*PI / 180.f && angle < 270.f*PI / 180.f && rot) {
			rot = false;
			rotate(0.f, 0.f, 0.f);
		}
		else if ((angle < 90.f*PI / 180.f && angle > 0.f*PI / 180.f) || angle > 270.f*PI / 180.f && !rot) {
			rot = true;
			rotate(0.f, 180.f, 0.f);
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	shoot();
	Character::update(deltaTime);
}

void Enemy3::shoot() {
	if (shootDelay == 0) {
		shootDelay = 60;

		int aux = 0;
		if (rot)aux = -5;

		glm::vec2 playerpos;
		bool existsPlayer = CharacterFactory::getInstance()->getPlayerPos(playerpos);

		if (!existsPlayer) return;

		glm::vec2 dir = (playerpos + glm::vec2(16.f, 7.f)) - (pos + poscanon[aux*sprite->animation()]);

		float angle = atan2(dir.y, dir.x);
		dir = glm::vec2(cos(angle), sin(angle));

		float velocity = 2.0f;
		dir *= velocity;

		ProjectileFactory::getInstance()->spawnProjectile(pos + poscanon[aux+sprite->animation()], dir, false, Projectile::EnemyProjectile);
	}
	else shootDelay -= 1;
}

void Enemy3::deleteRoutine() {
	int random = rand() % 3;
	if (random == 0) {
		random = rand() % 2;
		ObjectFactory::getInstance()->spawnObject(pos, (random == 0) ? Object::ModifierMBlue : Object::ModifierMRed);
	}
	Character::deleteRoutine();
}
