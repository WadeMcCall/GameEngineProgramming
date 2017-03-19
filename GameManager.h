#if !defined GAME_MANAGER
#define GAME_MANAGER

#include <string>
#include "LogManager.h"
#include "InputManager.h"

class RenderManager;

//supplies communication between managers
class GameManager
{
   private:
      RenderManager* render_manager;
	  LogManager* log_manager;
	  InputManager* input_manager;

      GameManager();
      void init();

   public:
      virtual ~GameManager();
      static GameManager* getGameManager();
	  void keyPressed(std::string key);
	  void keyReleased(std::string key);
	  void checkForInput(float time_step);
	  void logProblem(std::string msg, std::string filename, int line);
	  void logComment(std::string msg);
	  void leftJoystickAxisMoved(float north_south, float east_west);
	  void rightJoystickAxisMoved(float north_south, float east_west);
	  void triggerMoved(float amount);
      int getRenderWindowWidth();
      int getRenderWindowHeight();
      size_t getRenderWindowHandle();
	  std::string getLoadedLevelName();
};

#endif
