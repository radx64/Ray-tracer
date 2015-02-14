#include <exception>
#include <fstream>
#include <iostream>

#include "Loader.hpp"


namespace rt
{
namespace scene
{

Scene Loader::load(std::string filename)
{
	Scene scene;
	Json::Value root;
	std::ifstream file(filename);
	if (!file) throw std::string("Can't read " + filename);
	file >> root;
	//std::cout << root << std::endl;
	Json::Value sceneNode;
	sceneNode = getOrDie(root, "scene");
	scene.setName(sceneNode.get("name", "Name not set").asString());

	Json::Value objectsNode;
	objectsNode = getOrDie(sceneNode, "objects");

	for(auto& object : objectsNode)
	{
		if(object == "sphere")
		{
			//sphere creation
		}
	}

	return scene;
}

Json::Value Loader::getOrDie(Json::Value node, std::string name)
{
	Json::Value branch = node[name];
	if (branch != "null")
	{
		return branch;
	}	
	else
	{
		throw std::string("Error parsing branch " + name);
		return Json::Value();
	}
}

}  // namespace scene
}  // namespace rt