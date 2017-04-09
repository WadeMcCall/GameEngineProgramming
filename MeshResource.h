#if !defined MESH_RESOURCE
#define MESH_RESOURCE

#include "GameResource.h"

class GameManager;

class MeshResource : public GameResource{
	private:
		GameManager* game_manager;
		
	public:
		MeshResource(std::string level_name, std::string mesh, GameResourceType type, GameManager* gm);
		virtual ~MeshResource();
		
		virtual void load(GameManager* game_manager);
		virtual void unload(GameManager* game_manager);
};
#endif