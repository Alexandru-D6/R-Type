#include "SpatialHashmap.h"

SpatialHashmap::SpatialHashmap(int size) {
	hashSize = size;
}

SpatialHashmap::~SpatialHashmap() {} 

void SpatialHashmap::insertObject(Collision* a) {
	for (int i = 0; i < a->collidersSize; ++i) {
		glm::vec4 boundingBox = a->collisions[i];

		boundingBox.x += a->position.x + tileMapPos;
		boundingBox.y += a->position.y;
		boundingBox.z += a->position.x + tileMapPos;
		boundingBox.w += a->position.y;

		int i1 = boundingBox.x / hashSize;
		int i2 = boundingBox.z / hashSize;
		int j1 = boundingBox.y / hashSize;
		int j2 = boundingBox.w / hashSize;

		for (int i = i1; i <= i2; ++i) {
			for (int j = j1; j <= j2; ++j) {
				pair<int, int> index = make_pair(i, j);
				Hashmap[index][a->collisionGroup].insert(a);
			}
		}
	}
}

void SpatialHashmap::insertObject(Collision* a, const glm::vec2 &pos) {
	for (int i = 0; i < a->collidersSize; ++i) {
		glm::vec4 boundingBox = a->collisions[i];

		boundingBox.x += pos.x + tileMapPos;
		boundingBox.y += pos.y;
		boundingBox.z += pos.x + tileMapPos;
		boundingBox.w += pos.y;

		int i1 = boundingBox.x / hashSize;
		int i2 = boundingBox.z / hashSize;
		int j1 = boundingBox.y / hashSize;
		int j2 = boundingBox.w / hashSize;

		for (int i = i1; i <= i2; ++i) {
			for (int j = j1; j <= j2; ++j) {
				pair<int, int> index = make_pair(i, j);
				Hashmap[index][a->collisionGroup].insert(a);
			}
		}
	}
}

void SpatialHashmap::removeObject(Collision* a) {
	for (int i = 0; i < a->collidersSize; ++i) {
		glm::vec4 boundingBox = a->collisions[i];

		boundingBox.x += a->position.x + tileMapPos;
		boundingBox.y += a->position.y;
		boundingBox.z += a->position.x + tileMapPos;
		boundingBox.w += a->position.y;

		int i1 = boundingBox.x / hashSize;
		int i2 = boundingBox.z / hashSize;
		int j1 = boundingBox.y / hashSize;
		int j2 = boundingBox.w / hashSize;

		for (int i = i1; i <= i2; ++i) {
			for (int j = j1; j <= j2; ++j) {
				pair<int, int> index = make_pair(i, j);
				Hashmap[index][a->collisionGroup].erase(a);
			}
		}
	}
}

void SpatialHashmap::updateObject(Collision* a, const glm::vec2 &newPos) {
	// TODO: improve algorithm
	if (a->position != newPos) {
		removeObject(a);
		insertObject(a, newPos);
	}
}

set<Collision*> SpatialHashmap::getNearByObjects(const glm::vec2 &pos, const int &radius, const set<int> &groups) {
	glm::vec4 boundingBox = glm::vec4(pos.x-radius, pos.y-radius, pos.x+radius, pos.y+radius);

	boundingBox.x += tileMapPos;
	boundingBox.z += tileMapPos;

	int i1 = boundingBox.x / hashSize;
	int i2 = boundingBox.z / hashSize;
	int j1 = boundingBox.y / hashSize;
	int j2 = boundingBox.w / hashSize;

	set<Collision*> result;

	for (int i = i1; i <= i2; ++i) {
		for (int j = j1; j <= j2; ++j) {
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
