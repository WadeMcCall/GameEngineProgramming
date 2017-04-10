#include "GameHeader.h"
#include "InputManager.h"
#include "GameManager.h"

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

void InputManager::checkForInput(){
	if(keyboard_ois)keyboard_ois->capture();
	if(mouse_ois)mouse_ois->capture();
	if(joystick_ois){
		joystick_ois->capture();
		OIS::JoyStickState joystick_state = joystick_ois->getJoyStickState();
		OIS::JoyStickEvent e(joystick_ois, joystick_state);
		axisMoved(e,0);
	}
}

bool InputManager::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id){
	uint32 x_click = e.state.X.abs;
	uint32 y_click = e.state.Y.abs;
	game_manager->mousePressed(x_click, y_click, mouseMap(e));
	return true;
}

bool InputManager::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id){
	uint32 x_click = e.state.X.abs;
	uint32 y_click = e.state.Y.abs;
	return true;
}

bool InputManager::mouseMoved(const OIS::MouseEvent& e){
	e.state.width = window_width;
	e.state.height = window_height;
	uint32 x_click = e.state.X.abs;
	uint32 y_click = e.state.Y.abs;
	float x_rel = e.state.X.rel;
	float y_rel = e.state.Y.rel;
	
	game_manager->mouseMoved(x_click, y_click, x_rel, y_rel);
	return true;
}

bool InputManager::keyPressed(const OIS::KeyEvent& e){
	game_manager->keyPressed(keyMap(e));
	return true;
}

bool InputManager::keyReleased(const OIS::KeyEvent& e){
	game_manager->keyReleased(keyMap(e));
	return true;
}

InputManager::InputManager(GameManager* gm){
	game_manager = gm;
	input_manager_ois = NULL;
	keyboard_ois = NULL;
	mouse_ois = NULL;
	joystick_ois = NULL;
	
	init();
	
	window_width = game_manager->getRenderWindowWidth();
	window_height = game_manager->getRenderWindowHeight();
}

void InputManager::free(){
	if(input_manager_ois){
		input_manager_ois->destroyInputSystem(input_manager_ois);
	}
}

InputManager::~InputManager(){
	free();
	
	input_manager_ois = NULL;
	keyboard_ois = NULL;
	mouse_ois = NULL;
	joystick_ois = NULL;
}

void InputManager::init(){
	try{
		OIS::ParamList p1;
		std::ostringstream windowHndStr;
		size_t window_handle = game_manager->getRenderWindowHandle();
		
		size_t handle = window_handle;
		windowHndStr << handle;
		p1.insert(std::make_pair(std::string("WINDOW"),windowHndStr.str()));
		
		input_manager_ois = OIS::InputManager::createInputSystem(p1);
		if(input_manager_ois->getNumberOfDevices(OIS::OISKeyboard) > 0){
			keyboard_ois = static_cast<OIS::Keyboard*>(input_manager_ois->createInputObject(OIS::OISKeyboard,true));
			keyboard_ois->setEventCallback(this);
		}
		
		if(input_manager_ois->getNumberOfDevices(OIS::OISJoyStick)>0){
			joystick_ois = static_cast<OIS::JoyStick*>(input_manager_ois->createInputObject(OIS::OISJoyStick,true));
			joystick_ois->setEventCallback(this);
		}
		if(input_manager_ois->getNumberOfDevices(OIS::OISMouse)>0){
			mouse_ois = static_cast<OIS::Mouse*>(input_manager_ois->createInputObject(OIS::OISMouse,true));
			mouse_ois->setEventCallback(this);
		}
	}
	
	catch(std::exception& e){
		ASSERT_CRITICAL(false, e.what());
	}
	catch(...){
		ASSERT_CRITICAL(false, "Input Manager Initialization Error");
	}
}

std::string InputManager::mouseMap(const OIS::MouseEvent& id){
	if(id.state.buttonDown(OIS::MB_Left)){
		return "MB_left";
	}
	else if(id.state.buttonDown(OIS::MB_Right)){
		return "MB_right";
	}
	else return "MB_middle";
}

std::string InputManager::keyMap(const OIS::KeyEvent& e){
	std::string game_key = "INVALID_KEY";
	OIS::KeyCode key_code = e.key;
	
	if(key_code == OIS::KC_ESCAPE){
		game_key = "ESCAPE";
	}	
	else if(key_code == OIS::KC_0){
		game_key = "0";
	}
	else if(key_code == OIS::KC_1){
		game_key = "1";
	}
	else if(key_code == OIS::KC_2){
		game_key = "2";
	}
	else if(key_code == OIS::KC_RIGHT){
		game_key = "RIGHT";
	}
	else if(key_code == OIS::KC_LEFT){
		game_key = "LEFT";
	}
	else if(key_code == OIS::KC_UP){
		game_key = "UP";
	}
	else if(key_code == OIS::KC_DOWN){
		game_key = "DOWN";
	}
	else if(key_code == OIS::KC_W){
		game_key = "W";
	}
	else if(key_code == OIS::KC_A){
		game_key = "A";
	}
	else if(key_code == OIS::KC_S){
		game_key = "S";
	}
	else if(key_code == OIS::KC_D){
		game_key = "D";
	}
	
	return game_key;
}

bool InputManager::buttonPressed(const OIS::JoyStickEvent&e, int button){return true;}
bool InputManager::buttonReleased(const OIS::JoyStickEvent&e, int button){return true;}
bool InputManager::sliderMoved(const OIS::JoyStickEvent&e, int index){return true;}
bool InputManager::povMoved(const OIS::JoyStickEvent&e, int index){return true;}
bool InputManager::vector3Moved(const OIS::JoyStickEvent&e, int index){return true;}

bool InputManager::axisMoved(const OIS::JoyStickEvent&e, int axis){
	int DeadZone = 7000;
	
	float amount[5] = {e.state.mAxes[0].abs,e.state.mAxes[1].abs,
						e.state.mAxes[2].abs,e.state.mAxes[3].abs,
						e.state.mAxes[4].abs};
						
	//cout << amount [0] << " " << amount[1] << endl;
	
	float north_south = 0;
	float east_west = 0;
	if(fabs(amount[0]) > DeadZone ){
		north_south = amount[0]/32767.0;
	}
	if(fabs(amount[1]) > DeadZone ){
		east_west = amount[1]/32767.0;
	}
	
	game_manager->leftJoystickAxisMoved(north_south,east_west);
	north_south = 0.0;
	east_west = 0.0;
	
	if(fabs(amount[2]) > DeadZone){
		north_south = amount[2]/32767.0;
	}
	if(fabs(amount[3]) > DeadZone){
		east_west = amount[3]/32767.0;
	}
	game_manager->rightJoystickAxisMoved(north_south,east_west);
	north_south = 0.0;
	east_west = 0.0;
	
	if(fabs(amount[4]) > DeadZone){
		north_south = amount[4]/32767.0;
	}
	game_manager->triggerMoved(north_south);
	
	return true;
}

std::string InputManager::joystickAxisMap(int axis){
	if(axis == 0){
		return "L_NS";
	}
	else if(axis == 1){
		return "L_EW";
	}
	else if(axis == 2){
		return "R_NS";
	}
	else{
		return "R_EW";
	}
}

std::string InputManager::joystickButtonMap(int button){
	if(button == 0){
		return "A";
	}
	else if(button == 1){
		return "B";
	}
	else if(button == 2){
		return "X";
	}
	else if(button == 3){
		return "Y";
	}
	else if(button == 4){
		return "L";
	}
	else return "R";
}
