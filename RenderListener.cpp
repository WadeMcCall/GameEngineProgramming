#include "RenderListener.h"
#include <iostream>
using namespace std;

RenderListener::RenderListener(RenderManager* rm){
	render_manager = rm;
	render = true;
}

RenderListener::~RenderListener(){
	render_manager = NULL;
}

void RenderListener::stopRendering(){
	render = false;
}

void RenderListener::startRendering(){
	render = true;
}

bool RenderListener::getRenderStatus(){
	return render;
}

RenderManager* RenderListener::getRenderManager(){
	return render_manager;
}