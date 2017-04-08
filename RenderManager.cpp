#include "RenderManager.h"
#include "GameManager.h"
#include "GameHeader.h"
#include "Utils.h"
#include "AnimationRenderListener.h"
#include "InputRenderListener.h"
#include "ListArray.h"
#include "ListArrayIterator.h"
#include <math.h>

#include <vector>
#include <iostream>
using namespace std;

void RenderManager::leftJoystickAxisMoved(float north_south, float east_west){	
	Ogre::SceneNode* Scene_node = scene_manager->getSceneNode("WeirdMan Transform");
	Ogre::Vector3 current_pos = Scene_node->_getDerivedPosition();
	cout << current_pos.x << " " << current_pos.y << " " << current_pos.z << endl;
	if(fabs(current_pos.x) <  5.5 && fabs(current_pos.z) < 5.5)
		current_pos = Ogre::Vector3(current_pos.x + .002*east_west, current_pos.y, current_pos.z +.002*north_south);
	else if(current_pos.x > 5.5)
		current_pos.x = 5.4;
	else if (current_pos.x < -5.5)
		current_pos.x = -5.4;
	else if(current_pos.z > 5.5)
		current_pos.z = 5.4;
	else if (current_pos.z < -5.5)
		current_pos.z = -5.4;
	Scene_node->_setDerivedPosition(current_pos);
}

void RenderManager::rightJoystickAxisMoved(float north_south, float east_west){
	Ogre::SceneNode* Scene_node = scene_manager->getSceneNode("Monkey Entity");
	Ogre::Quaternion current_quat = Scene_node->getOrientation();
	Ogre::Degree prev_degree;
	Ogre::Vector3 axis;
	
	current_quat.ToAngleAxis(prev_degree, axis);
	float curr_deg = prev_degree.valueDegrees() + .1*east_west;
	
	if(curr_deg < 0) curr_deg = curr_deg + 360.0;
	if(curr_deg > 360) curr_deg = curr_deg - 360.0;
	
	Ogre::Degree curr_degree(curr_deg);
	
	Ogre::Quaternion update(curr_degree, axis);
	Scene_node->setOrientation(update);	
}

void RenderManager::triggerMoved(float amount){
}

void RenderManager::processKeyboardInput(std::string key){
	if(key == "ESCAPE"){
		stopRendering();
	}
	else if(key == "A"){
		
	}
	else{}
}

void RenderManager::checkForInput(float time_step){
	game_manager->checkForInput(time_step);
}

void RenderManager::init()
{
	root = NULL;
	window = NULL;
	scene_manager = NULL;

	root = OGRE_NEW Ogre::Root("","");  //resource/config files go here
	root->loadPlugin("RenderSystem_GL");  //prepares external dlls for later use

      Ogre::RenderSystem* render_system = root->getRenderSystemByName("OpenGL Rendering Subsystem"); //just returns a pointer to an uninialized render system
      if (!render_system)
      {
         ASSERT_CRITICAL(false, "no render system initialized");
      }

      root->setRenderSystem(render_system);
      //manually set configuration options
      render_system->setConfigOption("Full Screen", "No");
      render_system->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");

      //initialize render system
      //automatically create the window and give it a title
      window = root->initialise(true, "Game Engine Programming");  

      scene_manager = root->createSceneManager(Ogre::ST_GENERIC, "Default Scene Manager");
      window->getCustomAttribute("WINDOW", &window_handle);
	  
	  viewport = window->addViewport(NULL, 1,0,0,1,1);
	  viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
}

void RenderManager::attachEntity(std::string entity_name_str, std::string entity_mesh_str, std::string entity_material_str, std::string entity_scene_node_name_str){
	Ogre::Entity* entity = scene_manager->createEntity(entity_name_str, entity_mesh_str);
	entity->setMaterialName(entity_material_str);
	Ogre::SceneNode* entity_scene_node = scene_manager->getSceneNode(entity_scene_node_name_str);
	entity_scene_node->attachObject(entity);
}

void RenderManager::createSceneNode(std::string child_name_str, std::string parent_name_str){
	Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();
	Ogre::SceneNode* child_scene_node = scene_manager->createSceneNode(child_name_str);
	if(parent_name_str == "root"){
		root_scene_node->addChild(child_scene_node);
	}
	else{
		Ogre::SceneNode* parent_scene_node = scene_manager->getSceneNode(parent_name_str);
		parent_scene_node->addChild(child_scene_node);
	}
}

