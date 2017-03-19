#include "RenderListener.h"
#include "InputRenderListener.h"
#include "RenderManager.h"
#include <iostream>
using namespace std;

InputRenderListener::InputRenderListener(RenderManager* rm): RenderListener(rm){}

InputRenderListener::~InputRenderListener(){}

bool InputRenderListener::frameStarted(const Ogre::FrameEvent& event){
	float time_step = event.timeSinceLastFrame;
	
	getRenderManager()->checkForInput(time_step);
	return getRenderStatus();
}