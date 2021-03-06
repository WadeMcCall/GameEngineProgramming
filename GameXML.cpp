#include "GameXML.h"
#include "GameManager.h"
#include "Utils.h"
#include "PathResource.h"
#include "MeshResource.h"
#include "AudioResource.h"

#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;

void GameXML::buildXMLScene(std::string requested_level_name, GameManager* game_manager){
	TiXmlElement* scene_element = scenes_xml_document->RootElement();
	TiXmlElement* level_element = scene_element->FirstChildElement("level");
	while(level_element != NULL){
		TiXmlElement* level_name_element = level_element->FirstChildElement("name");
		std::string level_name_str = level_name_element->GetText();
		if(requested_level_name == level_name_str){
			TiXmlElement* camera_element = level_element->FirstChildElement("camera");
			TiXmlElement* camera_name_element = camera_element->FirstChildElement("name");
			std::string camera_name_str = camera_name_element->GetText();
			
			TiXmlElement* camera_position_element = camera_element->FirstChildElement("position");
			std::string camera_position_str = camera_position_element->GetText();
			float camera_position[3];
			Utils::parseFloats(camera_position_str, camera_position);
			
			float camera_lookat[3];
			TiXmlElement* camera_lookat_element = camera_element->FirstChildElement("look-at");
			std::string camera_lookat_str = camera_lookat_element->GetText();
			Utils::parseFloats(camera_lookat_str, camera_lookat);
			
			float camera_clip[2];
			TiXmlElement* camera_clip_element = camera_element->FirstChildElement("clip");
			std::string camera_clip_str = camera_clip_element->GetText();
			Utils::parseFloats(camera_clip_str, camera_clip);
			
			game_manager->createCamera(camera_name_str, camera_position, camera_lookat, camera_clip);
			
			TiXmlElement* light_element = level_element->FirstChildElement("light");
			TiXmlElement* light_name_element = light_element->FirstChildElement("name");
			std::string light_name_str = light_name_element->GetText();
			
			TiXmlElement* light_color_element = light_element->FirstChildElement("color");
			std::string light_color_str = light_color_element->GetText();
			float light_color[3];
			Utils::parseFloats(light_color_str, light_color);
			
			float light_direction[3];
			TiXmlElement* light_direction_element = light_element->FirstChildElement("direction");
			std::string light_direction_str = light_direction_element->GetText();
			Utils::parseFloats(light_direction_str, light_direction);
			
			game_manager->createLight(light_name_str, light_color, light_direction);
			
			TiXmlElement* graph_element = level_element->FirstChildElement("graph");
			TiXmlElement* children_element = graph_element->FirstChildElement("children");
			game_manager->logComment("building scene XML");
			processChildren(children_element, "root", game_manager);
		}
		level_element = level_element->NextSiblingElement();
	}
	game_manager->createRigidBodies();
}

