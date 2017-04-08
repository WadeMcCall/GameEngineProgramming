#if !defined AUDIO_MANAGER
#define AUDIO_MANAGER

#include "GameHeader.h"
#include "bass.h"
#include "ListArray.h"
#include <sstream>

class GameManager;
class AudioPlayer;
class AudioResource;
struct AudioResourceInfo;

class AudioManager{
	private:
		GameManager* game_manager;
		ListArray<AudioPlayer>* audio_players;
		
		BASS_DEVICEINFO device_info;
}