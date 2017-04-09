#if !defined GAME_MANAGER
#define GAME_MANAGER

#include <string>
#include <vector>
#include "LogManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "ResourceManager.h"
#include "AudioResource.h"

class RenderManager;

//supplies communication between managers
class GameManager
{
   private:
      RenderManager* render_manager;
	  LogManager* log_manager;
	  InputManager* input_manager;
	  ResourceManager* resource_manager;
	  AudioManager* audio_manager;
	  ListArray<AudioResource>* audio_resources;

      GameManager();
      void init();

   public:
      virtual ~GameManager();
      static GameManager* getGameManager();
	  void keyPressed(std::string key);
	  void keyReleased(std::string key);
	  void checkForInput(float time_step);
	  void logProblem(std::string msg, std::string filename, int line);
	  void logComment(std::string msg);
	  void leftJoystickAxisMoved(float north_south, float east_west);
	  void rightJoystickAxisMoved(float north_south, float east_west);
	  void triggerMoved(float amount);
      int getRenderWindowWidth();
      int getRenderWindowHeight();
      size_t getRenderWindowHandle();
	  std::string getLoadedLevelName();
	  
	  void attachEntity(std::string entity_name_str, std::string entity_mesh_str, std::string entity_material_str, std::string entity_scene_node_name_str);	  
	  void createSceneNode(std::string child_name_str, std::string parent_name_str);	  
	  void processScale(float* scale, std::string scene_node_name_str);	  
	  void processRotation(float* rotation, std::string scene_node_name_str);	  
	  void processTranslation(float* translation, std::string scene_node_name_str);	  
	  void createLight(std::string light_name, float* light_color, float* light_direction);
	  void createCamera(std::string camera_name, float* camera_position, float* camera_lookat, float* clip); 
	  void unloadLevel(std::string level_name);	  
	  void loadLevel(std::string level_name);	  
	  void addPathResource(std::string path, std::string level_name);	  
	  void addMeshResource(std::string mesh_file_name, std::string level_name);
	  void createAnimation(std::string animation_node_str, std::string animation_name_str, float seconds, std::vector<float> key_frame_times, std::vector<float*> key_frame_translate, std::vector<float*> key_frame_rotate);
	  
	  void addAudioResource(AudioResource* ar);
	  void unloadStreamAudioResource(AudioResourceInfo* audio_info);
	  void playAudio(AudioResource* audio_resource, uint32 num_repeats);
	  //void playResourceAudio(std::string audio_name, int num_repeats);
	  void updateAudio(float time_step);
	  AudioResourceInfo* createAudioResourceInfo();
	  void loadSampleAudioResource(std::string audio_file_name, AudioResourceInfo* audio_info);
	  void loadStreamAudioResource(std::string audio_file_name, AudioResourceInfo* audio_info);
	  void unloadSampleAudioResource(AudioResourceInfo* audio_info);
	  void playAudioByName(std::string name, int times);
};
#endif
