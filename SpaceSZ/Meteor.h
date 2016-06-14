#pragma once
#include "Entity.h"
#include "EngineConstants.h"

class Meteor : public Entity
{
public:
	Meteor(b2World* world, sf::Vector2f pos, bool dynamic);
	~Meteor();

	void PostUpdate(float time);
	void Draw(sf::RenderWindow& wnd);

private:
	b2CircleShape* shape;
	b2Vec2 vel;
};

