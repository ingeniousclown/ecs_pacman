#ifndef PLAYERCONTROLLERSYSTEM_H
#define PLAYERCONTROLLERSYSTEM_H

#include "../interfaces/System.h"
#include "../components/InputComponent.h"
#include "../components/VelocityComponent.h"

class PlayerControllerSystem :
	public System
{
public:
	PlayerControllerSystem();
	~PlayerControllerSystem();

	void run(const float deltaTime);

private:
};

#endif