void RenderManager::processScale(float* scale, std::string scene_node_name_str){
	Ogre::SceneNode* scale_scene_node = scene_manager->getSceneNode(scene_node_name_str);
	scale_scene_node->scale(scale[0],scale[1],scale[2]);
}

void RenderManager::processRotation(float* rotation, std::string scene_node_name_str){
	Ogre::SceneNode* rotation_scene_node = scene_manager->getSceneNode(scene_node_name_str);
	Ogre::Degree angle(rotation[0]);
	Ogre::Vector3 axis(rotation[1],rotation[2],rotation[4]);
	Ogre::Quaternion q(angle, axis);
	rotation_scene_node->rotate(q);
}

void RenderManager::processTranslation(float* translation, std::string scene_node_name_str){
	Ogre::SceneNode* translation_scene_node = scene_manager->getSceneNode(scene_node_name_str);
	translation_scene_node->translate(translation[0],translation[1],translation[2]);
}

void RenderManager::createLight(std::string light_name, float* light_color, float* light_direction){
	scene_manager->setAmbientLight(Ogre::ColourValue(.05,.05,.05));
	Ogre::Light* light = scene_manager->createLight(light_name);
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDiffuseColour(light_color[0],light_color[1],light_color[2]);
	light->setDirection(Ogre::Vector3(light_direction[0],light_direction[1],light_direction[2]));
}

void RenderManager::createCamera(std::string camera_name, float* camera_position, float* camera_lookat, float* clip){
	camera = scene_manager->createCamera(camera_name);
	viewport->setCamera(camera);
	
	float actual_width = Ogre::Real(viewport->getActualWidth());
	float actual_height = Ogre::Real(viewport->getActualHeight());
	float aspect_ratio = actual_width/actual_height;
	camera->setAspectRatio(aspect_ratio);
	camera->setPosition(Ogre::Vector3(camera_position[0],camera_position[1],camera_position[2]));
	camera->lookAt(Ogre::Vector3(camera_lookat[0],camera_lookat[1],camera_lookat[2]));
	camera->setNearClipDistance(clip[0]);
	camera->setFarClipDistance(clip[1]);
}

void RenderManager::unloadLevel(std::string level_name){
	scene_manager->clearScene();
	viewport->setCamera(NULL);
	scene_manager->destroyAllCameras();
	
	Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();
	rgm.destroyResourceGroup(level_name);
}

void RenderManager::loadLevel(std::string level_name){
	Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();
	rgm.initialiseResourceGroup(level_name);
	rgm.loadResourceGroup(level_name, true, true);
}

void RenderManager::addPathResource(std::string path, std::string level_name){
	game_manager->logComment("adding path resource from RenderManager");
	Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();
	rgm.addResourceLocation(path, "FileSystem", level_name);
}

void RenderManager::addMeshResource(std::string mesh_file_name, std::string level_name){
	Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();
	rgm.declareResource(mesh_file_name, "Mesh", level_name);
}

void RenderManager::createAnimation(std::string animation_node_str, std::string animation_name_str, float seconds, vector<float> key_frame_times, vector<float*> key_frame_translate, vector<float*> key_frame_rotate){
	Ogre::SceneNode* animation_node = scene_manager->getSceneNode(animation_node_str);
	Ogre::Animation* animation = scene_manager->createAnimation(animation_name_str, seconds);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(1, animation_node);
	Ogre::TransformKeyFrame* key_frame;
	vector<float*>::iterator key_frame_translate_iter = key_frame_translate.begin();
	vector<float*>::iterator key_frame_rotate_iter = key_frame_rotate.begin();
	for(vector<float>::iterator key_frame_times_iter = key_frame_times.begin(); key_frame_times_iter != key_frame_times.end();key_frame_times_iter++){
		float time = *key_frame_times_iter;
		cout << time << endl;
		key_frame = track->createNodeKeyFrame(time);
		float* translate_values = *key_frame_translate_iter;
		cout << translate_values[0] << " " << translate_values[1] << " " << translate_values[2] << " " << endl;
		key_frame->setTranslate(Ogre::Vector3(translate_values[0],translate_values[1],translate_values[2]));
		translate_values = *key_frame_rotate_iter;
		Ogre::Vector3 rotate_axis(translate_values[1],translate_values[2],translate_values[3]);
		Ogre::Quaternion q1(Ogre::Degree(translate_values[0]), rotate_axis);
		key_frame->setRotation(q1);
		key_frame_rotate_iter++;
		key_frame_translate_iter++;
	}
	Ogre::AnimationState* animation_state = scene_manager->createAnimationState(animation_name_str);
	animation_state->setEnabled(true); 
	animation_state->setLoop(true);	
	animation_states->add(animation_state);	
	game_manager->logComment("built Animations");
}

