#include "headers\ServiceLocator.h"

EntityManager* ServiceLocator::_entityManager = NULL;

void ServiceLocator::initialize()
{
	_entityManager = new EntityManager();
	//_audioManager = new AudioManager();
	//_gameStateManager = new GameStateManager();
	//_assetManager = new AssetManager();
	//_systemManager = new SystemManager();
}

EntityManager* ServiceLocator::getEntityManager()
{
	return _entityManager;
}