#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include "Component.h"

//okay, so it's not as much an interface as it is an abstract class
//this is because I wanted to enforce each system to keep track of its own types
class System
{
public:
	System(std::vector<Component::ComponentType> types);
	virtual ~System();

	//this is the function that will process entities each frame
	virtual void run(const float deltaTime) = 0;

protected:
	//nobody needs to know what types a system operates on except for itself
	std::vector<Component::ComponentType> getTypes();

private:
	std::vector<Component::ComponentType> _types;
};

#endif