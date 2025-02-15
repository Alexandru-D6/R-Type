#ifndef _CHARACTER_FACTORY_INCLUDE
#define _CHARACTER_FACTORY_INCLUDE

#include <map>

#include "Character.h"
#include "enemies\Enemy1.h"
#include "enemies\Enemy2.h"
#include "enemies\Enemy3.h"
#include "enemies\Enemy4.h"
#include "enemies\Boss.h"
#include "enemies\Worm.h"
#include "player\Player.h"
#include "ExplosionFactory.h"

class CharacterFactory {

private:

	static CharacterFactory *instance_;
	CharacterFactory();
	~CharacterFactory();

	void lateDestroyCharacter();

public:
	enum CharacterAvailable{cPlayer, cEnemy1, cEnemy2, cEnemy3, cEnemy4, cBoss, cWormUp, cWormDown};

	static CharacterFactory *getInstance();
	static void deleteReference();

	void init();
	void update(int deltaTime);
	void render();

	void setProjection(glm::mat4 *project);
	void setSpawnFiles(string file);
	void setTileMapPos(const glm::vec2 &pos);
	void setMap(TileMap *map);

	bool getPlayerPos(glm::vec2 &pos);
	int getHealthCharacter(int id);

	void spawnCharacter(int type, const glm::vec2 &pos);
	void spawnRoutine();

	void destroyCharacter(const int &id);
	void destroyAllCharactersToTeleport();
	void destroyAllCharactersToEnd();
	void killCharacter(const int &id);
	void damageCharacter(const int &id, int dmg);
	void bossIsDead(bool dead);
	bool isBossDead();

	void exterminateWorms();


	void increasePlayerForce(int power);

	void wormRetun(int idSource, int idDest, bool upOrDown);
	Player *player = nullptr;
public:

	float mapSpeed;

private:
	
	glm::mat4 *projection;
	glm::vec2 tileMapPos;
	TileMap *mapa;

	
	map<int, Character *> characters;
	int last_id = 0;
	bool alive = false;
	int timer = -1;

	set<int> pendingToBeDestroyed;
	set<int> pendingToBeKilled;

	vector<pair<CharacterAvailable, glm::vec2>> enemies;
	int nextSpawn = 0;
	vector<int>IdreservedBoss;
	vector<int>IdreservedWorm1;
	vector<int>IdreservedWorm2;
	bool bossdead = false;

};

#endif // _CHARACTER_FACTORY_INCLUDE