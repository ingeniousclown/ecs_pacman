#include "..\headers\managers\AssetManager.h"

AssetManager::AssetManager()
{}

AssetManager::~AssetManager()
{
	//delete all assets
}

sf::Texture* AssetManager::getTexture(std::string filename)
{
	return new sf::Texture();
}