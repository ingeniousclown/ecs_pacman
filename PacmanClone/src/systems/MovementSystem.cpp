#include "../headers/systems/MovementSystem.h"
#include "../headers/ServiceLocator.h"
#include "../headers/components/TransformComponent.h"
#include "../headers/components/VelocityComponent.h"

MovementSystem::MovementSystem()
{
	std::vector<Component::ComponentType> types;
	types.push_back(Component::VELOCITY);
	types.push_back(Component::TRANSFORM);
	setTypes(types);
}

MovementSystem::~MovementSystem()
{}

void MovementSystem::run(const float deltaTime)
{
	EntityManager* entityMgr = ServiceLocator::getEntityManager();
	std::vector<unsigned int> entities = getEntities();

	for(std::vector<unsigned int>::iterator it = entities.begin();
		it != entities.end(); it++)
	{
		TransformComponent* trans = 
			static_cast<TransformComponent*>(entityMgr->getComponent(*it, Component::TRANSFORM));
		VelocityComponent* vel = 
			static_cast<VelocityComponent*>(entityMgr->getComponent(*it, Component::VELOCITY));
		
		trans->x += (vel->x * deltaTime);
		trans->y += (vel->y * deltaTime);
	}
}