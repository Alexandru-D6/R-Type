#include "SpatialHashmap.h"

SpatialHashmap::SpatialHashmap(int size) {
	hashSize = size;
}

SpatialHashmap::~SpatialHashmap() {} 

void SpatialHashmap::insertObject(Collision* a) {
    glm::ivec4 cells = a->colliderBox;

    cells.x += (int)(a->position.x + tileMapPos);
    cells.y += (int)(a->position.y);
    cells.z += (int)(a->position.x + tileMapPos);
    cells.w += (int)(a->position.y);

    cells.x /= hashSize;
    cells.z /= hashSize;
    cells.y /= hashSize;
    cells.w /= hashSize;

    a->cells = cells;

	for (int i = cells.x; i <= cells.z; ++i) {
		for (int j = cells.y; j <= cells.w; ++j) {
			Hashmap[i][j][(int)a->collisionGroup].insert(a);
		}
	}
}

void SpatialHashmap::insertObject(Collision* a, const glm::vec2 &pos) {
	glm::ivec4 cells = a->colliderBox;

    cells.x += (int)(pos.x + tileMapPos);
    cells.y += (int)(pos.y);
    cells.z += (int)(pos.x + tileMapPos);
    cells.w += (int)(pos.y);

    cells.x /= hashSize;
    cells.z /= hashSize;
    cells.y /= hashSize;
    cells.w /= hashSize;

    a->cells = cells;

	for (int i = cells.x; i <= cells.z; ++i) {
		for (int j = cells.y; j <= cells.w; ++j) {
			Hashmap[i][j][(int)a->collisionGroup].insert(a);
		}
	}
}

void SpatialHashmap::removeObject(Collision* a) {
	for (int i = a->cells.x; i <= a->cells.z; ++i) {
		for (int j = a->cells.y; j <= a->cells.w; ++j) {

			Hashmap[i][j][a->collisionGroup].erase(a);

            a->cells.z = -1;
            a->cells.w = -1;
		}
	}
}

void SpatialHashmap::updateObject(Collision* a, const glm::vec2 &newPos) {
    //return;
    glm::ivec4 boundingBox2 = a->colliderBox;

    boundingBox2.x += (int)(newPos.x + tileMapPos);
    boundingBox2.y += (int)(newPos.y);
    boundingBox2.z += (int)(newPos.x + tileMapPos);
    boundingBox2.w += (int)(newPos.y);

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

set<Collision*> SpatialHashmap::getNearByObjects(const glm::vec2 &pos, const int &radius, bool *groups) {
    set<Collision*> result;
    //return result;
	glm::vec4 cells = glm::vec4(pos.x-radius, pos.y-radius, pos.x+radius, pos.y+radius);

    cells.x += tileMapPos;
    cells.z += tileMapPos;

    cells.x /= hashSize;
    cells.z /= hashSize;
    cells.y /= hashSize;
    cells.w /= hashSize;

	for (int i = (int)cells.x; i <= (int)cells.z; ++i) {
		for (int j = (int)cells.y; j <= (int)cells.w; ++j) {
            for (int t = 0; t < 10; ++t) {
                if (groups[t]) {
                    result.insert(Hashmap[i][j][t].begin(), Hashmap[i][j][t].end());
                }
            }
		}
	}

	return result;
}
