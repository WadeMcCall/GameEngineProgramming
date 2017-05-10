#if !defined RENDER_MANAGER_INTERFACE
#define RENDER_MANAGER_INTERFACE

#include "GameHeader.h"

#include<vector>

class GameManager;
struct SceneNodeManual;
struct SceneNodeMotion;

class RenderManagerInterface
{
   protected:
		GameManager* game_manager;

   public: 
      RenderManagerInterface(GameManager* gm){game_manager = gm;};
      virtual ~RenderManagerInterface(){game_manager = NULL;};
	  
	  virtual void playAudioByName(std::string name, int repeat) = 0;
	  virtual void buttonEvent(std::string audioName, int numRepeats) = 0;
	 
	  virtual SceneNodeManual* createManualObject() = 0;
	  virtual void drawLine(float* from, float* to, float* color, SceneNodeManual* snm) = 0;
	  virtual void destroySceneNodeMotion(SceneNodeMotion* snm) = 0;
	  virtual void setPosition(SceneNodeMotion* scene_node_motion, double x, double y, double z) = 0;
	  virtual void setOrientation(SceneNodeMotion* scene_node_motion, double w, double x, double y, double z) = 0;
	  virtual SceneNodeMotion* createSceneNodeMotion(std::string& scene_node_id) = 0;
	  virtual void clearManualObject(SceneNodeManual* snm) = 0;
	  virtual float* getPosition(SceneNodeMotion* scene_node_motion) = 0;
	  virtual float* getOrientation(SceneNodeMotion* scene_node_motion) = 0;
	  virtual void stepPhysicsSimulation(float elapsed_time) = 0;
	  virtual void createCollisionShape(std::string& child_name, std::string& shape_str, float* params, float mass, float* translation, float* rotation) = 0;
	  virtual void createRigidBodies() = 0;
	  
      virtual size_t getRenderWindowHandle() = 0;
      virtual int getRenderWindowWidth() = 0;
      virtual int getRenderWindowHeight() = 0;
	  virtual void checkForInput(float time_step) = 0;
	  virtual void leftJoystickAxisMoved(float north_south, float east_west) = 0;
	  virtual void rightJoystickAxisMoved(float north_south, float east_west) = 0;
	  virtual void triggerMoved(float amount) = 0;
	  virtual void processKeyboardInput(std::string key) = 0;
	  virtual void updateAudio(float time_step) = 0;
	  
	  virtual void mousePressed(uint32 x_click, uint32 y_click, std::string mouse_button) = 0;
	  virtual void mouseMoved(uint32 x_click, uint32 y_click, float x_rel, float y_rel) = 0;
	  
      virtual void startRendering() = 0;
      virtual void stopRendering() = 0;
	  virtual void processAnimations(float time_step) = 0;
	  
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
	  virtual void jump() = 0;
	  virtual void buttonPressed(std::string button) = 0;
	  virtual void buttonEvent1() = 0;
};
#endif