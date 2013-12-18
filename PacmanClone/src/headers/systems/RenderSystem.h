#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../interfaces/System.h"

class RenderSystem :
	public System
{
public:
	RenderSystem(std::vector<Component::ComponentType> types);
	~RenderSystem();
	
	void run(const float deltaTime);

private:
};

#endif