#include "PathResource.h"
#include "GameManager.h"
#include <iostream>

PathResource::PathResource(std::string level_name, std::string path, GameResourceType type, GameManager* gm) : GameResource(level_name,path,type){
	game_manager = gm;
}

PathResource::~PathResource(){
	game_manager = NULL;
}

void PathResource::load(){
	std::cout << "here";
	game_manager->logComment("addingPathResource");
	game_manager->addPathResource(getResourceFileName(),getResourceLevelName());
	is_loaded = true;
}

void PathResource::unload(){
	is_loaded = false;
}