#ifndef _TEXTURE_MANAGER_INCLUDE
#define _TEXTURE_MANAGER_INCLUDE

#include <map>
#include "utilities\Texture.h"
class TextureManager {

private:

	static TextureManager *instance_;
	TextureManager();
	~TextureManager();

public:
	enum Textures { Map, Planets, Player, Force, Projectiles, Enemies, Boss, PoweUp};
	static TextureManager *getInstance();
	Texture getSpriteSheet(Textures type);

private:
	map<Textures, Texture> textures;
};

#endif // _TEXTURE_MANAGER_INCLUDE
