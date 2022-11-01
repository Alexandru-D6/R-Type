#include "AudioManager.h"
#include "SDL.h"

AudioManager* AudioManager::instance_ = nullptr;

AudioManager *AudioManager::getInstance() {
	if (instance_ == nullptr) instance_ = new AudioManager();
	return instance_;
}

AudioManager::AudioManager() {
	SDL_Init(SDL_INIT_AUDIO);

	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;

	int result = Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);

	if (result != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %S", Mix_GetError());
		exit(-1);
	}
}

AudioManager::~AudioManager() {
}

void AudioManager::init() {

	//auto memory = nqr::ReadFile("sounds/Running-in-the-90s.mp3");
	//loader->Load(fileData.get(), "mp3", memory.buffer);

}

int AudioManager::addSoundEffect(const char* soundFile) {
	Mix_Chunk* tmpChunk = Mix_LoadWAV(soundFile);

	if (tmpChunk != nullptr) {
		mSoundEffectBank.push_back(tmpChunk);
	}
}

void AudioManager::playSoundEffect(int sound) {
	Mix_PlayChannel(-1, mSoundEffectBank[sound], 0);
}
