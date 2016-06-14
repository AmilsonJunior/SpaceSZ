#pragma once
#include "Entity.h"
#include "Weapon.h"

class Player : public Entity
{
public:
	Player(b2World* world, sf::Vector2f pos);
	~Player();

	void PostUpdate(float frametime);
	void Draw(sf::RenderWindow& wnd);
	void SetAngleShot(float as) { angleShot = as; }
	float GetAngleShot() const { return angleShot; }
private:
	b2PolygonShape* shape;
	float angleShot;
	int life;
	float velocity;
};

