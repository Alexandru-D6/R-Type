#ifndef _COLLISION_INCLUDE
#define _COLLISION_INCLUDE

#include <glm/glm.hpp>
#include <vector>

#include "TrianglesRenderer.h"
#include "CollisionSystem.h"

// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class Collision {

public:
	Collision();
	Collision(const glm::mat4 &project, CollisionSystem::CollisionGroups group);
	~Collision();

	void setProjection(const glm::mat4 &project);

	void addCollider(const glm::ivec4 &boxCollider);
	void removeCollider(const glm::ivec4 &boxCollider);

	void changePositionAbsolute(const glm::ivec2 &pos);
	void changePositionRelative(const glm::ivec2 &pos);

#ifdef DEBUG
	void showHitBox();
	void render();
#endif // DEBUG
	
public:

	CollisionSystem::CollisionGroups collisionGroup;

private:
	int collidersSize;
	glm::ivec4 *collisions;

	TrianglesRenderer* trianglesRenderer;

	glm::ivec2 position;

};


#endif // _COLLISION_INCLUDE


