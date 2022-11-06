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

	glm::vec2 rearAnchorPoint;
	glm::vec2 frontAnchorPoint;

private:

	void init();
	int idBody;
};

class Worm : public Character {

public:

	Worm(glm::mat4 *project, int id);

	void update(int deltaTime);
	void render();

	void rotateSprites(const glm::vec2 &vector);
	void setPosition(const glm::vec2 &pos);

private:

	void init();
	std::vector<Part*> parts;
};

#endif // _WORM_INCLUDE

