#include "..\headers\managers\AssetManager.h"

AssetManager::AssetManager()
{}

AssetManager::~AssetManager()
{
	//delete all assets
}

sf::Texture* AssetManager::getTexture(std::string filename)
{
	if(!isTextureLoaded(filename))
		return loadTexture(filename);
	return _textures.find(filename)->second;
}

sf::Texture* AssetManager::loadTexture(std::string filename)
{
	sf::Texture* t = new sf::Texture();
	t->loadFromFile(filename);
	_textures.insert(std::pair<std::string, sf::Texture*>(filename, t));
	return t;
}

bool AssetManager::isTextureLoaded(std::string filename)
{
	if(_textures.find(filename) == _textures.end())
		return false;
	return true;
}