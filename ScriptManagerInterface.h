#if !defined SCRIPT_MANAGER_INTERFACE
#define SCRIPT_MANAGER_INTERFACE

#include <string>

class GameManager;

class ScriptManagerInterface{
	protected:
		GameManager* game_manager;
		
	public:
		ScriptManagerInterface(GameManager* gm){game_manager = gm;};
		virtual ~ScriptManagerInterface(){game_manager = NULL;};
		
		virtual void input(std::string& input) = 0;
		virtual std::string output(int index) = 0;
		virtual void reset() = 0;
		virtual void buttonEventCallback(std::string audioName, int num, std::string event_script) = 0;
		
		virtual void executeScript(std::string& script_file_name, std::string& script_function_name, int num_outputs) = 0;
};
#endif