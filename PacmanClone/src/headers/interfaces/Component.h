#ifndef COMPONENT_H
#define COMPONENT_H

struct Component 
{
	//a simple enum denoting all the component types
	//update as you add components
	enum ComponentType
	{
		DRAWABLE,
		TRANSFORM,
		VELOCITY
	};
};

#endif