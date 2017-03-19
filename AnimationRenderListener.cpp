#include "AnimationRenderListener.h"
#include "RenderManager.h"

#include <iostream>
using namespace std;

AnimationRenderListener::AnimationRenderListener(RenderManager* rm):RenderListener(rm){
	//render_manager = rm;
	//render = true;
}

AnimationRenderListener::~AnimationRenderListener(){
	//render_manager = NULL;
}

//bool AnimationRenderListener::getRenderStatus(){
//	return render;
//}
//
//RenderManager* AnimationRenderListener::getRenderManager(){
//	return render_manager;
//}
//
//void AnimationRenderListener::stopRendering(){
//	render = false;
//}

bool AnimationRenderListener::frameStarted(const Ogre::FrameEvent& event){
	float time_step = event.timeSinceLastFrame;
	getRenderManager()->processAnimations(time_step);
	return getRenderStatus();
}

//bool AnimationRenderListener::frameEnded(const Ogre::FrameEvent& event){}
//bool AnimationRenderListener::frameRenderingQueued(const Ogre::FrameEvent& event){}