void GameXML::buildAnimation(std::string animation_node_str, TiXmlElement* animation_element, GameManager* game_manager){
	TiXmlElement* name_element = animation_element->FirstChildElement("name");
	std:string animation_name_str = name_element->GetText();
	
	TiXmlElement* time_element = animation_element->FirstChildElement("seconds");
	std::string animation_time_str = time_element->GetText();
	float seconds = atof(animation_time_str.c_str());
		
	//Ogre::Animation* animation = scene_manager->createAnimation(animation_name_str, seconds);//***
	//animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	//
	//Ogre::NodeAnimationTrack* track = animation->createNodeTrack(1, animation_node);
	//
	//Ogre::TransformKeyFrame* key_frame;
	//
	TiXmlElement* keyframes_element = animation_element->FirstChildElement("keyframes");
	TiXmlElement* keyframe_element = keyframes_element->FirstChildElement("keyframe");
	vector<float> key_frame_times;		
	vector<float*> key_frame_translate;		
	vector<float*> key_frame_rotate;
	while(keyframe_element != NULL){
		
		TiXmlElement* keyframe_time_element = keyframe_element->FirstChildElement("time");
		TiXmlElement* translate_element = keyframe_element->FirstChildElement("translation");
		TiXmlElement* rotate_element = keyframe_element->FirstChildElement("rotation");
		
		std::string time_str = keyframe_time_element->GetText();
		float time = (float)atof(time_str.c_str());
		cout << "time: " << time;
		
		float* translate_values = new float[3];
		float* rotate_values = new float[4];
		std::string translate_str = translate_element->GetText();
		Utils::parseFloats(translate_str, translate_values);
		
		
		//key_frame = track->createNodeKeyFrame(time);
		//key_frame->setTranslate(Ogre::Vector3(translate_values[0],translate_values[1],translate_values[2]));
		cout << endl << "building animation GameXML " << endl;
		key_frame_times.push_back(time);
		key_frame_translate.push_back(translate_values);
		
		std::string rotate_str = rotate_element->GetText();
		Utils::parseFloats(rotate_str, rotate_values);
		key_frame_rotate.push_back(rotate_values);
		
		//Ogre::Vector3 rotate_axis(translate_values[1],translate_values[2],translate_values[3]);
		//Ogre::Quaternion q1(Ogre::Degree(translate_values[0]), rotate_axis);
		//key_frame->setRotation(q1);
		
		keyframe_element = keyframe_element->NextSiblingElement("keyframe");
	}
	game_manager->createAnimation(animation_node_str, animation_name_str, seconds, key_frame_times, key_frame_translate, key_frame_rotate);
	
	//Ogre::AnimationState* animation_state = scene_manager->createAnimationState(animation_name_str);//***
	//animation_state->setEnabled(true); 
	//animation_state->setLoop(true);
	//
	//game_manager->addAnimationState(animation_state);
	//animation_states->add(animation_state);
	
	//game_manager->logComment("built Animations");
}

void GameXML::processChildren(TiXmlElement* children_element, std::string parent_name_string, GameManager* game_manager){
	if(children_element == NULL) return;
	
	TiXmlElement* child_element = children_element->FirstChildElement("child");
	while(child_element !=NULL){
		TiXmlElement* name_element = child_element->FirstChildElement("name");
		std::string child_name_str = name_element->GetText();
		game_manager->createSceneNode(child_name_str, parent_name_string);
		std::cout << std::endl << child_name_str << std::endl;
		
		TiXmlElement* entity_element = child_element->FirstChildElement("entity");
		TiXmlElement* animation_element = (TiXmlElement*) child_element->FirstChild("animation");
		if(entity_element != NULL){
			TiXmlElement* entity_name_element = entity_element->FirstChildElement("name");
			std::string entity_name_str = entity_name_element->GetText();
			
			TiXmlElement* entity_mesh_element = entity_element->FirstChildElement("mesh");
			std::string entity_mesh_str = entity_mesh_element->GetText();
			
			TiXmlElement* entity_material_element = entity_element->FirstChildElement("material");
			std::string entity_material_str = entity_material_element->GetText();
			cout << "material " << entity_material_str << endl;
			
			game_manager->attachEntity(entity_name_str, entity_mesh_str, entity_material_str, child_name_str);
		}
		if(animation_element != NULL){
			buildAnimation(child_name_str, animation_element, game_manager);
		}
		TiXmlElement* physics_element = (TiXmlElement*) child_element->FirstChild("physics");
		while(physics_element != NULL){
			TiXmlElement* collision_shape_element = physics_element->FirstChildElement("collision_shape");
			std::string collision_shape_name_str = collision_shape_element->GetText();
			
			TiXmlElement* translation_element = physics_element->FirstChildElement("translation");
			std::string translation_str = translation_element->GetText();
			float translation[3];
			Utils::parseFloats(translation_str, translation);
			
			TiXmlElement* rotation_element = physics_element->FirstChildElement("rotation");
			std::string rotation_str = rotation_element->GetText();
			float rotation[4];
			Utils::parseFloats(rotation_str, rotation);
			
			TiXmlElement* collision_parameters_element = physics_element->FirstChildElement("collision_parameters");
			std::string collision_parameters_str = collision_parameters_element->GetText();
			float params[3];
			Utils::parseFloats(collision_parameters_str, params);
			
			TiXmlElement* mass_element = physics_element->FirstChildElement("mass");
			std::string mass_str = mass_element->GetText();
			float mass = stof(mass_str);
			
			game_manager->createCollisionShape(child_name_str, collision_shape_name_str, params, mass, translation, rotation);
			physics_element = (TiXmlElement*) physics_element->NextSiblingElement("physics");
		}
		
		TiXmlElement* translate_element = child_element->FirstChildElement("translation");
		std::string translate_str = translate_element->GetText();
		float translation[3];
		Utils::parseFloats(translate_str, translation);
		game_manager->processTranslation(translation, child_name_str);
		
		TiXmlElement* rotation_element = child_element->FirstChildElement("rotation");
		std::string rotation_str = rotation_element->GetText();
		float rotation[4];
		Utils::parseFloats(rotation_str,rotation);
		game_manager->processRotation(rotation, child_name_str);
		
		TiXmlElement* scale_element = child_element->FirstChildElement("scale");
		std::string scale_str = scale_element->GetText();
		float scale[3];
		Utils::parseFloats(scale_str, scale);
		game_manager->processScale(scale, child_name_str);
		
		TiXmlElement* grand_children_element = child_element->FirstChildElement("children");
		processChildren(grand_children_element, child_name_str, game_manager);
		
		child_element = child_element->NextSiblingElement();		
	}
}

