#include "GUIManager.h"
#include "RenderManager.h"
#include <iostream>

void GUIManager::buttonEvent(const CEGUI::EventArgs& e){
	render_manager->playAudioByName("shine", 2);
}

void GUIManager::keyPressed(std::string game_key){
	gui_context->injectChar((char) game_key[0]);
}

void GUIManager::loadLevel(std::string level_name){
    CEGUI::ImageManager::setImagesetDefaultResourceGroup(level_name);
    CEGUI::Scheme::setDefaultResourceGroup(level_name);
    CEGUI::Font::setDefaultResourceGroup(level_name);
    CEGUI::WidgetLookManager::setDefaultResourceGroup(level_name);
    CEGUI::WindowManager::setDefaultResourceGroup(level_name);
	CEGUI::ScriptModule::setDefaultResourceGroup(level_name);
	createGUIContext();
}

GUIManager::GUIManager(RenderManager* rm){
	cegui_ogre_renderer = getRenderer();
	render_manager = rm;
}

GUIManager::~GUIManager(){
	cegui_ogre_renderer = NULL;
}

void GUIManager::mousePressed(uint32 x_click, uint32 y_click, std::string mouse_button){
	CEGUI::MouseButton mouse_enum = CEGUI::NoButton;
	if(mouse_button == "MB_left"){
		mouse_enum = CEGUI::LeftButton;
	}
	else if(mouse_button == "MB_right"){
		mouse_enum = CEGUI::RightButton;
	}
	
	gui_context->injectMouseButtonDown(mouse_enum);
	gui_context->injectMouseButtonUp(mouse_enum);
}

void GUIManager::mouseMoved(uint32 x_click, uint32 y_click, float x_rel, float y_rel){
	gui_context->injectMouseMove(x_rel, y_rel);
}

CEGUI::OgreRenderer* GUIManager::getRenderer(){
	static CEGUI::OgreRenderer& cegui_ogre_renderer = CEGUI::OgreRenderer::bootstrapSystem();
	return &cegui_ogre_renderer;
}

void GUIManager::createGUIContext(){
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::FontManager::getSingleton().createFromFile("GreatVibes-16.font");
	CEGUI::System& system = CEGUI::System::getSingleton();
	gui_context = &system.createGUIContext(cegui_ogre_renderer->getDefaultRenderTarget());
	
	gui_context->setDefaultFont("GreatVibes-16");
	gui_context->getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	gui_context->setDefaultTooltipType("TaharezLook/Tooltip");
	
	CEGUI::WindowManager* wmgr = &CEGUI::WindowManager::getSingleton();
	root_window = wmgr->loadLayoutFromFile("myDemo.layout");
	gui_context->setRootWindow(root_window);
	
	CEGUI::PushButton* push_button = static_cast<CEGUI::PushButton*>(root_window->getChild("FrameWindow/Button"));
	push_button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::buttonEvent, this));
}

void GUIManager::destroyGUIContext(){
	CEGUI::System& system = CEGUI::System::getSingleton();
	if(gui_context != NULL){
		system.destroyGUIContext(*gui_context);
		gui_context=NULL;
	}
	CEGUI::SchemeManager::getSingleton().destroyAll();
	CEGUI::FontManager::getSingleton().destroyAll();
}