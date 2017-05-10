#if !defined GAME_MANAGER_INTERFACE
#define GAME_MANAGER_INTERFACE

#include <vector>
#include "GameHeader.h"

struct AudioResourceInfo;
class AudioResource;

//supplies communication between managers
class GameManagerInterface
{
   protected:

   public:
      GameManagerInterface(){};
      virtual ~GameManagerInterface(){};
	  virtual void mouseMoved(uint32 x_click, uint32 y_click, float x_rel, float y_rel) = 0;
	  virtual void mousePressed(uint32 x_click, uint32 y_click, std::string mouse_button) = 0;
	  virtual void keyPressed(std::string key) = 0;
	  virtual void keyReleased(std::string key) = 0;
	  virtual void buttonPressed(std::string button) = 0;
	  virtual void checkForInput(float time_step) = 0;
	  virtual void logProblem(std::string msg, std::string filename, int line) = 0;
	  virtual void logComment(std::string msg) = 0;
	  virtual void leftJoystickAxisMoved(float north_south, float east_west) = 0;
	  virtual void rightJoystickAxisMoved(float north_south, float east_west) = 0;
	  virtual void triggerMoved(float amount) = 0;
      virtual int getRenderWindowWidth() = 0;
      virtual int getRenderWindowHeight() = 0;
      virtual size_t getRenderWindowHandle() = 0;
	  
	  virtual void attachEntity(std::string entity_name_str, std::string entity_mesh_str, std::string entity_material_str, std::string entity_scene_node_name_str) = 0;	  
	  virtual void createSceneNode(std::string child_name_str, std::string parent_name_str) = 0; 
	  virtual void processScale(float* scale, std::string scene_node_name_str) = 0;
	  virtual void processRotation(float* rotation, std::string scene_node_name_str) = 0;
	  virtual void processTranslation(float* translation, std::string scene_node_name_str) = 0;
	  virtual void createLight(std::string light_name, float* light_color, float* light_direction) = 0;
	  virtual void createCamera(std::string camera_name, float* camera_position, float* camera_lookat, float* clip) = 0;
	  virtual void unloadLevel(std::string level_name) = 0;
	  virtual void loadLevel(std::string level_name) = 0;
	  virtual void addPathResource(std::string path, std::string level_name) = 0;
	  virtual void addMeshResource(std::string mesh_file_name, std::string level_name) = 0;
	  virtual void createAnimation(std::string animation_node_str, std::string animation_name_str, float seconds, std::vector<float> key_frame_times, std::vector<float*> key_frame_translate, std::vector<float*> key_frame_rotate) = 0;
	  
	  virtual void addAudioResource(AudioResource* ar) = 0;
	  virtual void unloadStreamAudioResource(AudioResourceInfo* audio_info) = 0;
	  virtual void playAudio(AudioResource* audio_resource, uint32 num_repeats) = 0;
	  virtual void updateAudio(float time_step) = 0;
	  virtual AudioResourceInfo* createAudioResourceInfo() = 0;
	  virtual void loadSampleAudioResource(std::string audio_file_name, AudioResourceInfo* audio_info) = 0;
	  virtual void loadStreamAudioResource(std::string audio_file_name, AudioResourceInfo* audio_info) = 0;
	  virtual void unloadSampleAudioResource(AudioResourceInfo* audio_info) = 0;
	  virtual void playAudioByName(std::string name, int times) = 0;
	  
	  
	  virtual void createRigidBodies() = 0;
	  virtual void createCollisionShape(std::string child_name_str, std::string collision_shape_name_str, float* params, float mass, float* translation, float* rotation) = 0;
	  virtual void jump() = 0;
};
#endif
