#include "GameManager.h"
#include "RenderManager.h"

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
	render_manager = new RenderManager(this);  //calls render manager's init, sets up the frame listener
	logComment("Render Manager Initialized");
	input_manager = new InputManager(this);
	logComment("Input Manager Initialized");
}

GameManager::GameManager()
{
   init();
   render_manager->parseResourceXML("resources.xml");
   render_manager->parseSceneXML("monkey_scene.xml");
   render_manager->startRendering();
}

GameManager::~GameManager()
{
	std::cout << "GameManager destructor called" << std::endl;
	
	delete input_manager;
	input_manager = NULL;
	delete render_manager;
	render_manager = NULL;
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
