#include "../headers/managers/EntityManager.h"
#include "../headers/Constants.h"
#include <assert.h>


EntityManager::EntityManager() :
	_nextUnusedId(0)
{ }

EntityManager::~EntityManager()
{
	//delete all the components
	printf("Destroying entity manager...\n");
	int numEntities = _entities.size();
	int numTypes = _components.size();

	for(std::map<Component::ComponentType, std::map<unsigned int, Component*>>::iterator it = _components.begin();
		it != _components.end(); it++)
	{
		std::map<unsigned int, Component*>& temp = it->second;
		for(std::map<unsigned int, Component*>::iterator innerIt = temp.begin();
			innerIt != temp.end(); innerIt++)
		{
			delete innerIt->second;
		}
		temp.clear();
	}
	_components.clear();

	_entities.clear();
	printf("Done destroying entity manager...\n");
}

Component* EntityManager::getComponent(const unsigned int entity, Component::ComponentType cType)
{
	assert(doesEntityExist(entity));

	return _components.find(cType)->second.find(entity)->second;
}

std::vector<unsigned int> EntityManager::getAllEntitiesWithComponent(Component::ComponentType cType)
{
	std::vector<unsigned int> output;
	std::map<Component::ComponentType, std::map<unsigned int, Component*>>::iterator cTypeMapIt = _components.find(cType);
	
	//make sure component exists
	if(cTypeMapIt == _components.end())
		return output;	//return empty vector

	//components exist, good, move on
	//get a more convenient reference to the components we want
	std::map<unsigned int, Component*> allComponents = cTypeMapIt->second;

	//dump all the unsigned ints into our output vector
	for(std::map<unsigned int, Component*>::iterator it = allComponents.begin();
		it != allComponents.end(); it++)
	{
		output.push_back(it->first);
	}

	return output;
}

//this is going to be a first-pass attempt - expect it to be crappy and slow and inefficient
std::vector<unsigned int> EntityManager::getAllEntitiesWithComponent(std::vector<Component::ComponentType> cTypes)
{
	std::vector<unsigned int> output;
	int numTypes = cTypes.size();
	
	//make sure list isnt empty
	if(numTypes == 0)
		return output;	//return empty vector

	//if only one type, just return the one-type function
	if(numTypes == 1)
		return getAllEntitiesWithComponent(cTypes[0]);

	//fill a vector with all the possible entity ids; a list of the first type
	//we will check the map against this list and add to output vector accordingly
	std::vector<unsigned int> possibleEntities = getAllEntitiesWithComponent(cTypes[0]);

	//for each possible entity...
	for(std::vector<unsigned int>::iterator it = possibleEntities.begin();
			it != possibleEntities.end(); it++)
	{
		bool shouldAdd = true;
		//for each other type...
		for(int i = 1; i < numTypes; i++)
		{
			//check the current component type's map for the entity id
			if(_components.find(cTypes[i])->second.find(*it) ==  _components.find(cTypes[i])->second.end())
			{	//if it doesn't exist, then set shouldAdd to false and break to outer loop
				shouldAdd = false;
				break;
			}
			//else keep going
		}
		//if we didn't break out, shouldAdd is true so we add id to output
		if(shouldAdd)
		{
			output.push_back(*it);
		}
	}

	return output;
}

//very naive implementation - no int overflow protection
unsigned int EntityManager::createNewEntity()
{
	unsigned int entity = _nextUnusedId++;
	_entities.insert(entity);
	return entity;
}

void EntityManager::addComponent(const unsigned int entity, Component::ComponentType cType, Component* component)
{
	assert(doesEntityExist(entity));

	//check first if _components list has the component type, add it if it doesn't
	if(_components.find(cType) == _components.end())
		_components.insert(
			std::pair<Component::ComponentType,
				std::map<unsigned int, Component*>>(cType, std::map<unsigned int, Component*>()));

	_components.find(cType)->second.insert(std::pair<unsigned int, Component*>(entity, component));
}

//this will erase the reference to a component, so we should delete it
void EntityManager::removeComponent(const unsigned int entity, Component::ComponentType cType)
{
	assert(doesEntityExist(entity));

	//get the map of the components we want
	//getting the reference instead of value so we don't accidentally copy
	std::map<unsigned int, Component*>& temp = _components.find(cType)->second;

	//delete the component
	delete temp.find(entity)->second;
	//now erase the entity from the map
	temp.erase(entity);
}

bool EntityManager::doesEntityExist(const unsigned int entity)
{
	return _entities.find(entity) != _entities.end();
}