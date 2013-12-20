#include "../headers/systems/RenderSystem.h"
#include "../headers/ServiceLocator.h"

RenderSystem::RenderSystem(std::vector<Component::ComponentType> types) :
	System(types)
{}
	

RenderSystem::~RenderSystem()
{}

void RenderSystem::run(const float deltaTime)
{
	_window.clear();	//clear last frame
	EntityManager* entityMgr = ServiceLocator::getEntityManager();
	std::vector<unsigned int> entities = entityMgr->getAllEntitiesWithComponent(getTypes());

	//for each entity that contains all types this sytem requires...
	for(std::vector<unsigned int>::const_iterator it = entities.begin();
		it != entities.end(); it++)
	{
		//if the entity number doesn't have a sprite
		//...call load sprite for entity

		//set sprite's position to value in transform component
		//draw sprite to window
	}

	_window.display();	//display current frame
}

sf::Sprite* RenderSystem::loadSprite(const unsigned int entity)
{
	//create new sprite ptr
	//give sprite a texture (if texture isn't loaded, it will be by the assetmgr)
	//put sprite ptr into map
	//return ptr
	return new sf::Sprite();
}