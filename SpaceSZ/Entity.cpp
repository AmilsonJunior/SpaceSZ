#include "Entity.h"
#include "Game.h"

Entity::Entity(b2World* world, bool dynamic, const sf::Vector2f& pos)
{
	this->world = world;
	this->texture = new sf::Texture();
	this->bodyDef = new b2BodyDef();
	active = true;
	density = 0;
	friction = 0;
}

Entity::~Entity()
{
	delete texture;
	delete bodyDef;
//	delete bodyShape;
	delete fixDef;
	delete texture;
}

void Entity::Initialize(b2Shape* shape, sf::Vector2f pos, bool dynamic, float scale)
{
	if (dynamic)
		bodyDef->type = b2_dynamicBody;
	else
		bodyDef->type = b2_staticBody;

	bodyDef->position = b2Vec2(pos.x / 30.f, pos.y / 30.f);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

	body = this->world->CreateBody(bodyDef);
	this->bodyShape = shape;

	if (dynamic)
	{
		fixDef = new b2FixtureDef();
		fixDef->shape = this->bodyShape;
		fixDef->density = density;
		fixDef->friction = friction;
		body->CreateFixture(fixDef);
	}
	else
	{
		body->CreateFixture(this->bodyShape, 0);
	}
}

void Entity::Update(float frameTime)
{
	PostUpdate(frameTime);

	if (sprite.getPosition().x > Constants::WND_WIDTH || sprite.getPosition().x < 0 || sprite.getPosition().y > Constants::WND_HEIGHT || sprite.getPosition().y < -100)
	{
		//Saiu da view ()
		active = false;
	}

	sprite.setPosition(body->GetPosition().x * 30.f, body->GetPosition().y * 30.f);
	sprite.setRotation(180 / b2_pi * body->GetAngle());
}

void Entity::PostUpdate(float frametime)
{
}


void Entity::Draw(sf::RenderWindow & wnd)
{
	wnd.draw(sprite);
}

void Entity::HandleEvents(sf::Event & event)
{
}

void Entity::Load(const std::string & name)
{
	if (!texture->loadFromFile(name)) return;
	texture->setRepeated(false);
	sprite.setTexture(*texture);
}

