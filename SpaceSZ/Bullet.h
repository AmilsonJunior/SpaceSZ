#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(b2World* world, bool dynamic, sf::Vector2f source)
		: Entity(world, dynamic, source)
	{
		_source = source;

		Load("Assets/textures/bullet.png");

		shape = new b2PolygonShape();
		shape->SetAsBox((sprite.getTexture()->getSize().x / 2) / 30.f, (sprite.getTexture()->getSize().y / 2) / 30.f);

		this->density = 900.f;
		this->friction = 0.0f;
		this->typeName = "Bullet";

		Initialize(shape, _source, dynamic);

	}
	~Bullet()
	{
		delete shape;
	}

	void PostUpdate(float frametime)
	{
		body->SetLinearVelocity(b2Vec2(0, -90));
		
		if (sprite.getPosition().y < -10)
		{
			active = false;
		}
	}

	void Draw(sf::RenderWindow& wnd)
	{
		Entity::Draw(wnd);
	}

private:
	b2PolygonShape* shape;
	sf::Vector2f _source;
};