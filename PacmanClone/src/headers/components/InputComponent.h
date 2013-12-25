#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "../interfaces/Component.h"

struct InputComponent :
	Component
{
	int playerNumber;
	float acceleration;
};

#endif