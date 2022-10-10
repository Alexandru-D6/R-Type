#ifndef _COLLISION_INCLUDE
#define _COLLISION_INCLUDE

#include <glm/glm.hpp>
#include <vector>

// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class Collision {

public:
	Collision();
	~Collision();

	void setInitColliderPos();

	void addCollider(const glm::ivec4 &boxCollider);
	void removeCollider(const glm::ivec4 &boxCollider);

	void changePositionAbsolute(const glm::ivec2 &pos);
	void changePositionRelative(const glm::ivec2 &pos);

	static bool collisionMoveLeft(const Collision &a, const Collision &b);
	static bool collisionMoveRight(const Collision &a, const Collision &b);
	static bool collisionMoveDown(const Collision &a, const Collision &b);
	static bool collisionMoveUp(const Collision &a, const Collision &b);
	
private:
	static bool overlapVertical(const glm::ivec4 &a, const glm::ivec4 &b, const glm::ivec2 &posA, const glm::ivec2 &posB);
	static bool overlapHorizontal(const glm::ivec4 &a, const glm::ivec4 &b, const glm::ivec2 &posA, const glm::ivec2 &posB);

private:
	int collidersSize;
	glm::ivec4 *collisions;

	glm::ivec2 position;

};


#endif // _COLLISION_INCLUDE


