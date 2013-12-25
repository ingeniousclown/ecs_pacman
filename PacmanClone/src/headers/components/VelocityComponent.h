#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include "../interfaces/Component.h"

struct VelocityComponent :
	Component
{
	float x;
	float y;
	float maxX;
	float maxY;
};

#endif