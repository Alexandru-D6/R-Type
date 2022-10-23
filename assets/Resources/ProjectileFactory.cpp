#include "ProjectileFactory.h"

ProjectileFactory* ProjectileFactory::instance_ = nullptr;

ProjectileFactory *ProjectileFactory::getInstance() {
    if (instance_ == nullptr) instance_ = new ProjectileFactory();
    return instance_;
}

ProjectileFactory::ProjectileFactory() {
}

ProjectileFactory::~ProjectileFactory() {
}

void ProjectileFactory::init() {
    last_id = 0;
    /*spritesheet.loadFromFile("images/player/force-pit-beam.png", TEXTURE_PIXEL_FORMAT_RGBA);

    spritesheet.setWrapS(GL_CLAMP_TO_EDGE);
    spritesheet.setWrapT(GL_CLAMP_TO_EDGE);
    spritesheet.setMinFilter(GL_NEAREST);
    spritesheet.setMagFilter(GL_NEAREST);

    float xt = 1.0 / 20.0;
    float ys = 1.0 / 64.0;
    sprite = Sprite::createSprite(glm::ivec2(12, 6), glm::vec2(xt, ys), &spritesheet, projection);
    sprite->setNumberAnimations(1);*/
}

void ProjectileFactory::setProjection(glm::mat4 *project) {
    projection = project;
}

void ProjectileFactory::spawnProjectile(const glm::vec2 &pos, const glm::vec2 &vel, bool bounce, Projectile::ProjectileType type) {
    Projectile *projectile = new ProjectileNormal(projection, last_id);
    projectiles.insert({last_id, projectile });
    ++last_id;

    projectile->init();
    projectile->setPosition(pos);
    projectile->setVelocity(vel);
    projectile->setBounciness(bounce);
    projectile->setType(type);
}

void ProjectileFactory::destroyProjectile(const int &id) {
    pendingToBeDestroyed.insert(id);
}

void ProjectileFactory::lateDestroyProjectile() {
    for (auto it = pendingToBeDestroyed.begin(); it != pendingToBeDestroyed.end(); ++it) {
        projectiles[*it]->deleteRoutine();
        delete projectiles[*it];
        projectiles.erase(*it);
    }
    pendingToBeDestroyed.clear();
}

void ProjectileFactory::update(int deltaTime) {
    map<int, Projectile*>::iterator it = projectiles.begin();

    while (it != projectiles.end()) {
        it->second->update(deltaTime);
        if(it != projectiles.end()) ++it;
    }

    lateDestroyProjectile();
}

void ProjectileFactory::render() {
    for (auto it = projectiles.begin(); it != projectiles.end(); it++) {
        it->second->render();
    }
}