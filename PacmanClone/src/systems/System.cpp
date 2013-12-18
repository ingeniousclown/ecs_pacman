#include "../headers/interfaces/System.h"

System::System(std::vector<Component::ComponentType> types) :
	_types(types)
{}

System::~System()
{
	_types.clear();
}

std::vector<Component::ComponentType> System::typeList()
{
	return _types;
}