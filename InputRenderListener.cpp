#include "RenderListener.h"
#include "InputRenderListener.h"
#include "RenderManager.h"
using namespace std;

InputRenderListener::InputRenderListener(RenderManager* rm): RenderListener(rm){}

InputRenderListener::~InputRenderListener(){}

bool InputRenderListener::frameStarted(const Ogre::FrameEvent& event){
	float time_step = event.timeSinceLastFrame;
	
	getRenderManager()->updateAudio(time_step);
	getRenderManager()->checkForInput(time_step);
	getRenderManager()->stepPhysicsSimulation(time_step);
	return getRenderStatus();
}