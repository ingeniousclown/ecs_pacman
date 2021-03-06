#include <SFML/Graphics.hpp>
#include "headers\managers\EntityManager.h"
#include "headers\components\DrawableComponent.h"
#include "headers\components\TransformComponent.h"
#include "headers\components\VelocityComponent.h"
#include "headers\components\InputComponent.h"
#include "headers\systems\RenderSystem.h"
#include "headers\systems\MovementSystem.h"
#include "headers\systems\PlayerControllerSystem.h"
#include "headers\ServiceLocator.h"

#include <assert.h>

void testEntityMgr();

int main()
{
	//testEntityMgr();

	ServiceLocator::initialize();
	System* renderSystem = new RenderSystem();
	System* movementSystem = new MovementSystem();
	System* playerControllerSystem = new PlayerControllerSystem();

	//this block creates an entity with four components
	//yes, this is the general setup for creating entities
	//it's a lot, but the eventual goal is to automate the crap out of this
	const unsigned int entity = ServiceLocator::getEntityManager()->createNewEntity();
	DrawableComponent* draw = new DrawableComponent();
	draw->textureLocation = "assets/images/pacman.png";
	TransformComponent* trans = new TransformComponent();
	trans->x = 30;  trans->y = 30;  trans->rotation = 0;
	VelocityComponent* vel = new VelocityComponent();
	vel->x = 10;	vel->y = 20;
	InputComponent* input = new InputComponent();
	input->acceleration = 5;	input->playerNumber = 1;
	ServiceLocator::getEntityManager()->addComponent(entity, Component::DRAWABLE, draw);
	ServiceLocator::getEntityManager()->addComponent(entity, Component::TRANSFORM, trans);
	ServiceLocator::getEntityManager()->addComponent(entity, Component::VELOCITY, vel);
	ServiceLocator::getEntityManager()->addComponent(entity, Component::INPUT, input);

    while (static_cast<RenderSystem*>(renderSystem)->isWindowOpen())
    {
        sf::Event event;
        while (static_cast<RenderSystem*>(renderSystem)->pollWindowEvent(event))
        {
            if (event.type == sf::Event::Closed)
                static_cast<RenderSystem*>(renderSystem)->closeWindow();
        }

		playerControllerSystem->run(0.01f);
		movementSystem->run(0.01f);
		renderSystem->run(0.01f);
    }

    return 0;
}

//just a super quick-and-dirty implementation of the entity manager to test it
void testEntityMgr()
{
	//let's test the entity manager
	EntityManager mgr = EntityManager();
	unsigned int entity = mgr.createNewEntity();

	DrawableComponent* dr = new DrawableComponent();
	dr->textureLocation = "lol";
	printf("%s\n", dr->textureLocation.c_str());
	TransformComponent* tr = new TransformComponent();
	tr->x = 15; tr->y = 24; tr->rotation = 1.45f;

	mgr.addComponent(entity, Component::DRAWABLE, dr);
	mgr.addComponent(entity, Component::TRANSFORM, tr);
	
	DrawableComponent* dr2 = new DrawableComponent();
	dr2->textureLocation = "trollol";

	mgr.addComponent(mgr.createNewEntity(), Component::DRAWABLE, dr2);
	std::vector<unsigned int> test;

	test = mgr.getAllEntitiesWithComponent(Component::TRANSFORM);
	assert(test.size() == 1);
	float x, y, r;
	x = static_cast<TransformComponent*>(mgr.getComponent(test[0], Component::TRANSFORM))->x;
	y = static_cast<TransformComponent*>(mgr.getComponent(test[0], Component::TRANSFORM))->y;
	r = static_cast<TransformComponent*>(mgr.getComponent(test[0], Component::TRANSFORM))->rotation;
	printf("%f %f %f\n", x, y, r);
	
	test = mgr.getAllEntitiesWithComponent(Component::DRAWABLE);
	std::string s;
	assert(test.size() == 2);
	s = static_cast<DrawableComponent*>(mgr.getComponent(test[0], Component::DRAWABLE))->textureLocation;
	printf("%s\n", s.c_str());

	mgr.removeComponent(0, Component::DRAWABLE);
	test = mgr.getAllEntitiesWithComponent(Component::DRAWABLE);
	assert(test.size() == 1);
	s = static_cast<DrawableComponent*>(mgr.getComponent(test[0], Component::DRAWABLE))->textureLocation;
	printf("%s\n", s.c_str());
}