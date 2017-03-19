#if !defined INPUT_RENDER_LISTENER
#define INPUT_RENDER_LISTENER

#include "RenderListener.h"

class RenderManager;

class InputRenderListener : public RenderListener{
	private:
	
	public:
		InputRenderListener(RenderManager* render_manager);
		virtual ~InputRenderListener();
		
		virtual bool frameStarted(const Ogre::FrameEvent& event);
};
#endif