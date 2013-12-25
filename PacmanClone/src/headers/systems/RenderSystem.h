#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../interfaces/System.h"
#include <SFML/Graphics.hpp>

class RenderSystem :
	public System
{
public:
	RenderSystem();
	~RenderSystem();
	
	void run(const float deltaTime);

	//some wrapper functions for the window object
	//maybe we should move this to its own manager class?
	bool isWindowOpen();
	bool pollWindowEvent(sf::Event& e);
	void closeWindow();

private:
	//a repository for our sprites, since components can only be
	//POD objects.  I want to enforce that design so having this
	//system keep track of sprites on its own seems like the most
	//obvious solution
	//the alternative I guess would be to make a sprite manager class,
	//but that seems dangerous.  it might actually be necessary in the
	//future if I want to have components affect the lighting of a sprite.
	//we'll see I guess?
	std::map<unsigned int, sf::Sprite*> _sprites;

	//is this the best place for this?
	sf::RenderWindow _window;

	//load a sprite to the map and return ptr to it for convenience
	sf::Sprite* loadSprite(const unsigned int entity);
};

#endif