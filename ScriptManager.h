#if !defined SCRIPT_MANAGER
#define SCRIPT_MANAGER

extern "C" //prevents name mangling
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <LuaBridge.h>

#include <string>
#include "ListArray.h"
#include "GameManager.h"
#include "ScriptManagerInterface.h"

class ScriptManager : public ScriptManagerInterface
{
	private:
		lua_State* L;
		
		ListArray<const char>* inputs;
		ListArray<const char>* outputs;
		
	public:
		ScriptManager(GameManager* game_manager);
		virtual ~ScriptManager();
		
		void input(std::string& input);
		std::string output(int index);
		void reset();
		void buttonEventCallback(std::string audioName, int num, std::string event_script);
		
		void executeScript(std::string& script_file_name, std::string& script_function_name, int num_outputs);
};
#endif