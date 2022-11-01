#include "CollisionSystem.h"

CollisionSystem* CollisionSystem::instance_ = nullptr;

CollisionSystem *CollisionSystem::getInstance() {
    if (instance_ == nullptr) instance_ = new CollisionSystem();
    return instance_;
}

CollisionSystem::CollisionSystem() {
	spatialHashmap = new SpatialHashmap(32);
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::addColliderIntoGroup(Collision* a) {
	spatialHashmap->insertObject(a);
    //groups[int(a->collisionGroup)].push_back(a);
}

void CollisionSystem::removeColliderFromGroup(Collision* a) {
	spatialHashmap->removeObject(a);
    /*int group = int(a->collisionGroup);
    for (auto it = groups[group].begin(); it != groups[group].end(); ++it) {
        if (*it == a) {
            groups[group].erase(it);
            return;
        }
    }*/
}

void CollisionSystem::updateCollider(Collision* a, const glm::vec2 &newPos) {
	spatialHashmap->updateObject(a, newPos);
}

bool CollisionSystem::isValidCollision(const Collision* a, const Collision* b) {
    return collisionMatrix[a->collisionGroup][b->collisionGroup];
}

bool CollisionSystem::isTriggerCollision(const Collision* a, const Collision* b) {
    return triggersMatrix[a->collisionGroup][b->collisionGroup];
}

CollisionSystem::CollisionInfo CollisionSystem::isColliding(Collision* a, const glm::vec2 &offset) {
	glm::vec4 box = a->getBoundingBox();

	glm::vec2 pos = glm::vec2((box.x+box.z)/2.0f, (box.y+box.w)/2.0f);
	float radius = glm::distance(pos, glm::vec2(box.x,box.y));

	pos.x += a->position.x;
	pos.y += a->position.y;

	int coll = a->collisionGroup;
	set<int> collidersGroup;

	for (int i = 0; i < collisionMatrix[coll].size(); ++i) {
		if (collisionMatrix[coll][i]) collidersGroup.insert(i);
	}

	set<Collision*> objects = spatialHashmap->getNearByObjects(pos, radius, collidersGroup);
	set<Collision*>::iterator it = objects.begin();

	while (it != objects.end()) {
		if (searchForCollision(a, *it, offset)) {
			return CollisionInfo{
				true,
				*it,
				false };
		}
		++it;
	}

    /*for (int i = 0; i < (int)groups.size(); ++i) {
        for (int j = 0; j < (int)groups[i].size(); ++j) {
            if (isValidCollision(a, groups[i][j])) {
                if (searchForCollision(a, groups[i][j], offset)) {
                    return CollisionInfo{ 
                                isValidCollision(a, groups[i][j]), 
                                groups[i][j], 
                                false };
                }
            }
        }
    }
	*/
    return CollisionInfo{ false, NULL, false};
}

CollisionSystem::CollisionInfo CollisionSystem::isTriggering(Collision* a, const glm::vec2 &offset) {
	glm::vec4 box = a->getBoundingBox();

	glm::vec2 pos = glm::vec2((box.x + box.z) / 2.0f, (box.y + box.w) / 2.0f);
	float radius = glm::distance(pos, glm::vec2(box.x, box.y));

	int coll = a->collisionGroup;
	set<int> collidersGroup;

	for (int i = 0; i < triggersMatrix[coll].size(); ++i) {
		if (triggersMatrix[coll][i]) collidersGroup.insert(i);
	}

	set<Collision*> objects = spatialHashmap->getNearByObjects(pos, radius, collidersGroup);
	set<Collision*>::iterator it = objects.begin();

	while (it != objects.end()) {
		if (searchForCollision(a, *it, offset)) {
			return CollisionInfo{
				true,
				*it,
				false };
		}
		++it;
	}
	
	/*for (int i = 0; i < (int)groups.size(); ++i) {
        for (int j = 0; j < (int)groups[i].size(); ++j) {
            if (isTriggerCollision(a, groups[i][j])) {
                if (searchForCollision(a, groups[i][j], offset)) {
                    return CollisionInfo{ 
                                false, 
                                groups[i][j], 
                                isTriggerCollision(a, groups[i][j]) };
                }
            }
        }
    }
	*/
    return CollisionInfo{ false, NULL, false };
}

bool CollisionSystem::searchForCollision(const Collision* a, const Collision* b, const glm::vec2 &offset) {
    for (int i = 0; i < a->collidersSize; ++i) {
        for (int j = 0; j < b->collidersSize; ++j) {
            glm::vec4 colliderA = a->collisions[i];
            glm::vec4 colliderB = b->collisions[j];
            glm::vec2 posA = a->position + offset;

            if ((posA.x + colliderA.x) >= 500.0f) {
                return false;
            } else if ((b->position.x + colliderB.x) >= 500.0f) {
                return false;
            }

            if (overlapHorizontal(colliderA, colliderB, posA, b->position)) {
                return true;
            }
        }
    }

    return false;
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
