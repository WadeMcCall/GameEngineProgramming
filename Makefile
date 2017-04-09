AutomatedMakefile = am
CC = g++

INC_DIRS=-I./ -I$(OGRE_PATH)/OgreMain/include -I$(BOOST_PATH) -I$(TINYXML_DIR)/include -I$(OIS_PATH)/include -I$(BASS_PATH)
LIB_DIRS=-L./ -L$(OGRE_PATH)/build/lib -L$(BOOST_PATH)/stage/lib -L$(TINYXML_DIR)/lib -L$(OIS_PATH)/lib -L$(BASS_PATH)
LIBS=-lboost_system-mgw51-mt-1_63 -lOgreMain -ltinyxml -lOIS -lbass

COMPILE = $(CC) $(INC_DIRS) -c
LINK = $(CC) $(LIB_DIRS) -o

FILES = AudioPlayer.o AudioResource.o AudioManager.o GameResource.o PathResource.o MeshResource.o ResourceManager.o GameXML.o LogManager.o InputManager.o RenderManager.o GameManager.o RenderListener.o GameDriver.o Utils.o AnimationRenderListener.o InputRenderListener.o 

all: Ogre

Ogre: 	$(FILES)
		$(LINK) Game.exe $(FILES) $(LIBS)
					
AudioManager.o:		AudioManager.h AudioManager.cpp
					$(COMPILE) AudioManager.cpp
					
AudioPlayer.o:		AudioPlayer.h AudioPlayer.cpp
					$(COMPILE) AudioPlayer.cpp
					
AudioResource.o:	AudioResource.h AudioResource.cpp
					$(COMPILE) AudioResource.cpp
		
GameResource.o:		GameResource.h GameResource.cpp
					$(COMPILE) GameResource.cpp
					
PathResource.o:		PathResource.h PathResource.cpp
					$(COMPILE) PathResource.cpp
					
MeshResource.o:		MeshResource.h MeshResource.cpp
					$(COMPILE) MeshResource.cpp
					
ResourceManager.o:	ResourceManager.h ResourceManager.cpp
					$(COMPILE) ResourceManager.cpp -fpermissive

GameXML.o:			GameXML.h GameXML.cpp
					$(COMPILE) GameXML.cpp
					
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