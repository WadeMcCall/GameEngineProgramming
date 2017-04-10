#if !defined RENDER_MANAGER
#define RENDER_MANAGER

#include "Ogre.h"
#include "ListArray.h"
#include "ListArrayIterator.h"
#include "AnimationRenderListener.h"
#include "InputRenderListener.h"
#include "GameHeader.h"

#include<vector>

class GameManager;
class GUIManager;

class RenderManager
{
   private:
		ListArray<Ogre::AnimationState>* animation_states;
	
      Ogre::Root* root;
      Ogre::RenderWindow* window;
      Ogre::SceneManager* scene_manager;

      Ogre::Camera* camera;
      Ogre::Camera* camera2;
      Ogre::Viewport* viewport;
      Ogre::Viewport* viewport2;

      GameManager* game_manager;
	  GUIManager* gui_manager;
	  ListArray<RenderListener>* render_listeners;

      void init();
      size_t window_handle;
      Ogre::Real time_since_last_frame;

   public:
      RenderManager(GameManager* game_manager);
	  AnimationRenderListener* render_listener;
      virtual ~RenderManager();
	 // static RenderManager* getRenderManager();
	 
	 void playAudioByName(std::string name, int repeat);

      size_t getRenderWindowHandle();
      int getRenderWindowWidth();
      int getRenderWindowHeight();
	  void checkForInput(float time_step);
	  void leftJoystickAxisMoved(float north_south, float east_west);
	  void rightJoystickAxisMoved(float north_south, float east_west);
	  void triggerMoved(float amount);
	  void processKeyboardInput(std::string key);
	  void updateAudio(float time_step);
	  //void playAudio(std::string audio_name, int numRepeats);
	  
	  void mousePressed(uint32 x_click, uint32 y_click, std::string mouse_button);
	  void mouseMoved(uint32 x_click, uint32 y_click, float x_rel, float y_rel);

      Ogre::RenderWindow* getRenderWindow();
      Ogre::SceneManager* getSceneManager();

      void startRendering();
      void stopRendering();
	  void processAnimations(float time_step);
	  
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
};

#endif
