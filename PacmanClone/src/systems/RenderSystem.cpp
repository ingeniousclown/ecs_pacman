#include "../headers/systems/RenderSystem.h"

RenderSystem::RenderSystem(std::vector<Component::ComponentType> types) :
	System(types)
{}

RenderSystem::~RenderSystem()
{}

void RenderSystem::run(const float deltaTime)
{
	typeList();
}