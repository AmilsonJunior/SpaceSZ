#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "EngineConstants.h"


class Entity
{
public:
	Entity(b2World* world, bool dynamic, const sf::Vector2f& pos);
	~Entity();
	
	virtual void Update(float frameTime);
	virtual void Draw(sf::RenderWindow& wnd);
	virtual void HandleEvents(sf::Event& event);
	bool isActive() const { return active; }
	sf::Vector2f GetPosition() const { return sprite.getPosition(); }
protected:
	void Load(const std::string& name);
	void Initialize(b2Shape* shape, sf::Vector2f pos, bool dynamic, float scale = 1);
	virtual void PostUpdate(float frametime);

	b2Body* body;
	b2BodyDef* bodyDef;
	b2Shape* bodyShape;
	b2World* world;
	b2FixtureDef* fixDef;

	sf::Sprite sprite;

	bool active;
	float density;
	float friction;
private:
	sf::Texture* texture;
};

//class RectEntity
//{
//public:
//	RectEntity(b2World* world, bool dynamic, const sf::Vector2f& pos)
//	{
//		this->world = world;
//		bodyDef = new b2BodyDef();
//		bodyShape = new b2PolygonShape();
//		fixDef = new b2FixtureDef();
//
//		if (dynamic)
//			bodyDef->type = b2_dynamicBody;
//		else
//			bodyDef->type = b2_staticBody;
//
//		bodyDef->position = b2Vec2(pos.x / 30.f, pos.y / 30.f);
//		sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
//
//	}
//	~RectEntity()
//	{
//	}
//
//	void Render()
//
//protected:
//	b2Body* body;
//	b2BodyDef* bodyDef;
//	b2Shape* bodyShape;
//	b2World* world;
//	b2FixtureDef* fixDef;
//	sf::RectangleShape sprite;
//};
