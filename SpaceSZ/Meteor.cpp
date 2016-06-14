#include "Meteor.h"

#include <iostream>


Meteor::Meteor(b2World* world, sf::Vector2f pos, bool dynamic)
	: Entity(world, dynamic, pos)
{
	Load("Assets/textures/meteor1.png");

	shape = new b2CircleShape();
	shape->m_radius = 0.7f;
	
	this->friction = 0.f;
	this->density = rand() % 50 + 200;
	this->typeName = "Meteor";

	Initialize(shape, pos, dynamic, 0.5);

	vel.x = rand() % 6 + (-6);
	vel.y = rand() % 10 + (1);
}

Meteor::~Meteor()
{
	delete shape;

	std::cout << "Deleted meteor\n";
}

void Meteor::PostUpdate(float time)
{
	body->SetLinearVelocity(b2Vec2(vel.x, vel.y));
	sprite.setRotation(180 / b2_pi * body->GetAngle());
}

void Meteor::Draw(sf::RenderWindow & wnd)
{
	Entity::Draw(wnd);
}
