#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
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

	collider = Collision();
	collider.addCollider(glm::ivec4(5, 5, 27, 32));
	collider.changePositionAbsolute(glm::ivec2(tileMapDispl.x + posPlayer.x, tileMapDispl.y + posPlayer.y));

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		collider.changePositionRelative(glm::ivec2(-2, 0));
		map->moveMap(8);
		if(Collision::Collision().collisionMoveLeft(Player::collider, map->collision))
		{
			posPlayer.x += 2;
			collider.changePositionRelative(glm::ivec2(2, 0));
			map->moveMap(-8);
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);

		posPlayer.x += 2;
		collider.changePositionRelative(glm::ivec2(2, 0));
		map->moveMap(-8);
		if(Collision::Collision().collisionMoveRight(Player::collider, map->collision))
		{
			posPlayer.x -= 2;
			collider.changePositionRelative(glm::ivec2(-2, 0));
			map->moveMap(8);
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		posPlayer.y += 2;
		collider.changePositionRelative(glm::ivec2(0, 2));
		if (Collision::Collision().collisionMoveDown(Player::collider, map->collision))
		{
			posPlayer.y -= 2;
			collider.changePositionRelative(glm::ivec2(0, -2));
		}
	}else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		posPlayer.y -= 2;
		collider.changePositionRelative(glm::ivec2(0, -2));
		if (Collision::Collision().collisionMoveUp(Player::collider, map->collision))
		{
			posPlayer.y += 2;
			collider.changePositionRelative(glm::ivec2(0, 2));
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	collider.changePositionAbsolute(glm::ivec2(tileMapDispl.x + posPlayer.x, tileMapDispl.y + posPlayer.y));
}




