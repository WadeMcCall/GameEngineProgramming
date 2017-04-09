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
		std::string device_info_str;
		
	public:
		AudioManager(GameManager* gm);
		virtual ~AudioManager();
		
		AudioResourceInfo* createAudioResourceInfo();
		
		void init(int Device = 1, DWORD SampleRate = 44100, DWORD flags = 0, HWND win = 0);
		void free();
		
		void setVolume(float volume){BASS_SetVolume(volume);}
		void pause(){BASS_Pause();}
		void start(){BASS_Start();}
		
		void addAudioPlayer(AudioPlayer* audio_player);
		
		void updateAudio(float time_step);
		void playAudio(AudioResource* ar, uint32 num_repeats);
		
		void loadSampleAudioResource(std::string file_name, AudioResourceInfo* ar_info);
		void loadStreamAudioResource(std::string file_name, AudioResourceInfo* ar_info);
		
		void unloadSampleAudioResource(AudioResourceInfo* ar_info);
		void unloadStreamAudioResource(AudioResourceInfo* ar_info);
};
#endif