#ifndef _PROJECTILE_NORMAL_INCLUDE
#define _PROJECTILE_NORMAL_INCLUDE

#include "Projectile.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Collision.h"
#include "CollisionSystem.h"
#include "ProjectileFactory.h"

#include "GeneralDefines.h"

class ProjectileNormal : public Projectile {

public:

	enum ProjectileType {};

public:

    ProjectileNormal(glm::mat4 *project, int id);
    void init();
    void update(int deltaTime);
    void render();

    void setPosition(const glm::vec2 &pos);
    void setVelocity(const glm::vec2 &vel);
    void setType(const ProjectileType type);
    void setBounciness(const bool bounce);

    int getId() { return idProjectile; };

    void collisionRoutine(set<Collision::CollisionGroups> collisions);
    void deleteRoutine();

private:

    int idProjectile;
    glm::vec2 posProjectile;
    Texture spritesheet;
    Sprite *sprite;

    glm::mat4 *projection;

    Collision *collider;
    CollisionSystem *collisionSystem;
};

#endif // _PROJECTILE_NORMAL_INCLUDE
