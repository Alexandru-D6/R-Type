#ifndef _WORM_INCLUDE
#define _WORM_INCLUDE

#include "characters\Character.h"
#include <vector>

class Part : public Character {
public:

	Part(glm::mat4 *project, int id, int idBody);

	void update(int deltaTime);
	
	void rotateSprite(glm::vec3 rotation);
	glm::vec2 getPosition() { return pos; };
	void setPosition(const glm::vec2 &pos);

public:

	glm::vec2 anchorPoint;
	glm::vec2 lastDir;

private:

	void init();
	int idBody;
};

class Worm : public Character {

public:

	Worm(glm::mat4 *project, int id);

	void update(int deltaTime);
	void render();

	void rotateSprite(Part *part, const glm::vec2 &vector);
	void setPosition(const glm::vec2 &movement);

private:

	glm::vec2 targetPosition;
	int currentTarget = 0;

	glm::vec2 position[4] = {	glm::vec2(225.0f,128.0f),
								glm::vec2(350.0f,50.0f),
								glm::vec2(50.0f,50.0f),
								glm::vec2(50.0f,50.0f) };
	
	void changeTarget();
	glm::vec2 getDir(const glm::vec2 &posA, const glm::vec2 &posB);

private:

	void init();
	std::vector<Part*> parts;
};

#endif // _WORM_INCLUDE

