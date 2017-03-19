#if !defined ANIMATION_RENDER_LISTENER
#define ANIMATION_RENDER_LISTENER

#include "RenderListener.h"
class RenderManager;

class AnimationRenderListener : public RenderListener{ //Ogre::FrameListener{
	private:
		//RenderManager* render_manager;
		//bool render;
		
	public:
		AnimationRenderListener(RenderManager* render_manager);
		virtual ~AnimationRenderListener();
		
		//bool getRenderStatus();
		//RenderManager* getRenderManager();
		//void stopRendering();
		//
		bool frameStarted(const Ogre::FrameEvent& event);
		//
		//bool frameRenderingQueued(const Ogre::FrameEvent& event);
		//
		//bool frameEnded(const Ogre::FrameEvent& event);
};

#endif