#ifndef _WORM_INCLUDE
#define _WORM_INCLUDE

#include "characters\Character.h"
#include <vector>

class Part : public Character {
public:

	Part(glm::mat4 *project, int id, int idBody);

	void update(int deltaTime);
	
	glm::vec2 getPosition() { return pos; };
	void setPosition(const glm::vec2 &pos);

private:

	void init();
	int idBody;
};

class Worm : public Character {

public:

	Worm(glm::mat4 *project, int id);

	void update(int deltaTime);
	void render();
	void setPosition(const glm::vec2 &pos);

private:

	void init();
	std::vector<Part*> parts;
};

#endif // _WORM_INCLUDE

