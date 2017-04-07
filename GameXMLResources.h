#if !defined GAME_XML_RESOURCES
#define GAME_XML_RESOURCES

#include "tinyxml.h"
#include "ListArray.h"
#include "GameResource.h"

class GameManager;

class GameXMLResources{
	private:
		TiXmlDocument tiny_xml_document;
		GameManager* game_manager;
}