#include "GameManager.h"
#include "AudioResource.h"
#include "ListArray.h"

#include <iostream>

void GameManager::buttonPressed(std::string button){
	render_manager->buttonPressed(button);
}

void GameManager::jump(){
	render_manager->jump();
}

void GameManager::createRigidBodies(){
	render_manager->createRigidBodies();
}

void GameManager::createCollisionShape(std::string child_name_str, std::string collision_shape_name_str, float* params, float mass, float* translation, float* rotation){
	render_manager->createCollisionShape(child_name_str, collision_shape_name_str, params, mass, translation, rotation);
}

void GameManager::mouseMoved(uint32 x_click, uint32 y_click, float x_rel, float y_rel){
	render_manager->mouseMoved(x_click, y_click, x_rel, y_rel);
}

void GameManager::mousePressed(uint32 x_click, uint32 y_click, std::string mouse_button){
	render_manager->mousePressed(x_click, y_click, mouse_button);
}

void GameManager::addAudioResource(AudioResource* ar){
	audio_resources->add(ar);
}

void GameManager::playAudioByName(std::string name, int times){
   ListArrayIterator<AudioResource>* audio_resources_iter = audio_resources->iterator();
   while(audio_resources_iter->hasNext()){
	   AudioResource* ar = audio_resources_iter->next();
	   if(ar->getAudioResourceName() == name)
			playAudio(ar, times);
   }	
}

void GameManager::playAudio(AudioResource* audio_resource, uint32 num_repeats){
	audio_manager->playAudio(audio_resource, num_repeats);
}

void GameManager::updateAudio(float time_step){
	audio_manager->updateAudio(time_step);
}

AudioResourceInfo* GameManager::createAudioResourceInfo(){
	return audio_manager->createAudioResourceInfo();
}

void GameManager::loadSampleAudioResource(std::string audio_file_name, AudioResourceInfo* audio_info){
	audio_manager->loadSampleAudioResource(audio_file_name,audio_info);
}

void GameManager::loadStreamAudioResource(std::string audio_file_name, AudioResourceInfo* audio_info){
	audio_manager->loadStreamAudioResource(audio_file_name,audio_info);
}

void GameManager::unloadSampleAudioResource(AudioResourceInfo* audio_info){
	audio_manager->unloadSampleAudioResource(audio_info);
}

void GameManager::unloadStreamAudioResource(AudioResourceInfo* audio_info){
	audio_manager->unloadStreamAudioResource(audio_info);
}

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

void GameManager::createAnimation(std::string animation_node_str, std::string animation_name_str, float seconds, std::vector<float> key_frame_times, std::vector<float*> key_frame_translate, std::vector<float*> key_frame_rotate){
	render_manager->createAnimation(animation_node_str, animation_name_str, seconds, key_frame_times, key_frame_translate, key_frame_rotate);
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
	audio_manager = new AudioManager(this);
	logComment("AudioManager initialized");
}

GameManager::GameManager() : GameManagerInterface()
{
   audio_resources = new ListArray<AudioResource>();
   init();
   resource_manager->loadLevel("level_0");
   playAudioByName("theme", 1);
   logComment("level loaded");
   render_manager->startRendering();
}

GameManager::~GameManager()
{
	std::cout << "GameManager destructor called" << std::endl;
	delete audio_manager;
	audio_manager = NULL;
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
