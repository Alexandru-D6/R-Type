#include "SpatialHashmap.h"

SpatialHashmap::SpatialHashmap(int size) {
	hashSize = size;
}

SpatialHashmap::~SpatialHashmap() {} 

void SpatialHashmap::insertObject(Collision* a) {
    glm::ivec4 cells = a->colliderBox;

    cells.x += a->position.x + tileMapPos;
    cells.y += a->position.y;
    cells.z += a->position.x + tileMapPos;
    cells.w += a->position.y;

    cells.x /= hashSize;
    cells.z /= hashSize;
    cells.y /= hashSize;
    cells.w /= hashSize;

    a->cells = cells;

	for (int i = cells.x; i <= cells.z; ++i) {
		for (int j = cells.y; j <= cells.w; ++j) {
			pair<int, int> index = make_pair(i, j);
			Hashmap[index][a->collisionGroup].insert(a);
		}
	}
}

void SpatialHashmap::insertObject(Collision* a, const glm::vec2 &pos) {
	glm::ivec4 cells = a->colliderBox;

    cells.x += pos.x + tileMapPos;
    cells.y += pos.y;
    cells.z += pos.x + tileMapPos;
    cells.w += pos.y;

    cells.x /= hashSize;
    cells.z /= hashSize;
    cells.y /= hashSize;
    cells.w /= hashSize;

    a->cells = cells;

	for (int i = cells.x; i <= cells.z; ++i) {
		for (int j = cells.y; j <= cells.w; ++j) {
			pair<int, int> index = make_pair(i, j);
			Hashmap[index][a->collisionGroup].insert(a);
		}
	}
}

void SpatialHashmap::removeObject(Collision* a) {
	for (int i = a->cells.x; i <= a->cells.z; ++i) {
		for (int j = a->cells.y; j <= a->cells.w; ++j) {
			pair<int, int> index = make_pair(i, j);
			Hashmap[index][a->collisionGroup].erase(a);
		}
	}
}

void SpatialHashmap::updateObject(Collision* a, const glm::vec2 &newPos) {
    glm::ivec4 boundingBox2 = a->colliderBox;

    boundingBox2.x += newPos.x + tileMapPos;
    boundingBox2.y += newPos.y;
    boundingBox2.z += newPos.x + tileMapPos;
    boundingBox2.w += newPos.y;

    boundingBox2.x /= hashSize;
    boundingBox2.z /= hashSize;
    boundingBox2.y /= hashSize;
    boundingBox2.w /= hashSize;

    if (a->cells.x == boundingBox2.x && 
        a->cells.y == boundingBox2.y &&
        a->cells.z == boundingBox2.z &&
        a->cells.w == boundingBox2.w
        ) return;

	removeObject(a);
	insertObject(a, newPos);
}

set<Collision*> SpatialHashmap::getNearByObjects(const glm::vec2 &pos, const int &radius, const set<int> &groups) {
	glm::vec4 cells = glm::vec4(pos.x-radius, pos.y-radius, pos.x+radius, pos.y+radius);

    cells.x += tileMapPos;
    cells.z += tileMapPos;

    cells.x /= hashSize;
    cells.z /= hashSize;
    cells.y /= hashSize;
    cells.w /= hashSize;

	set<Collision*> result;

	for (int i = cells.x; i <= cells.z; ++i) {
		for (int j = cells.y; j <= cells.w; ++j) {
			pair<int, int> index = make_pair(i, j);

			map<int, set<Collision*>> tmp = Hashmap[index];
			map<int, set<Collision*>>::iterator it = tmp.begin();

			while (it != tmp.end()) {
				if (groups.find(it->first) != groups.end()) {
					result.insert(it->second.begin(), it->second.end());
				}
				++it;
			}
		}
	}

	return result;
}
