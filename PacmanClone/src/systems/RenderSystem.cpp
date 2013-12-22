#include "../headers/systems/RenderSystem.h"
#include "../headers/ServiceLocator.h"
#include "../headers/components/TransformComponent.h"
#include "../headers/components/DrawableComponent.h"

RenderSystem::RenderSystem(std::vector<Component::ComponentType> types) :
	System(types)
{
	_window.create(sf::VideoMode(1280, 780), "SFML works!");
}
	

RenderSystem::~RenderSystem()
{}

void RenderSystem::run(const float deltaTime)
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	_window.clear();	//clear last frame
	_window.draw(shape);
	EntityManager* entityMgr = ServiceLocator::getEntityManager();
	std::vector<unsigned int> entities = entityMgr->getAllEntitiesWithComponent(getTypes());

	//for each entity that contains all types this sytem requires...
	//will need to eventually re-do this to make it render in a better order
	for(std::vector<unsigned int>::const_iterator it = entities.begin();
		it != entities.end(); it++)
	{
		sf::Sprite* sprite;
		
		//if we've loaded the sprite already, use it, else load it
		if(_sprites.find(*it) != _sprites.end())
		{
			sprite = _sprites.find(*it)->second;
		}
		else
		{
			sprite = loadSprite(*it);
		}

		//set sprite's position to value in transform component
		TransformComponent* transform = 
			static_cast<TransformComponent*>(entityMgr->getComponent(*it, Component::TRANSFORM));
		sprite->setPosition(transform->x, transform->y);

		_window.draw(*sprite);
	}

	_window.display();	//display current frame
}

bool RenderSystem::isWindowOpen()
{
	return _window.isOpen();
}

bool RenderSystem::pollWindowEvent(sf::Event& e)
{
	return _window.pollEvent(e);
}

void RenderSystem::closeWindow()
{
	_window.close();
}

sf::Sprite* RenderSystem::loadSprite(const unsigned int entity)
{
	AssetManager* assetMgr = ServiceLocator::getAssetManager();
	DrawableComponent* drawable = 
		static_cast<DrawableComponent*>(ServiceLocator::getEntityManager()->getComponent(entity, Component::DRAWABLE));

	sf::Sprite* sprite = new sf::Sprite();

	//give sprite a texture (if texture isn't loaded, it will be by the assetmgr)
	sprite->setTexture(*(assetMgr->getTexture(drawable->textureLocation)));

	//put sprite ptr into map and return the ptr
	_sprites.insert(std::pair<const unsigned int, sf::Sprite*>(entity, sprite));

	return sprite;
}