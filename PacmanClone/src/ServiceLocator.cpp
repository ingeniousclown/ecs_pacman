#include "headers\ServiceLocator.h"

EntityManager* ServiceLocator::_entityManager = NULL;
AssetManager* ServiceLocator::_assetManager = NULL;

void ServiceLocator::initialize()
{
	_entityManager = new EntityManager();
	//_audioManager = new AudioManager();
	//_gameStateManager = new GameStateManager();
	_assetManager = new AssetManager();
	//_systemManager = new SystemManager();
}

EntityManager* ServiceLocator::getEntityManager()
{
	return _entityManager;
}

AssetManager*  ServiceLocator::getAssetManager()
{
	return _assetManager;
}