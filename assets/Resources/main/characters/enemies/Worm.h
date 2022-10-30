#ifndef _WORM_INCLUDE
#define _WORM_INCLUDE

#include "characters\Character.h"


class Worm : public Character {

public:

	Worm(glm::mat4 *project, int id, const glm::ivec2 &tileMapPos);

	void update(int deltaTime);

private:

	void init(const glm::ivec2 &tileMapPos);
};

#endif // _WORM_INCLUDE

class Part : public Character {
public:

	Part(glm::mat4 *project, int id, const glm::ivec2 &tileMapPos);

	void update(int deltaTime);

private:

	void init(const glm::ivec2 &tileMapPos);
};