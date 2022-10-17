#ifndef _Enemy1_INCLUDE
#define _Enemy1_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Collision.h"
#include "CollisionSystem.h"

#include "GeneralDefines.h"

// Enemy1 is basically a Sprite that represents the Enemy1. As such it has
// all properties it needs to track its movement, jumping, and collisions.
class Enemy1 {

public:

	enum Enemy1Anims { STAND_LEFT, STAND_UP, STAND_DOWN, MOVE_LEFT,MOVE_UP, MOVE_DOWN, DOWN_RETURN, UP_RETURN };

public:

    Enemy1(glm::mat4 *project);
    void init(const glm::ivec2 &tileMapPos);
    void update(int deltaTime);
    void render();

    void setTileMap(TileMap *tileMap);
    void setPosition(const glm::vec2 &pos);

private:

    bool bJumping;
    glm::ivec2 tileMapDispl:
    glm::vec2 posEnemy1;
    int jumpAngle, startY;
    Texture spritesheet;
    Sprite *sprite;
    TileMap *map;

    glm::mat4 *projection;

    Collision *collider;
    CollisionSystem *collisionSystem;

};

#endif // _Enemy1_INCLUDE
