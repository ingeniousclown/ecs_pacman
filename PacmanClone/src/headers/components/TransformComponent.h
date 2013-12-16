#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../interfaces/Component.h"

struct TransformComponent :
	Component
{
	float x;
	float y;
	float rotation;	//in rads
}

#endif