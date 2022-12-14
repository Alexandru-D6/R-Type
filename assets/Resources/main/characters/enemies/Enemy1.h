#ifndef _Enemy1_INCLUDE
#define _Enemy1_INCLUDE

#include "characters\Character.h"

class Enemy1 : public Character {
	
public:

	Enemy1(glm::mat4 *project, int id, const glm::ivec2 &tileMapPos);
    void update(int deltaTime);

	void deleteRoutine();

private:

	enum Enemy1Anims {STAND_LEFT, MOVE_LEFT, FLY_LEFT, LANDING_LEFT, JUMP_LEFT};

	void init(const glm::ivec2 &tileMapPos);


	int jumpDelay;

};

#endif // _Enemy1_INCLUDE
