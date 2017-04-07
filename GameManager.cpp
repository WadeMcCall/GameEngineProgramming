#include "GameManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Ogre.h"

#include <iostream>

void GameManager::keyPressed(std::string key){
	render_manager->processKeyboardInput(key);
}

void GameManager::keyReleased(std::string key){}

void GameManager::checkForInput(float time_step){
	input_manager->checkForInput();
}

void GameManager::leftJoystickAxisMoved(float north_south, float east_west){
	render_manager->leftJoystickAxisMoved(north_south, east_west);
}

void GameManager::rightJoystickAxisMoved(float north_south, float east_west){
	render_manager->rightJoystickAxisMoved(north_south, east_west);
}

void GameManager::triggerMoved(float amount){
	render_manager->triggerMoved(amount);
}

void GameManager::logProblem(std::string msg, std::string filename, int line){
	log_manager->logProblem(msg, filename, line);
}

void GameManager::logComment(std::string msg){
	log_manager->logComment(msg);
}

void GameManager::attachEntity(std::string entity_name_str, std::string entity_mesh_str, std::string entity_material_str, std::string entity_scene_node_name_str){
	render_manager->attachEntity(entity_name_str, entity_mesh_str, entity_material_str, entity_scene_node_name_str);
}

//Ogre::SceneNode* GameManager::getSceneNode(std::string scene_node_name){
//	render_manager->getSceneNode(scene_node_name);
//}

//void GameManager::createAnimation(std::string animation_name_str){
//	render_manager->createAnimation(animation_name_str);
//}

Ogre::SceneManager* GameManager::getSceneManager(){
	return render_manager->getSceneManager();
}

void GameManager::addAnimationState(Ogre::AnimationState* animation_state){
	render_manager->addAnimationState(animation_state);
}

void GameManager::createSceneNode(std::string child_name_str, std::string parent_name_str){
	render_manager->createSceneNode(child_name_str, parent_name_str);
}

void GameManager::processScale(float* scale, std::string scene_node_name_str){
	render_manager->processScale(scale, scene_node_name_str);
}

void GameManager::processRotation(float* rotation, std::string scene_node_name_str){
	render_manager->processRotation(rotation, scene_node_name_str);
}

void GameManager::processTranslation(float* translation, std::string scene_node_name_str){
	render_manager->processTranslation(translation, scene_node_name_str);
}

void GameManager::createLight(std::string light_name, float* light_color, float* light_direction){
	render_manager->createLight(light_name, light_color, light_direction);
}

void GameManager::createCamera(std::string camera_name, float* camera_position, float* camera_lookat, float* clip){
	render_manager->createCamera(camera_name, camera_position, camera_lookat, clip);
}

void GameManager::unloadLevel(std::string level_name){
	render_manager->unloadLevel(level_name);
}

void GameManager::loadLevel(std::string level_name){
	render_manager->loadLevel(level_name);
}

void GameManager::addPathResource(std::string path, std::string level_name){
	std::cout << std::endl << "im right here!";
	logComment("addingpathResource from game manager");
	render_manager->addPathResource(path, level_name);
}

void GameManager::addMeshResource(std::string mesh_file_name, std::string level_name){
	render_manager->addMeshResource(mesh_file_name, level_name);
}

//the problem is that in C++, it is not known when this initialization code will be called
//so we will use a function static variable that is initialized the first time the method is called
//destructor automatically called?
GameManager* GameManager::getGameManager()
{
   static GameManager game_manager;  //initialized when method is called the first time
   return &game_manager;  //won't go out of scope as game_manager is static
}

void GameManager::init()
{
	log_manager = new LogManager("game_log.txt");
	logComment("Log Manager Initialized");
	resource_manager = new ResourceManager("resources.xml", "monkey_scene.xml", this);
	render_manager = new RenderManager(this);  //calls render manager's init, sets up the frame listener
	logComment("Render Manager Initialized");
	input_manager = new InputManager(this);
	logComment("Input Manager Initialized");
}

GameManager::GameManager()
{
   init();
   //render_manager->parseResourceXML("resources.xml");
   //render_manager->parseSceneXML("monkey_scene.xml");
   resource_manager->loadLevel("level_0");
   logComment("level loaded");
   render_manager->startRendering();
}

GameManager::~GameManager()
{
	std::cout << "GameManager destructor called" << std::endl;
	
	delete input_manager;
	input_manager = NULL;
	delete render_manager;
	render_manager = NULL;
	delete resource_manager;
	resource_manager = NULL;
	delete log_manager;
	log_manager = NULL;
}

size_t GameManager::getRenderWindowHandle()
{
   return render_manager->getRenderWindowHandle();
}

int GameManager::getRenderWindowWidth()
{
   return render_manager->getRenderWindowWidth();
}

int GameManager::getRenderWindowHeight()
{
   return render_manager->getRenderWindowHeight();
}
