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

    Projectile(glm::mat4 *project, int id);
    void init();
    void update(int deltaTime);
    void render();

    void setPosition(const glm::vec2 &pos);
    void setVelocity(const glm::vec2 &vel);
    void setType(const ProjectileType type);
    void setBounciness(const bool bounce);

    void collisionRoutine(set<Collision::CollisionGroups> collisions);

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
