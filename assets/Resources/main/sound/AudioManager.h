#ifndef _AUDIO_MANAGER_INCLUDE
#define _AUDIO_MANAGER_INCLUDE

#include <string.h>
#include <iostream>
#include <vector>

#include "SDL_mixer.h"

class AudioManager {

private :

	static AudioManager *instance_;

public:

	enum soundNames {RunningInThe90s, };

	static AudioManager *getInstance();

private:

	AudioManager();
	~AudioManager();

public:

	void init();

	int addSoundEffect(const char* soundFile);
	void playSoundEffect(int sound);

private:

	std::vector<Mix_Chunk*> mSoundEffectBank;

};

#endif // _AUDIO_MANAGER_INCLUDE
