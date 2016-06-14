#include "SimpleBox.h"
#include <iostream>


SimpleBox::SimpleBox(b2World* world, sf::Vector2f pos, bool dynamic)
	: Entity(world, dynamic, pos)
{
	Load("Assets/textures/box.png");

	shape = new b2PolygonShape();
	shape->SetAsBox((sprite.getTexture()->getSize().x / 2) / 30.f, (sprite.getTexture()->getSize().y / 2) / 30.f);
	this->friction = 1.f;
	this->density = 2.f;
	Initialize(shape, pos, dynamic, 0.5);

	vel.x = rand() % 6 + (-6);
	vel.y = rand() % 10 + (1);
}

SimpleBox::~SimpleBox()
{
	delete shape;
}

void SimpleBox::PostUpdate(float time)
{
	body->SetLinearVelocity(b2Vec2(vel.x, vel.y));
}

void SimpleBox::Draw(sf::RenderWindow & wnd)
{
	Entity::Draw(wnd);
}
