#include "ProjectileNormal.h"
#include "GeneralDefines.h"

ProjectileNormal::ProjectileNormal(glm::mat4 *project, int id) {
    projection = project;
    idProjectile = id;
    collider = new Collision(project, Collision::PlayerProjectiles);

    collisionSystem = CollisionSystem::getInstance();
    collisionSystem->addColliderIntoGroup(collider);
}

void ProjectileNormal::init() {
    spritesheet.loadFromFile("images/player/force-pit-beam.png", TEXTURE_PIXEL_FORMAT_RGBA);

    spritesheet.setWrapS(GL_CLAMP_TO_EDGE);
    spritesheet.setWrapT(GL_CLAMP_TO_EDGE);
    spritesheet.setMinFilter(GL_NEAREST);
    spritesheet.setMagFilter(GL_NEAREST);

    float xt = 1.0 / 20.0;
    float ys = 1.0 / 64.0;
    sprite = Sprite::createSprite(glm::ivec2(12, 6), glm::vec2(xt, ys), &spritesheet, projection);
    sprite->setNumberAnimations(1);

        sprite->setAnimationSpeed(0, 8);
        sprite->addKeyframe(0, glm::vec2(xt * 0.0, ys * 56.0f));
        sprite->addKeyframe(0, glm::vec2(xt * 1.0, ys * 56.0f));

    sprite->changeAnimation(0, false);

    collider->addCollider(glm::ivec4(0, 0, 12, 6));
    collider->changePositionAbsolute(glm::vec2(0.0f, 0.0f));

#ifdef SHOW_HIT_BOXES
    collider->showHitBox();
#endif // SHOW_HIT_BOXES

    sprite->setPosition(glm::vec2(0.0f,0.0f));
}

void ProjectileNormal::update(int deltaTime) {
    if (posProjectile.x >= 600.0f) {
        ProjectileFactory::getInstance()->destroyProjectile(idProjectile);
        return;
    }

    posProjectile += glm::vec2(3.0f, 0.0f);

    sprite->setPosition(posProjectile);
    sprite->update(deltaTime);
}

void ProjectileNormal::render() {
    sprite->render();

#ifdef SHOW_HIT_BOXES
    collider->render();
#endif // SHOW_HIT_BOXES
}

void ProjectileNormal::setPosition(const glm::vec2 &pos) {
    posProjectile = pos;
    sprite->setPosition(posProjectile);
    collider->changePositionAbsolute(posProjectile);
}

void ProjectileNormal::setVelocity(const glm::vec2 &vel) {
    throw exception("Not Implemented Method");
}

void ProjectileNormal::setType(const ProjectileType type) {
    throw exception("Not Implemented Method");
}

void ProjectileNormal::setBounciness(const bool bounce) {
    throw exception("Not Implemented Method");
}

void ProjectileNormal::collisionRoutine(set<Collision::CollisionGroups> collisions) {
    throw exception("Not Implemented Method");
}

void ProjectileNormal::deleteRoutine() {
    collisionSystem->removeColliderFromGroup(collider);
    delete collider;
}