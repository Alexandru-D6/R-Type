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

void CharacterFactory::destroyCharacter(const int &id) {
	pendingToBeDestroyed.insert(id);
}
void CharacterFactory::lateDestroyCharacter() {
	for (auto it = pendingToBeDestroyed.begin(); it != pendingToBeDestroyed.end(); ++it) {
		characters[*it]->deleteRoutine();
		delete characters[*it];
		characters.erase(*it);
	}
	pendingToBeDestroyed.clear();
}

void CharacterFactory::init() {

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
		pair<CharacterAvailable, glm::vec2> enemy;
		glm::vec2 coord;
		int type;

		getline(fin, line);
		sstream.str(line);
		sstream >> type >> coord.x >> coord.y;

		enemy.first = (CharacterAvailable)type;
		enemy.second = coord;

		enemies.push_back(enemy);
	}

	fin.close();
}

void CharacterFactory::spawnCharacter(int type, const glm::vec2 &pos) {

	Character *character = nullptr;
	switch (type) {
		case cPlayer:
			if (player==nullptr) {
				player = new Player(projection, last_id, tileMapPos);
				player->setPosition(pos);
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
		default:
			character = new Enemy1(projection, last_id, tileMapPos);
			character->setPosition(pos);
			break;
	}
	if(character!=nullptr)characters[last_id] = character;
	++last_id;


}

void CharacterFactory::update(int deltaTime) {
	if(player != nullptr)player->update(deltaTime);
	for (auto it = characters.begin(); it != characters.end(); it++) {
		it->second->update(deltaTime);
	}

	spawnRoutine();
	lateDestroyCharacter();
}

void CharacterFactory::render() {
	if (player != nullptr)player->render();
	for (auto it = characters.begin(); it != characters.end(); it++) {
		it->second->render();
	}
}

void CharacterFactory::setTileMapPos(const glm::vec2 &pos){
	tileMapPos = pos;
}

void CharacterFactory::setMap(TileMap *map) {
	mapa = map;
}

void CharacterFactory::spawnRoutine() {
	float x1 = (float)mapa->getPosition() + COORD_VIEW_LIMIT_X;
	float x2 = x1 + 50.0f;

	vector<pair<CharacterAvailable, glm::vec2>>::iterator it = enemies.begin();
	while (it != enemies.end()) {
		if (it->second.x >= x1 && it->second.x <= x2) {
			spawnCharacter(it->first, it->second);

			// TODO: maybe add it purge to avoid revise all the previous generated enemies
		}
		++it;
	}
}
