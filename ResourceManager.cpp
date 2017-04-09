#include "ResourceManager.h"
#include "GameManager.h"
#include "AudioResource.h"
#include "GameXML.h"
#include "ListArrayIterator.h"
#include <iostream>

ResourceManager::ResourceManager(const char* resource_file_name, const char* scenes_file_name, GameManager* gm){
	loaded_level_name = "";
	game_manager = gm;	
	try{
		game_xml = new GameXML(resource_file_name, scenes_file_name);
	}
	catch(std::exception& e){
		ASSERT_CRITICAL(false, e.what());
	}
}

ResourceManager::~ResourceManager(){}

void ResourceManager::loadLevel(std::string requested_level_name){
	if(loaded_level_name != requested_level_name){
		game_resources_by_level = game_xml->getXMLGameResourcesByLevel(requested_level_name, game_manager);
		ListArrayIterator<GameResource>* game_resource_iter = game_resources_by_level->iterator();
		game_manager->logComment(requested_level_name);
		while(game_resource_iter->hasNext()){
			GameResource* gameResource = game_resource_iter->next();
			gameResource->load(game_manager);
		}
		game_manager->loadLevel(requested_level_name);
		game_xml->buildXMLScene(requested_level_name, game_manager);
	}
	loaded_level_name = requested_level_name;
}

void ResourceManager::unloadLevel(){
	game_manager->unloadLevel(loaded_level_name);
	loaded_level_name = "";
}

//AudioResource* ResourceManager::getAudioResourceByName(std::string audio_name){
//	ListArrayIterator<GameResource>* game_resource_iter = game_resources_by_level->iterator();
//	int i = 0;
//	while(game_resource_iter->hasNext()){
//		GameResource* gr = game_resource_iter->next();
//		if(gr->getResourceType() == AUDIO){
//			AudioResource* ar = game_resources_by_level->get(i);
//			if(ar->getAudioResourceName() == audio_name){
//				return ar;
//			}
//		}
//		i++;
//	}
//}

void ResourceManager::addPathResource(std::string path, std::string level_name){
	game_manager->addPathResource(path, level_name);
}


void ResourceManager::addMeshResource(std::string mesh_file_name, std::string level_name){
	game_manager->addMeshResource(mesh_file_name, level_name);
}