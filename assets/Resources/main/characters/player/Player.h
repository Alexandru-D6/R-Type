#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "sound\AudioManager.h"
#include "characters\Character.h"
#include "ForceDevice.h"
#include "ui\Text.h"

class Player : public Character {

private:

	enum PlayerAnims {STAND_RIGHT, STAND_UP, STAND_DOWN, MOVE_UP, MOVE_DOWN, DOWN_RETURN, UP_RETURN };

public:

    Player(glm::mat4 *project, int id, const glm::ivec2 &tileMapPos);
    void update(int deltaTime);
	void render();

	bool isPlayer() { return true; };

	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition() { return pos; };

	void inputController();

	void damage(int dmg) override;

private:

	void init(const glm::ivec2 &tileMapPos);
    

private:

    ForceDevice *forceDevice;
	Text text;
	bool godmode = false;
	int contGod = 0;
    bool latchKeys[256];

};

#endif // _PLAYER_INCLUDE
