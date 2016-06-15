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
	typeName = "Player";

	Initialize(shape, pos, true);
}


Player::~Player()
{
	delete shape;
}

void Player::PostUpdate(float frametime)
{
	b2Vec2 vel = body->GetLinearVelocity();
	sf::Vector2f* mousePos = &Game::window.mapPixelToCoords(sf::Mouse::getPosition());
	float angle = atan2(mousePos->y - sprite.getPosition().y, mousePos->x - sprite.getPosition().x);
	angle = angle * 180 / b2_pi;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//Move left
		vel.x = b2Max(vel.x - 0.1f, -5.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//Move right
		vel.x = b2Min(vel.x + 0.1f, 5.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		vel.y = b2Max(vel.y - 0.1f, -5.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		vel.y = b2Min(vel.y + 0.1f, 3.0f);
	}

	if (sprite.getPosition().y > Constants::WND_HEIGHT || sprite.getPosition().y < 0 ||
		sprite.getPosition().x > Constants::WND_WIDTH || sprite.getPosition().x < 0)
	{
		//Game Over!
		active = false;
		Game::gameState = Game::GameState::GAMEOVER;
	}

	body->SetLinearVelocity(vel);
	//body->SetTransform(body->GetPosition(), angle);
	//sprite.setRotation(180/b2_pi * body->GetAngle());
}

void Player::Draw(sf::RenderWindow & wnd)
{
	Entity::Draw(wnd);
}
