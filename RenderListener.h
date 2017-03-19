#if !defined RENDER_LISTENER
#define RENDER_LISTENER

#include "Ogre.h"
class RenderManager;

class RenderListener: public Ogre::FrameListener{
	private:
		RenderManager* render_manager;
		bool render;
		
	public:
		RenderListener(RenderManager* render_manager);
		virtual ~RenderListener();
		
		virtual bool frameStarted(const Ogre::FrameEvent& event){return getRenderStatus();}
		
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& event){return getRenderStatus();}
		
		virtual bool frameEnded(const Ogre::FrameEvent& event){return getRenderStatus();}
		
		void stopRendering();
		void startRendering();
		bool getRenderStatus();
		
	protected:
		RenderManager* getRenderManager();
};
#endif