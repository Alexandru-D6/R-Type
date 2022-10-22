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

void ProjectileFactory::spawnProjectile(const glm::vec2 &pos) {
    Projectile *projectile = new Projectile(projection, last_id);
    projectiles[last_id] = projectile;
    ++last_id;

    projectile->init();
    projectile->setPosition(pos);
}

void ProjectileFactory::update(int deltaTime) {
    for (auto it = projectiles.begin(); it != projectiles.end(); it++) {
        it->second->update(deltaTime);
    }
}

void ProjectileFactory::render() {
    for (auto it = projectiles.begin(); it != projectiles.end(); it++) {
        it->second->render();
    }
}