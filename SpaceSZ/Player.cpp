#include "Player.h"
#include "Game.h"
#include "GameFactory.h"

Player::Player(b2World* world, sf::Vector2f pos)
	: Entity(world, true, pos)
{
	Load("Assets/textures/space_ship.png");

	shape = new b2PolygonShape();
	shape->SetAsBox((sprite.getTexture()->getSize().x / 2) / 30.f, (sprite.getTexture()->getSize().y / 2) / 30.f);
	density = 100.f;
	friction = 1.5f;
	Initialize(shape, pos, true);
}


Player::~Player()
{
	delete shape;
}

void Player::PostUpdate(float frametime)
{
	b2Vec2 vel = body->GetLinearVelocity();
	sf::Vector2f mousePos = Game::window.mapPixelToCoords(sf::Mouse::getPosition(Game::window));
	b2Vec2 target = b2Vec2(mousePos.x, mousePos.y) - body->GetPosition();
	float angle = atan2f(target.x, target.y);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//Move left
		vel.x = b2Max(vel.x - 0.1f, -3.0f + angle);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//Move right
		vel.x = b2Min(vel.x + 0.1f, 3.0f + angle);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		vel.y = b2Max(vel.y - 0.1f, -3.0f + angle);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		vel.y = b2Min(vel.y + 0.1f, 3.0f + angle);
	}

	if (sprite.getPosition().y > Constants::WND_HEIGHT || sprite.getPosition().x > Constants::WND_WIDTH || sprite.getPosition().x < 0)
	{
		//Game Over!
		active = false;
	}

	body->SetLinearVelocity(vel);
	body->SetTransform(body->GetPosition(), angle);
}

void Player::Draw(sf::RenderWindow & wnd)
{
	Entity::Draw(wnd);
}
