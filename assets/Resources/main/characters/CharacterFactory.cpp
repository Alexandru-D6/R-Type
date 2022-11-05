#include "CharacterFactory.h"


CharacterFactory* CharacterFactory::instance_ = nullptr;

CharacterFactory *CharacterFactory::getInstance() {
	if (instance_ == nullptr) instance_ = new CharacterFactory();
	return instance_;
}

CharacterFactory::CharacterFactory() {
	
}

CharacterFactory::~CharacterFactory() {
}

void CharacterFactory::lateDestroyCharacter() {
	for (auto it = pendingToBeDestroyed.begin(); it != pendingToBeDestroyed.end(); ++it) {
		characters[*it]->deleteRoutine();

		if (characters[*it] == player) player = nullptr;

		delete characters[*it];
		characters.erase(*it);
	}
	pendingToBeDestroyed.clear();

	for (auto it = pendingToBeKilled.begin(); it != pendingToBeKilled.end(); ++it) {
		if (characters.find(*it) != characters.end()) {
			characters[*it]->deleteRoutine();

			if (characters[*it] == player) player = nullptr;

			delete characters[*it];
			characters.erase(*it);
		}
	}
	pendingToBeKilled.clear();
}

void CharacterFactory::init() {

}

void CharacterFactory::update(int deltaTime) {
	for (auto it = characters.begin(); it != characters.end(); it++) {
		it->second->update(deltaTime);
	}

	spawnRoutine();
	lateDestroyCharacter();
}

void CharacterFactory::render() {
	for (auto it = characters.begin(); it != characters.end(); it++) {
		it->second->render();
	}
}

void CharacterFactory::setProjection(glm::mat4 *project) {
	projection = project;
}

void CharacterFactory::setSpawnFiles(string file) {
	ifstream fin;
	string line;
	stringstream sstream;
	int nrEntities;

	fin.open(file.c_str());
	if (!fin.is_open()) return;
	getline(fin, line);
	sstream.str(line);
	sstream >> nrEntities;

	for (int i = 0; i < nrEntities; ++i) {
		stringstream sstream1;
		pair<CharacterAvailable, glm::vec2> enemy;
		glm::vec2 coord;
		int type;

		getline(fin, line);
		sstream1.str(line);
		sstream1 >> type >> coord.x >> coord.y;

		enemy.first = (CharacterAvailable)type;
		enemy.second = coord;

		enemies.push_back(enemy);
	}

	fin.close();
}

void CharacterFactory::setTileMapPos(const glm::vec2 &pos) {
	tileMapPos = pos;
}

void CharacterFactory::setMap(TileMap *map) {
	mapa = map;
}

bool CharacterFactory::getPlayerPos(glm::vec2 &pos) {
	if (player == nullptr) return false;

	pos = player->getPosition();
	return true;
}

void CharacterFactory::spawnCharacter(int type, const glm::vec2 &pos) {

	Character *character = nullptr;
	switch (type) {
	case cPlayer:
		if (player == nullptr) {
			player = new Player(projection, last_id, tileMapPos);
			player->setPosition(pos);
			character = player;
		}
		break;
	case cEnemy1:
		character = new Enemy1(projection, last_id, tileMapPos);
		character->setPosition(pos);
		break;
	case cEnemy2:
		character = new Enemy2(projection, last_id, tileMapPos);
		character->setPosition(pos);
		break;
	case cEnemy3:
		character = new Enemy3(projection, last_id, tileMapPos);
		character->setPosition(pos);
		break;
	case cEnemy4:
		character = new Enemy4(projection, last_id, tileMapPos);
		character->setPosition(pos);
		break;
	case cBoss:
		character = new Boss(projection, last_id, tileMapPos);
		character->setPosition(pos);
		break;
	case cWorm:
		character = new Worm(projection, last_id, tileMapPos);
		character->setPosition(pos);
		break;
	default:
		character = new Enemy1(projection, last_id, tileMapPos);
		character->setPosition(pos);
		break;
	}
	if (character != nullptr)characters[last_id] = character;
	++last_id;


}

void CharacterFactory::spawnRoutine() {
	float x1 = COORD_VIEW_LIMIT_X;
	float x2 = x1 + 25.0f;
	float mapOffset = mapa->getPosition();

	if (nextSpawn >= (int)enemies.size()) return;

	glm::vec2 tempPos = enemies[nextSpawn].second;
	tempPos.x += mapOffset;

	// Loop to discard all the enemies that can not spawn because its position
	while (nextSpawn < (int)enemies.size() && tempPos.x < x1) {
		++nextSpawn;

		if (nextSpawn < (int)enemies.size()) {
			tempPos = enemies[nextSpawn].second;
			tempPos.x += mapOffset;
		}
	}

	// Actual loop that spawn the following enemy
	while (nextSpawn < (int)enemies.size() && tempPos.x >= x1 && tempPos.x <= x2) {
		// TODO: Change '2' to nextSpawn->first
		spawnCharacter(2, tempPos);

		++nextSpawn;
		if (nextSpawn < (int)enemies.size()) {
			tempPos = enemies[nextSpawn].second;
			tempPos.x += mapOffset;
		}
	}
}

void CharacterFactory::destroyCharacter(const int &id) {
	pendingToBeDestroyed.insert(id);
}

void CharacterFactory::destroyAllCharacters() {
	map<int, Character *>::iterator it = characters.begin();

	while (it != characters.end()) {
		if (it->first != player->getId()) pendingToBeDestroyed.insert(it->first);
		++it;
	}
	nextSpawn = 0;
}

void CharacterFactory::killCharacter(const int &id) {
	pendingToBeKilled.insert(id);
	auto it = characters.find(id);
	if (it != characters.end()) {
		if(player != nullptr && player->getId() == id){
			ExplosionFactory::getInstance()->spawnExplosion(Explosion::Explosions::ExplosionPlayer, projection, it->second->getPosition(), it->second->getBoundingBox());
		}
		else ExplosionFactory::getInstance()->spawnExplosion(Explosion::Explosions::ExplosionEnemy,projection,it->second->getPosition(),it->second->getBoundingBox());
	}
}

void CharacterFactory::damageCharacter(const int &id, int dmg) {
	auto search = characters.find(id);
	if (search != characters.end()) search->second->damage(dmg);
}