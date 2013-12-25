#include "../headers/systems/PlayerControllerSystem.h"
#include "../headers/ServiceLocator.h"
#include <SFML/Window.hpp>

PlayerControllerSystem::PlayerControllerSystem()
{
	std::vector<Component::ComponentType> types;
	types.push_back(Component::VELOCITY);
	types.push_back(Component::INPUT);
	setTypes(types);
}

PlayerControllerSystem::~PlayerControllerSystem()
{}

void PlayerControllerSystem::run(const float deltaTime)
{
	EntityManager* entityMgr = ServiceLocator::getEntityManager();
	std::vector<unsigned int> entities = getEntities();

	for(std::vector<unsigned int>::iterator it = entities.begin();
		it != entities.end(); it++)
	{
		InputComponent* input = 
			static_cast<InputComponent*>(entityMgr->getComponent(*it, Component::INPUT));
		VelocityComponent* vel =
			static_cast<VelocityComponent*>(entityMgr->getComponent(*it, Component::VELOCITY));
		
		switch(input->playerNumber)
		{

		//player 1
		case 1:
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				vel->y -= (input->acceleration * deltaTime);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				vel->y += (input->acceleration * deltaTime);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				vel->x -= (input->acceleration * deltaTime);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				vel->x += (input->acceleration * deltaTime);
			}
			break;
		}

		//player 2 NYI
		case 2:
		{
			break;
		}

		//do nothing for this entitiy because the player number is not defined
		default:
			continue;
		}
	}
}