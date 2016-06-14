#pragma once
#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile(b2World* world, bool dynamic, sf::Vector2f pos, sf::Vector2f mousePos);
	~Projectile();

	void PostUpdate(float frametime);
	void Draw(sf::RenderWindow& wnd);
	bool fired;
private:
	b2PolygonShape* shape;
	sf::Vector2f mousePos;
};