GameXML::GameXML(const char* resources_file_name, const char* scenes_file_name)
{
	resources_xml_document = new TiXmlDocument(resources_file_name);
	bool success = resources_xml_document->LoadFile();
	if(!success){
		throw std::runtime_error("Error Parsing XML Resources File");
	}
	
	scenes_xml_document = new TiXmlDocument(scenes_file_name);
	success = scenes_xml_document->LoadFile();
	if(!success){
		throw std::runtime_error("Error Parsing XML Scenes file");
	}
	//game_manager->logComment("GameXMl initialised");
}

GameXML::~GameXML(){
}

ListArray<GameResource>* GameXML::getXMLGameResourcesByLevel(std::string requested_level_name, GameManager* game_manager){
	ListArray<GameResource>* game_resources = new ListArray<GameResource>();
	
	TiXmlElement* levels_element = resources_xml_document->RootElement();
	TiXmlElement* level_element = levels_element->FirstChildElement("level");
	
	while(level_element != NULL){
		TiXmlElement* level_name_element = level_element->FirstChildElement("name");
		std::string level_name_str = level_name_element->GetText();
		if(requested_level_name == level_name_str){
			TiXmlElement* paths_element = level_element->FirstChildElement("paths");
			TiXmlElement* path_element = paths_element->FirstChildElement("path");
			
			while(path_element!=NULL){
				std::string path_str = path_element->GetText();
				PathResource* path_resource = new PathResource(requested_level_name, path_str, PATH, game_manager);
				game_resources->add(path_resource);
				path_element = path_element->NextSiblingElement();
			}
			
			TiXmlElement* meshes_element = level_element->FirstChildElement("meshes");
			TiXmlElement* mesh_element = meshes_element->FirstChildElement("mesh");
			
			while(mesh_element != NULL){
				std::string mesh_str = mesh_element->GetText();
				MeshResource* mesh_resource = new MeshResource(requested_level_name, mesh_str, MESH, game_manager);
				game_resources->add(mesh_resource);
				mesh_element = mesh_element->NextSiblingElement();
			}
			
			TiXmlElement* audios_element = level_element->FirstChildElement("audios");
			if(audios_element!=NULL){
				TiXmlElement* audio_element = audios_element->FirstChildElement("audio");
				while(audio_element!= NULL){
					TiXmlElement* file_element = audio_element->FirstChildElement("file");
					TiXmlElement* type_element = audio_element->FirstChildElement("type");
					TiXmlElement* name_element = audio_element->FirstChildElement("name");
					
					std::string file_name = file_element->GetText();
					std::string type_name = type_element->GetText();
					std::string sound_name = name_element->GetText();
					AudioResource* audio_resource;
					if(type_name == "stream")
						audio_resource = new AudioResource(requested_level_name, file_name, sound_name, STREAM);
					else
						audio_resource = new AudioResource(requested_level_name, file_name, sound_name, SAMPLE);
					game_resources->add(audio_resource);
					audio_element = audio_element->NextSiblingElement();
				}
			}
		}
		level_element = level_element->NextSiblingElement();
	}
	return game_resources;
}