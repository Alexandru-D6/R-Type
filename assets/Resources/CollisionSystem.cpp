#include "CollisionSystem.h"

CollisionSystem* CollisionSystem::instance_ = nullptr;

CollisionSystem *CollisionSystem::getInstance() {
    if (instance_ == nullptr) instance_ = new CollisionSystem();
    return instance_;
}

CollisionSystem::CollisionSystem() {
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::addColliderIntoGroup(Collision* a) {
    groups[int(a->collisionGroup)].push_back(a);
}

void CollisionSystem::removeColliderFromGroup(Collision* a) {
    int group = int(a->collisionGroup);
    for (auto it = groups[group].begin(); it != groups[group].end(); ++it) {
        if (*it == a) {
            groups[group].erase(it);
            return;
        }
    }
}

bool CollisionSystem::isColliding(const Collision* a, const glm::vec2 &offset) {
    for (int i = 0; i < groups.size(); ++i) {
        if (i != int(a->collisionGroup) 
			&& !(i == int(Collision::Player) && int(a->collisionGroup) == int(Collision::Force))
			&& !(i == int(Collision::Force) && int(a->collisionGroup) == int(Collision::Player))) {
            for (int j = 0; j < groups[i].size(); ++j) {
                if (searchForCollision(a, groups[i][j], offset)) return true;
            }
        }
    }

    return false;
}

set<Collision::CollisionGroups> CollisionSystem::collidedWith(const Collision* a) {
    set<Collision::CollisionGroups> collidedGroups;

    for (int i = 0; i < groups.size(); ++i) {
        for (int j = 0; j < groups[i].size(); ++j) {
            if (searchForCollision(a, groups[i][j], glm::vec2(0, 0))) collidedGroups.insert(static_cast<Collision::CollisionGroups>(i));
        }
    }

    return collidedGroups;
}

bool CollisionSystem::searchForCollision(const Collision* a, const Collision* b, const glm::vec2 &offset) {
    for (int i = 0; i < a->collidersSize; ++i) {
        for (int j = 0; j < b->collidersSize; ++j) {
            glm::vec2 posA = a->position + offset;
            if (overlapHorizontal(a->collisions[i], b->collisions[j], posA, b->position)) {
                return true;
            }
        }
    }

    return false;
}

bool CollisionSystem::overlapVertical(const glm::vec4 &a, const glm::vec4 &b, const glm::vec2 &posA, const glm::vec2 &posB) {
    // if one rectangle is on left side of other
    if (a[0] + posA.x >= b[2] + posB.x || b[0] + posB.x >= a[2] + posA.x) {
        return false;
    }

    // if one rectangle is above other
    if (a[3] + posA.y <= b[1] + posB.y || a[1] + posA.y >= b[3] + posB.y) {
        return false;
    }

    return true;
}

bool CollisionSystem::overlapHorizontal(const glm::vec4 &a, const glm::vec4 &b, const glm::vec2 &posA, const glm::vec2 &posB) {
    // if one rectangle is on left side of other
    if (a[0] + posA.x >= b[2] + posB.x || b[0] + posB.x >= a[2] + posA.x) {
        return false;
    }

    // if one rectangle is above other
    if (a[3] + posA.y <= b[1] + posB.y || a[1] + posA.y >= b[3] + posB.y) {
        return false;
    }

    return true;
}
