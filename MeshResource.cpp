#include "MeshResource.h"
#include "GameManager.h"

MeshResource::MeshResource(std::string level_name, std::string mesh, GameResourceType type, GameManager* gm) : GameResource(level_name,mesh,type){
	game_manager = gm;
}

MeshResource::~MeshResource(){
	game_manager = NULL;
}

void MeshResource::load(){
	game_manager->logComment("addingMeshResource");
	game_manager->addMeshResource(getResourceFileName(),getResourceLevelName());
	is_loaded = true;
}

void MeshResource::unload(){
	is_loaded = false;
}