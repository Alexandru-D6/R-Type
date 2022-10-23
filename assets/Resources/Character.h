#ifndef _CHARACTER_INCLUDE
#define _CHARACTER_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Collision.h"
#include "CollisionSystem.h"

#include "GeneralDefines.h"


class Character {

public:

	enum CharacterAnims { STAND_RIGHT};

protected:
	Character(glm::mat4 *project);
	~Character();

public:

	
	virtual void init(const glm::ivec2 &tileMapPos);
	virtual void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition() { return pos; };

private:

	bool bJumping;
	glm::ivec2 tileMapDispl;
	glm::vec2 pos;
	float jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

	glm::mat4 *projection;

	Collision *collider;
	CollisionSystem *collisionSystem;

};

#endif // _CHARACTER_INCLUDE
