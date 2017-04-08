#include "AudioResource.h"
#include "GameManager.h"

#include <cstdlib>

std::string AudioResource::getAudioResourceName(){
	return audio_resource_name;
}

AudioResourceType AudioResource::getAudioResourceType(){
	return audio_resource_type;
}