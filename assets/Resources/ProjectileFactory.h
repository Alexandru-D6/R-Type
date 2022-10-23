#ifndef _PROJECTILE_FACTORY_INCLUDE
#define _PROJECTILE_FACTORY_INCLUDE

#include <map>
#include <set>

#include "Projectile.h"
#include "ProjectileNormal.h"

class ProjectileFactory {

private:

    static ProjectileFactory *instance_;

public:

    static ProjectileFactory *getInstance();

private:

    ProjectileFactory();
    ~ProjectileFactory();

    void lateDestroyProjectile();

public:

    void init();
    void update(int deltaTime);
    void render();

    void setProjection(glm::mat4 *project);

    void spawnProjectile(const glm::vec2 &pos);
    void destroyProjectile(const int &id);

private:

    glm::mat4 *projection;

    map<int, Projectile *> projectiles;
    int last_id = 0;

    set<int> pendingToBeDestroyed;
};

#endif // _PROJECTILE_FACTORY_INCLUDE
