#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include "interfaces\Component.h"

class Entity
{
public:
	Entity();

private:
	const unsigned int id;
	
	std::vector<Component*> components;
};

#endif