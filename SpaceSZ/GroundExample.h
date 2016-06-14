#pragma once
#include "EngineConstants.h"
#include "Entity.h"
#include "Game.h"

class Ground : public Entity
{
public:
	Ground(b2World* world, sf::Vector2f pos)
		: Entity(world, false, pos)
	{
		Load("Assets/textures/ground.png");

		shape = new b2PolygonShape;
		shape->SetAsBox((sprite.getTexture()->getSize().x / 2) / 30.f, (sprite.getTexture()->getSize().y / 2) / 30.f);

		Initialize(shape, pos, false);
	}
	~Ground()
	{

	}

	void Draw(sf::RenderWindow& wnd)
	{
		Entity::Draw(wnd);
	}
	void PostUpdate(float time)
	{
		
	}

private:
	b2PolygonShape* shape;
};