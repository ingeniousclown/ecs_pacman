#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../interfaces/System.h"
#include "../interfaces/Component.h"

class MovementSystem :
	public System
{
public:
	MovementSystem();
	~MovementSystem();

	void run(const float deltaTime);

private:


};

#endif