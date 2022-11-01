#ifndef _SPATIAL_HASHMAP_INCLUDE
#define _SPATIAL_HASHMAP_INCLUDE

#include <Set>
#include <Map>

#include "Collision.h"

class SpatialHashmap {
public:

	/**
	*
	* Size should be power of 2
	**/
	SpatialHashmap(int size = 32);
	~SpatialHashmap();

	void setTileMapPos(float pos) { tileMapPos = pos; };

	void insertObject(Collision* a);
	void insertObject(Collision* a, const glm::vec2 &pos);
	void removeObject(Collision* a);
	void updateObject(Collision* a, const glm::vec2 &newPos);

	set<Collision*> getNearByObjects(const glm::vec2 &pos, const int &radius, const set<int> &groups);

private:

	map<pair<int, int>, map<int, set<Collision*>>> Hashmap;

	int hashSize;
	float tileMapPos = 0;
};

#endif // _SPATIAL_HASHMAP_INCLUDE

