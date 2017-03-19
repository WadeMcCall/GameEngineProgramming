#if !defined INPUT_MANAGER
#define INPUT_MANAGER

#include <OIS.h>
#include "ListArray.h"
#include <iostream>
#include "LogManager.h"

class GameManager;

class InputManager : public OIS::KeyListener, public OIS::JoyStickListener{
	private:
		OIS::InputManager* input_manager_ois;
		
		OIS::Keyboard* keyboard_ois;
		OIS::Mouse* mouse_ois;
		OIS::JoyStick* joystick_ois;
		GameManager* game_manager;
		
		int window_height;
		int window_width;
		
		std::string keyMap(const OIS::KeyEvent& e);
		std::string joystickButtonMap(int button);
		std::string joystickAxisMap(int button);
		
		void init();
		void free();
		
	public: 
		InputManager(GameManager* game_manager);
		virtual ~InputManager();
		
		void checkForInput();
		
		bool keyPressed(const OIS::KeyEvent& e);
		bool keyReleased(const OIS::KeyEvent& e);
		
		bool buttonReleased(const OIS::JoyStickEvent& e, int button);
		bool buttonPressed(const OIS::JoyStickEvent& e, int button);
		bool sliderMoved(const OIS::JoyStickEvent& e, int index);
		bool povMoved(const OIS::JoyStickEvent& e, int index);
		bool vector3Moved(const OIS::JoyStickEvent& e, int index);
		bool axisMoved(const OIS::JoyStickEvent& e, int axis);		
};

#endif