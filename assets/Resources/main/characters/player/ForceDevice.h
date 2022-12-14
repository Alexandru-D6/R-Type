#ifndef _FORCE_DEVICE_INCLUDE
#define _FORCE_DEVICE_INCLUDE

#include <vector>
#include <set>
#include <iostream>
#include <string>

#include "textures\Sprite.h"
#include "textures\TileMap.h"
#include "collisions\Collision.h"
#include "collisions\CollisionSystem.h"
#include "ui/Text.h"

#include "GeneralDefines.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.
class ForceDevice {

public:

    enum ForceDeviceMk { ForceMK1, ForceMK2, ForceMK3 };

public:

    ForceDevice(glm::mat4 *project);
    void init(Collision *sCollider);
    void update(int deltaTime);
    void render();

    void setPosition(const glm::vec2 &pos);

    Collision* getCollider();
	bool isAttached() { return isAtached; };

	int getForceLevel() { return forceLevel; };
    void setForceLevel(int level, int power);

	void deleteRoutine();

private:

    void inputController();

    void collisionRoutine();
	bool collisionHelper(const CollisionSystem::CollisionInfo &info);

    glm::vec2 getOffsetofColliders(bool left);
    void attachToASide();

    void rotateForce(const glm::vec3 &rotation);
    void spawnProjectiles();

private:

    int forceLevel;

    glm::vec2 posForce;
    Texture *spritesheet;
    Sprite *sprite;
    TileMap *map;

    glm::mat4 *projection;

    Collision *collider;
    Collision *shipCollider;
    CollisionSystem *collisionSystem;

	int cont = 0;
	Text text;
	bool levelup = false;
	bool latchKeys[256] = { false };


    bool isAtached = true;
    bool isLeft = false;
    float shipOffset = 32.0f; // TODO: hacerlo de alguna manera dinamica
    float leftLimit = 30;
    float rightLimit = 320;
    glm::vec2 targetPosition;

    glm::vec2 forceVelocity = glm::vec2(3.0f,1.0f);
						
						/* ATTACHED   | NO ATTACHED*/
	int shotDelay1[6] = {   5, 15, 30,  0, 20, 40 };
	int currentShotCountdown = 1;

	int currentPower = 0;
};

#endif // _FORCE_DEVICE_INCLUDE
