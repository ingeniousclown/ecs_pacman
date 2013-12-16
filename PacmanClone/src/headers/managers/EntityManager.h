#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <set>
#include <map>
#include "../Entity.hpp"
#include "../interfaces/Component.h"
#include "../components/ComponentType.h"

//this whole class is modeled heavily after the entitymanager here:
//https://github.com/Razoric480/EntitySystem-Pong
class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Component* getComponent(const unsigned int entity, ComponentType cType);

	//returns a vector of entity ids that contain the component type
	std::vector<unsigned int> getAllEntitiesWithComponent(ComponentType cType);
	
	//returns a vector of entity ids that contain all the component types
	//is there a better way to do this?
	std::vector<unsigned int> getAllEntitiesWithComponent(std::vector<ComponentType> cTypes);
	unsigned int createNewEntity();

	void addComponent(const unsigned int entity, ComponentType cType, Component* component);
	void removeComponent(const unsigned int entity, ComponentType cType, Component* component);

private:
	unsigned int _nextUnusedId;

	std::set<int> _entities;
	//dictionary of components mapped to a dictionary of entityIds to components
	//note this isn't very type-safe (relative to ComponentType) so implementing right is important
	//eg value of ComponentType.DRAWABLE could potentially contain a TRANSFORMABLE.  don't do this!
	std::map<ComponentType, std::map<unsigned int, Component*>> _components;
};

#endif