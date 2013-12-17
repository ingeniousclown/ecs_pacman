#include <SFML/Graphics.hpp>
#include "headers\managers\EntityManager.h"
#include "headers\components\DrawableComponent.h"
#include "headers\components\TransformComponent.h"

#include <assert.h>

void testEntityMgr();

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 780), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	testEntityMgr();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
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