RenderManager::RenderManager(GameManager* gm)
{
   game_manager = gm;
   init();
   
   animation_states = new ListArray<Ogre::AnimationState>();
   render_listeners = new ListArray<RenderListener>();
   RenderListener* render_listener = new AnimationRenderListener(this);
   render_listeners->add(render_listener);
   render_listener = new InputRenderListener(this);
   render_listeners->add(render_listener);
   
   ListArrayIterator<RenderListener>* render_listeners_iter = render_listeners->iterator();
   while(render_listeners_iter->hasNext()){
	   RenderListener* render_listener = render_listeners_iter->next();
	   root->addFrameListener(render_listener);
   }
   delete render_listeners_iter;
}

void RenderManager::processAnimations(float time_step){
	ListArrayIterator<Ogre::AnimationState>* anim_iter = animation_states->iterator();
	while(anim_iter->hasNext()){
		Ogre::AnimationState* animation_state = anim_iter->next();
		animation_state->addTime(time_step);
	}
	delete anim_iter;
}

void RenderManager::buildAnimation(Ogre::SceneNode* animation_node, TiXmlElement* animation_element){
	TiXmlElement* name_element = animation_element->FirstChildElement("name");
	std:string animation_name_str = name_element->GetText();
	
	TiXmlElement* time_element = animation_element->FirstChildElement("seconds");
	std::string animation_time_str = time_element->GetText();
	float seconds = atof(animation_time_str.c_str());
	
	Ogre::Animation* animation = scene_manager->createAnimation(animation_name_str, seconds);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(1, animation_node);
	
	Ogre::TransformKeyFrame* key_frame;
	
	TiXmlElement* keyframes_element = animation_element->FirstChildElement("keyframes");
	TiXmlElement* keyframe_element = keyframes_element->FirstChildElement("keyframe");
	while(keyframe_element != NULL){
		
		TiXmlElement* keyframe_time_element = keyframe_element->FirstChildElement("time");
		TiXmlElement* translate_element = keyframe_element->FirstChildElement("translation");
		TiXmlElement* rotate_element = keyframe_element->FirstChildElement("rotation");
		
		std::string time_str = keyframe_time_element->GetText();
		float time = atof(time_str.c_str());
		
		float* translate_values = new float[3];
		std::string translate_str = translate_element->GetText();
		Utils::parseFloats(translate_str, translate_values);
		
		
		key_frame = track->createNodeKeyFrame(time);
		key_frame->setTranslate(Ogre::Vector3(translate_values[0],translate_values[1],translate_values[2]));
		
		std::string rotate_str = rotate_element->GetText();
		Utils::parseFloats(rotate_str, translate_values);
		
		Ogre::Vector3 rotate_axis(translate_values[1],translate_values[2],translate_values[3]);
		Ogre::Quaternion q1(Ogre::Degree(translate_values[0]), rotate_axis);
		key_frame->setRotation(q1);
		
		keyframe_element = keyframe_element->NextSiblingElement("keyframe");
	}
	
	Ogre::AnimationState* animation_state = scene_manager->createAnimationState(animation_name_str);
	animation_state->setEnabled(true); 
	animation_state->setLoop(true);
	
	animation_states->add(animation_state);
	
	game_manager->logComment("built Animations");
}

RenderManager::~RenderManager()
{
	ListArrayIterator<RenderListener>* render_listeners_iter = render_listeners->iterator();
	while(render_listeners_iter->hasNext()){
		RenderListener* render_listener = render_listeners_iter->next();
		render_listener->stopRendering();
	}
	delete render_listeners_iter;
	
	delete animation_states;
	game_manager = NULL;
	
	scene_manager->clearScene();
	scene_manager->destroyAllCameras();
	
	window->removeAllViewports();
	
	window->destroy();
	window = NULL;
	
	delete root;
	root = NULL;
}

size_t RenderManager::getRenderWindowHandle()
{
   return window_handle;
}

int RenderManager::getRenderWindowWidth()
{
   return viewport->getActualWidth();
}

int RenderManager::getRenderWindowHeight()
{
   return viewport->getActualHeight();
}

void RenderManager::startRendering()
{
	ListArrayIterator <RenderListener>* render_listeners_iter = render_listeners->iterator();
	while(render_listeners_iter->hasNext()){
		RenderListener* render_listener = render_listeners_iter->next();
		render_listener->startRendering();
		game_manager->logComment("started rendering");
	}
	delete render_listeners_iter;
   root->startRendering();
}

