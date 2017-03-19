AutomatedMakefile = am
CC = g++

INC_DIRS=-I./ -I$(OGRE_PATH)/OgreMain/include -I$(BOOST_PATH) -I$(TINYXML_DIR)/include -I$(OIS_PATH)/include
LIB_DIRS=-L./ -L$(OGRE_PATH)/build/lib -L$(BOOST_PATH)/stage/lib -L$(TINYXML_DIR)/lib -L$(OIS_PATH)/lib
LIBS=-lboost_system-mgw51-mt-1_63 -lOgreMain -ltinyxml -lOIS

COMPILE = $(CC) $(INC_DIRS) -c
LINK = $(CC) $(LIB_DIRS) -o

FILES = LogManager.o InputManager.o RenderManager.o GameManager.o RenderListener.o GameDriver.o Utils.o AnimationRenderListener.o InputRenderListener.o 

all: Ogre

Ogre: 	$(FILES)
		$(LINK) Game.exe $(FILES) $(LIBS)
		
LogManager.o:		LogManager.h LogManager.cpp
					$(COMPILE) LogManager.cpp
		
RenderManager.o:	RenderManager.h RenderManager.cpp
					$(COMPILE) RenderManager.cpp
							
InputRenderListener.o: InputRenderListener.h InputRenderListener.cpp
					$(COMPILE) InputRenderListener.cpp
					
InputManager.o:			InputManager.h InputManager.cpp
					$(COMPILE) InputManager.cpp
	
GameManager.o:		GameManager.h GameManager.cpp
					$(COMPILE) GameManager.cpp
		
GameDriver.o:		GameDriver.cpp
					$(COMPILE) GameDriver.cpp
					
RenderListener.o:		RenderListener.h RenderListener.cpp
					$(COMPILE) RenderListener.cpp
					
AnimationRenderListener.o:		AnimationRenderListener.h AnimationRenderListener.cpp
					$(COMPILE) AnimationRenderListener.cpp