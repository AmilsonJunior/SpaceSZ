#pragma once
#include "Entity.h"
#include "EngineConstants.h"

class SimpleBox : public Entity
{
public:
	SimpleBox(b2World* world, sf::Vector2f pos, bool dynamic);
	~SimpleBox();

	void PostUpdate(float time);
	void Draw(sf::RenderWindow& wnd);

private:
	b2PolygonShape* shape;
	b2Vec2 vel;
};

