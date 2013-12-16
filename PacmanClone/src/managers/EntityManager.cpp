#include "../headers/managers/EntityManager.h"
#include "../headers/Constants.h"

EntityManager::EntityManager() :
	_nextUnusedId(0)
{ }

EntityManager::~EntityManager()
{
	//delete all the components
}

Component* EntityManager::getComponent(const unsigned int entity, ComponentType cType)
{
	if(!doesEntityExist(entity))
		throw Exception::NO_SUCH_ENTITY_EXCEPTION;

	return _components.find(cType)->second.find(entity)->second;
}

std::vector<unsigned int> EntityManager::getAllEntitiesWithComponent(ComponentType cType)
{
	std::vector<unsigned int> output;
	std::map<ComponentType, std::map<unsigned int, Component*>>::iterator cTypeMapIt = _components.find(cType);
	
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
std::vector<unsigned int> EntityManager::getAllEntitiesWithComponent(std::vector<ComponentType> cTypes)
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
	_entities.insert(++_nextUnusedId);
	return _nextUnusedId;
}

void EntityManager::addComponent(const unsigned int entity, ComponentType cType, Component* component)
{
	if(!doesEntityExist(entity))
		throw Exception::NO_SUCH_ENTITY_EXCEPTION;

	_components.find(cType)->second.insert(std::pair<unsigned int, Component*>(entity, component));
}

//this will erase the reference to a component, so we should delete it
void EntityManager::removeComponent(const unsigned int entity, ComponentType cType, Component* component)
{
	if(!doesEntityExist(entity))
		throw Exception::NO_SUCH_ENTITY_EXCEPTION;

	//get the map of the components we want
	std::map<unsigned int, Component*> temp = _components.find(cType)->second;

	//delete the component
	delete temp.find(entity)->second;
	//now erase the entity from the map
	temp.erase(entity);
}

bool EntityManager::doesEntityExist(const unsigned int entity)
{
	return _entities.find(entity) == _entities.end();
}