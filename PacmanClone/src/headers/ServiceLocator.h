#ifndef SERVICELOCATOR_H
#define SERVICELOCATOR_H

#include "managers\EntityManager.h"

class ServiceLocator
{
public:
	//just initialize all members in here...
	//a more general implementation could let you provide one yourself
	static void initialize();

	static EntityManager* getEntityManager();
	//static AudioManager* getAudioManager();
	//static GameStateManager* getGameStateManager();
	//static AssetManager* getAssetManager();
	//static SystemManager* getSystemManager();

private:
	static EntityManager* _entityManager;
	//static AudioManager* _audioManager;
	//static GameStateManager* _gameStateManager;
	//static AssetManager* _assetManager;
	//static SystemManager* _systemManager;
};

#endif