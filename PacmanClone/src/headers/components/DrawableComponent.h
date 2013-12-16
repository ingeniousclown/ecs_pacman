#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include "../interfaces/Component.h"

struct DrawableComponent :
	Component
{
	std::String textureLocation;
};

#endif