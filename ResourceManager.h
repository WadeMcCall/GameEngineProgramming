#if !defined RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <string>
#include "ListArray.h"

class GameManager;
class GameXML;
class GameResource;

class ResourceManager{
	private:
		GameManager* game_manager;
		GameXML* game_xml;
		
		ListArray<GameResource>* game_resources_by_level;		
		std::string loaded_level_name;
		
	public:
		ResourceManager(const char* resource_file_name, const char* scenes_file_name, GameManager* gm);
		virtual ~ResourceManager();
		
		void unloadLevel();
		void loadLevel(std::string requested_level_name);
		
		void addPathResource(std::string path, std::string level_name);
		void addMeshResource(std::string mesh_file_name, std::string level_name);
};
#endif