#include "Collision.h"

using namespace std;

Collision::Collision() {
	collidersSize = 0;
	collisions = new glm::ivec4[1000];

	position = glm::ivec2(0, 0);
}

Collision::~Collision() {
	collidersSize = 0;

	position = glm::ivec2(0, 0);
}

void Collision::addCollider(const glm::ivec4 &boxCollider) {
	collisions[collidersSize] = boxCollider;
	collidersSize++;
}

void Collision::removeCollider(const glm::ivec4 &boxCollider) {
	// Unused
}

void Collision::changePositionAbsolute(const glm::ivec2 &pos) {
	position = pos;
}

void Collision::changePositionRelative(const glm::ivec2 &pos) {
	position += pos;
}

bool Collision::collisionMoveLeft(const Collision &a, const Collision &b) {
	for (int i = 0; i < a.collidersSize; ++i) {
		for (int j = 0; j < b.collidersSize; ++j) {
			if (overlapHorizontal(a.collisions[i], b.collisions[j], a.position, b.position)) {
				return true;
			}
		}
	}

	return false;
}

bool Collision::collisionMoveRight(const Collision &a, const Collision &b) {
	for (int i = 0; i < a.collidersSize; ++i) {
		for (int j = 0; j < b.collidersSize; ++j) {
			if (overlapHorizontal(a.collisions[i], b.collisions[j], a.position, b.position)) {
				return true;
			}
		}
	}

	return false;
}

bool Collision::collisionMoveDown(const Collision &a, const Collision &b) {
	/*glm::ivec4 objCollider = glm::ivec4(pos.x, pos.y, pos.x + size.x, pos.y+size.y);

	for (int i = 0; i < collidersSize; ++i) {
		if (overlapVertical(objCollider, collisions[i])) {
			*posY = pos.y-4;
			return true;
		}
	}
	*/
	return false;
}

bool Collision::collisionMoveUp(const Collision &a, const Collision &b) {
	/*glm::ivec4 objCollider = glm::ivec4(pos.x, pos.y, pos.x + size.x, pos.y + size.y);

	for (int i = 0; i < collidersSize; ++i) {
		if (overlapVertical(objCollider, collisions[i])) {
			*posY = pos.y - 4;
			return true;
		}
	}
	*/
	return false;
}

bool Collision::overlapVertical(const glm::ivec4 &a, const glm::ivec4 &b, const glm::ivec2 &posA, const glm::ivec2 &posB) {
	// if one rectangle is on left side of other
	/*if (r1[0] > r2[2] || r2[0] > r1[2]) {
		return false;
	}*/

	// if one rectangle is above other
	/*if (r1[3] < r2[1] || r1[1] > r2[3]) {
		return false;
	}*/

	return false;//return true;
}

bool Collision::overlapHorizontal(const glm::ivec4 &a, const glm::ivec4 &b, const glm::ivec2 &posA, const glm::ivec2 &posB) {
	// if one rectangle is on left side of other
	if (a[0] + posA.x > b[2] + posB.x || b[0] + posB.x > a[2] + posA.x) {
		return false;
	}

	// if one rectangle is above other
	if (a[3] + posA.y < b[1] + posB.y || a[1] + posA.y > b[3] + posB.y) {
		return false;
	}

	return true;
}