void RenderManager::stopRendering(){
	ListArrayIterator<RenderListener>* render_listeners_iter = render_listeners->iterator();
	while(render_listeners_iter->hasNext()){
		RenderListener* render_listener = render_listeners_iter->next();
		render_listener->stopRendering();
		game_manager->logComment("Stopped Rendering");
	}
	delete render_listeners_iter;
}

Ogre::RenderWindow* RenderManager::getRenderWindow()
{
   return window;
}

Ogre::SceneManager* RenderManager::getSceneManager()
{
   return scene_manager;
}

//void RenderManager::parseResourceXML(const char* file_name){
//	std::cout << "here" << endl;
//	Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();
//	
//	TiXmlDocument doc(file_name);
//	if(!doc.LoadFile()) return;
//	
//	TiXmlElement* levels_element = doc.RootElement();
//	TiXmlElement* level_element = (TiXmlElement*) levels_element->FirstChild("level");
//	
//	while(level_element != NULL){
//		TiXmlElement* name_element = (TiXmlElement*) level_element->FirstChild("name");
//		std::string name_str = name_element->GetText();
//		
//		TiXmlElement* paths_element = (TiXmlElement*) level_element->FirstChild("paths");
//		TiXmlElement* path_element = (TiXmlElement*) paths_element->FirstChild("path");
//		
//		while(path_element != NULL){
//			std::string path_str = path_element->GetText();
//			rgm.addResourceLocation(path_str, "FileSystem", name_str);
//			path_element = (TiXmlElement*) path_element->NextSibling();
//		}
//		
//		TiXmlElement* meshes_element = (TiXmlElement*) level_element->FirstChild("meshes");
//		TiXmlElement* mesh_element = (TiXmlElement*) meshes_element->FirstChild("meshes");
//		
//		while(mesh_element != NULL){
//			std::string mesh_str = mesh_element->GetText();
//			rgm.declareResource(mesh_str, "Mesh", name_str);
//			mesh_element = (TiXmlElement*) mesh_element->NextSibling();
//		}
//		
//		level_element = (TiXmlElement*) levels_element->NextSibling();
//		
//		rgm.initialiseResourceGroup(name_str);
//		rgm.loadResourceGroup(name_str, true,true);
//	}
//}

void RenderManager::parseSceneXML(const char* file_name){	
	TiXmlDocument doc(file_name);
	if(!doc.LoadFile()) return;
	
	TiXmlElement* scene_element = doc.RootElement();
	TiXmlElement* level_element = scene_element->FirstChildElement("level");
	
	TiXmlElement* graph_element = scene_element->FirstChildElement("graph");
	TiXmlElement* children_element = graph_element->FirstChildElement("children");
	
	Ogre::SceneNode* scene_root_node = scene_manager->getRootSceneNode();
	//TiXmlElement* camera_element = scene_element->FirstChildElement("camera");
	//TiXmlElement* camera_name_element = camera_element->FirstChildElement("name");
	//std::string camera_name_str = camera_name_element->GetText();
	
	
	//camera = scene_manager->createCamera(camera_name_str);
	//viewport->setCamera(camera);
	
	//	float actual_width = Ogre::Real(viewport->getActualWidth());
	//	float actual_height = Ogre::Real(viewport->getActualHeight());
	//	float aspect_ratio = actual_width/actual_height;
	//	camera->setAspectRatio(aspect_ratio);
	//
	//TiXmlElement* camera_position_element = camera_element->FirstChildElement("position");
	//std::string camera_position_str = camera_position_element->GetText();
	//float* camera_values = new float[3];
	//Utils::parseFloats(camera_position_str, camera_values);
	//
	//camera->setPosition(Ogre::Vector3(camera_values[0],camera_values[1],camera_values[2]));
	//
	//TiXmlElement* camera_lookat_element = camera_element->FirstChildElement("look-at");
	//std::string camera_lookat_str = camera_lookat_element->GetText();
	//Utils::parseFloats(camera_lookat_str, camera_values);
	//camera->lookAt(Ogre::Vector3(camera_values[0],camera_values[1],camera_values[2]));
	//
	//TiXmlElement* camera_clip_element = camera_element->FirstChildElement("clip");
	//std::string camera_clip_str = camera_clip_element->GetText();
	//Utils::parseFloats(camera_clip_str, camera_values);
	//camera->setNearClipDistance(camera_values[0]);
	//camera->setFarClipDistance(camera_values[1]);
	
	//TiXmlElement* light_element = scene_element->FirstChildElement("light");
	//TiXmlElement* light_name_element = light_element->FirstChildElement("name");
	//std::string light_name_str = light_name_element->GetText();
	//
	//scene_manager->setAmbientLight(Ogre::ColourValue(.05,.05,.05));
	//Ogre::Light* light = scene_manager->createLight(light_name_str);
	//light->setType(Ogre::Light::LT_DIRECTIONAL);
	//
	//TiXmlElement* light_color_element = light_element->FirstChildElement("color");
	//std::string light_color_str = light_color_element->GetText();
	//float* light_values = new float[3];
	//Utils::parseFloats(light_color_str, light_values);
	//light->setDiffuseColour(light_values[0],light_values[1],light_values[2]);
	//
	//TiXmlElement* light_direction_element = light_element->FirstChildElement("direction");
	//std::string light_direction_str = light_direction_element->GetText();
	//Utils::parseFloats(light_direction_str,light_values);
	//light->setDirection(Ogre::Vector3(light_values[0],light_values[1],light_values[2]));
	
	if(children_element!=NULL){
		processChild(children_element, scene_root_node);
	}
	
	//delete[] camera_values;
	//delete[] light_values;
}

