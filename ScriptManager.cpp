#include "ScriptManager.h"
#include "RenderManager.h"

void ScriptManager::reset(){
	inputs->removeAll();
	outputs->removeAll();
}

void ScriptManager::buttonEventCallback(std::string audioName, int num, std::string event_script){
	luabridge::push(L, audioName.c_str());
	lua_setglobal(L, "parameter_str");
	luabridge::push(L, num);
	lua_setglobal(L, "num");
	
	int script = luaL_dofile(L, event_script.c_str());
	if(script != 0){
		ASSERT_LOG(script != 0, lua_tostring(L, -1))
		lua_pop(L,1);
	}
}

void ScriptManager::input(std::string& input_str){
	const char* parameter = input_str.c_str();
	inputs->add(parameter);
}

std::string ScriptManager::output(int index){
	const char* output = outputs->get(index);
	std::string output_str(output);
	return output_str;
}

ScriptManager::ScriptManager(GameManager* gm){
	game_manager = gm;
	L = luaL_newstate();
	luaL_openlibs(L);
	
	inputs = new ListArray<const char>();
	outputs = new ListArray<const char>();
	
	luabridge::getGlobalNamespace(L)
	.beginClass<GameManager>("GameManager")
		.addFunction("playAudioByName", &GameManager::playAudioByName)
		.endClass();
		
	luabridge::push(L, game_manager);
	lua_setglobal(L, "game_manager");
}

ScriptManager::~ScriptManager(){
	reset();
	delete inputs;
	inputs = NULL;
	delete outputs;
	
	lua_close(L);
	game_manager = NULL;
}

void ScriptManager::executeScript(std::string& script_file_name, std::string& script_function_name, int num_outputs){
	int num_inputs = inputs->size();
	
	luaL_dofile(L, script_file_name.c_str());
	
	lua_getglobal(L, script_function_name.c_str());
	
	for(int i = 1; i <= num_inputs; i++){
		const char* input = inputs->get(i);
		lua_pushstring(L,input);
	}
	
	lua_pcall(L, num_inputs, num_outputs, 0);
	
	for(int i = num_outputs - 1; i >= 0; i--){
		const char* temp = lua_tostring(L, -1);
		outputs->add(temp);
		lua_pop(L,1);
	}
}