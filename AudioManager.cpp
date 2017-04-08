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
	
}