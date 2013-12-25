#include "../headers/interfaces/System.h"
#include "../headers/ServiceLocator.h"

System::System()
{}

System::~System()
{
	_types.clear();
}

std::vector<Component::ComponentType> System::getTypes()
{
	return _types;
}

void System::setTypes(std::vector<Component::ComponentType> types)
{
	_types = types;
}

std::vector<unsigned int> System::getEntities()
{
	return ServiceLocator::getEntityManager()->getAllEntitiesWithComponent(_types);
}