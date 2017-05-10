#include "AudioManager.h"
#include "AudioPlayer.h"
#include "AudioResource.h"
#include "GameManager.h"

struct AudioResourceInfo{
	HSAMPLE sample_data;
	HSAMPLE stream_data;
	HSAMPLE channel_data;
};

AudioResourceInfo* AudioManager::createAudioResourceInfo(){
	AudioResourceInfo* ar_info = (AudioResourceInfo*) malloc(sizeof(AudioResourceInfo));
	ar_info->sample_data = 0;
	ar_info->channel_data = 0;
	return ar_info;
}

void AudioManager::unloadSampleAudioResource(AudioResourceInfo* ar_info){
	if(!BASS_ChannelIsActive(ar_info->channel_data) == BASS_ACTIVE_STOPPED){
		BASS_ChannelStop(ar_info->channel_data);
	}
	
	BASS_SampleFree(ar_info->sample_data);
	ar_info->sample_data = 0;
	ar_info->channel_data = 0;
}

void AudioManager::unloadStreamAudioResource(AudioResourceInfo* ar_info){
	if(!BASS_ChannelIsActive(ar_info->channel_data) == BASS_ACTIVE_STOPPED){
		BASS_ChannelStop(ar_info->channel_data);
	}
	
	BASS_StreamFree(ar_info->stream_data);
	ar_info->stream_data = 0;
	ar_info->channel_data = 0;
}

void AudioManager::loadSampleAudioResource(std::string file_name, AudioResourceInfo* ar_info){
	ar_info->sample_data = BASS_SampleLoad(FALSE, file_name.c_str(), 0,0,1,0);
	if(ar_info->sample_data){
		ar_info->channel_data = BASS_SampleGetChannel(ar_info->sample_data, false);
	}
	else{
		ASSERT_LOG(false, "Sample Audio Resource Initialization Error: " + file_name);
	}
}

void AudioManager::loadStreamAudioResource(std::string file_name, AudioResourceInfo* ar_info){
	ar_info->stream_data = BASS_StreamCreateFile(FALSE, file_name.c_str(), 0,0,0);
	if(ar_info->stream_data){
		ar_info->channel_data = ar_info->stream_data;
	}
	else{
		ASSERT_LOG(false, "Stream Audio Resource Initialization Error: " + file_name);
	}
}

AudioManager::AudioManager(GameManager* gm){
	game_manager = gm;
	audio_players = new ListArray<AudioPlayer>();
	init();
}

AudioManager::~AudioManager(){
	game_manager = NULL;
	free();
	
	ListArrayIterator<AudioPlayer>* iter = audio_players->iterator();
	while(iter->hasNext()){
		AudioPlayer* ap = iter->next();
		delete ap;
	}
	
	delete iter;
	delete audio_players;
	audio_players = NULL;
}

void AudioManager::init(int Device, DWORD SampleRate, DWORD flags, HWND win){
	BOOL bassActive = BASS_Init(Device, SampleRate, flags, win, NULL);
	if(!bassActive){
		ASSERT_LOG(false, "Audio Manager Initialization Problem");
	}
	std::stringstream DeviceStringStream;
	if(BASS_GetDeviceInfo(Device, &device_info)){
		DeviceStringStream << "Audio Device Info. Name: " << device_info.name << "Driver: " << device_info.driver;
		device_info_str = DeviceStringStream.str();
		std::cout << device_info_str << std::endl;
	}
	else{
		BASS_Free();
		ASSERT_LOG(false, "Audio Manager Initialization Problem");
	}
}

void AudioManager::free(){
	BASS_Free();
}

void AudioManager::playAudio(AudioResource* ar, uint32 num_repeats){
	//if(audio_players->size() == 2) return;
	AudioPlayer* ap = new AudioPlayer(ar, num_repeats);
	addAudioPlayer(ap);
}

void AudioManager::addAudioPlayer(AudioPlayer* audio_player){
	audio_players->add(audio_player);
	
	AudioResource* audio_resource = audio_player->getAudioResource();
	AudioResourceInfo* ar_info = audio_resource->getAudioResourceInfo();
	BASS_ChannelPlay(ar_info->channel_data, false);
}

void AudioManager::updateAudio(float time_step){
	int num_players = audio_players->size();
	for(int i = 1; i < num_players; i++){
		AudioPlayer* audio_player = audio_players->get(i);
		AudioResource* audio_resource = audio_player->getAudioResource();
		AudioResourceInfo* ar_info = audio_resource->getAudioResourceInfo();
		
		if(BASS_ChannelIsActive(ar_info->channel_data) == BASS_ACTIVE_STOPPED){
			if(audio_player->getRepeatCount() >= audio_player->getNumRepeats()){
				audio_players->remove(i);
				delete audio_player;
				
				i--;
				num_players--;
			}
			else{
				audio_player->incRepeatCount();
				BASS_ChannelPlay(ar_info->channel_data, false);
			}
		}
	}
}