void RenderManager::processChild(TiXmlElement* children_element, Ogre::SceneNode* parent){
	TiXmlElement* child_element = (TiXmlElement*) children_element->FirstChild("child");
	
	while(child_element != NULL){
		TiXmlElement* name_element = (TiXmlElement*) child_element->FirstChild("name");
		std::string name_str = name_element->GetText();
		std::cout << name_str.c_str() << std::endl;
		Ogre::SceneNode* scene_node = scene_manager->createSceneNode(name_str);
		parent->addChild(scene_node);
		
		TiXmlElement* entity_element = (TiXmlElement*) child_element->FirstChild("entity");
		TiXmlElement* animation_element = (TiXmlElement*) child_element->FirstChild("animation");
		
		if(entity_element != NULL){
			//std::cout<< "you did it!" << std::endl;
			TiXmlElement* entity_name_element = (TiXmlElement*) entity_element->FirstChild("name");
			std::string entity_name_str = entity_name_element->GetText();
			TiXmlElement* entity_mesh_element = (TiXmlElement*) entity_element->FirstChild("mesh");
			std::string entity_mesh_str = entity_mesh_element->GetText();
			TiXmlElement* entity_material_element = (TiXmlElement*) entity_element->FirstChild("material");
			std::string entity_material_str = entity_material_element->GetText();
			
			Ogre::Entity* entity = scene_manager->createEntity(entity_name_str, entity_mesh_str);
			entity->setMaterialName(entity_material_str);
			scene_node->attachObject(entity);
		} 
		if(animation_element != NULL){
			//std::cout << "animation time!" << std::endl;
			buildAnimation(scene_node, animation_element);
		}
		TiXmlElement* translate_element = (TiXmlElement*) child_element->FirstChild("translation");
		std::string translate_str = translate_element->GetText();
		processTransformations(1, translate_str, scene_node);
		TiXmlElement* rotation_element = (TiXmlElement*) child_element->FirstChild("rotation");
		std::string rotate_str = rotation_element->GetText();
		processTransformations(2, rotate_str, scene_node);
		TiXmlElement* scale_element = (TiXmlElement*) child_element->FirstChild("scale");
		std::string scale_str = scale_element->GetText();
		processTransformations(3, scale_str, scene_node);
		TiXmlElement* grand_children_element = (TiXmlElement*) child_element->FirstChild("children");
		if(grand_children_element != NULL){
			processChild(grand_children_element, scene_node);
		}
		
		child_element = (TiXmlElement*) child_element->NextSibling();
	}
}

void RenderManager::processTransformations(int transform_type, std::string& transform_str, Ogre::SceneNode* scene_node){
	float* transform_values = new float[4];
	Utils::parseFloats(transform_str, transform_values);
	
	if(transform_type == 1){
		scene_node->translate(transform_values[0],transform_values[1],transform_values[2], Ogre::Node::TS_WORLD);
	}
	else if(transform_type == 2){
		Ogre::Degree angle(transform_values[0]);
		Ogre::Vector3 axis(transform_values[1],transform_values[2],transform_values[3]);
		Ogre::Quaternion q(angle,axis);
		scene_node->rotate(q,Ogre::Node::TS_WORLD);
	}
	else
		scene_node->scale(transform_values[0],transform_values[1],transform_values[2]);
	delete[] transform_values;
}