#include "Projectile.h"
#include "Game.h"
#include "GeneralDefines.h"

Projectile::Projectile() {
}

void Projectile::init() {
    throw exception("Not Implemented Method");
}

void Projectile::update(int deltaTime) {
    throw exception("Not Implemented Method");
}

void Projectile::render() {
    throw exception("Not Implemented Method");
}

void Projectile::setPosition(const glm::vec2 &pos) {
    throw exception("Not Implemented Method");
}

void Projectile::setVelocity(const glm::vec2 &vel) {
    throw exception("Not Implemented Method");
}

void Projectile::setType(const ProjectileType type) {
    throw exception("Not Implemented Method");
}

void Projectile::setBounciness(const bool bounce) {
    throw exception("Not Implemented Method");
}

int Projectile::getId() {
    throw exception("Not Implemented Method");
}

void Projectile::collisionRoutine(set<Collision::CollisionGroups> collisions) {
    throw exception("Not Implemented Method");
}

void Projectile::deleteRoutine() {
    throw exception("Not Implemented Method");
}