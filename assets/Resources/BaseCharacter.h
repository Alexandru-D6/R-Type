#ifndef _BASECHARACTER_INCLUDE
#define _BASECHARACTER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class BaseCharacter
{


public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int livepoints);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

protected:
	void update(int deltaTime);
	void setSprite(ShaderProgram &shaderProgram);

private:
	int  livepoints;
	glm::ivec2 tileMapDispl, posPlayer;
	int  startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};


#endif // _BASECHARACTER_INCLUDE