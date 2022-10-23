#ifndef _PROJECTILE_INCLUDE
#define _PROJECTILE_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Collision.h"
#include "CollisionSystem.h"
#include "ForceDevice.h"

#include "GeneralDefines.h"

class Projectile {

public:

	enum ProjectileType {};

public:

    Projectile();

    virtual void init();
    virtual void update(int deltaTime);
    virtual void render();

    virtual void setPosition(const glm::vec2 &pos);
    virtual void setVelocity(const glm::vec2 &vel);
    virtual void setType(const ProjectileType type);
    virtual void setBounciness(const bool bounce);

    virtual int getId();

    virtual void collisionRoutine(set<Collision::CollisionGroups> collisions);
    virtual void deleteRoutine();

private:

    int idProjectile;
    glm::vec2 posProjectile;
    Texture spritesheet;
    Sprite *sprite;

    glm::mat4 *projection;

    Collision *collider;
    CollisionSystem *collisionSystem;
};

#endif // _PROJECTILE_INCLUDE
