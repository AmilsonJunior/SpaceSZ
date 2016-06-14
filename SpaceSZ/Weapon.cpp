#include "Weapon.h"
#include "GameFactory.h"


Projectile::Projectile(b2World* world, bool dynamic, sf::Vector2f pos, sf::Vector2f mousePos)
	: Entity(world, dynamic, pos)
	, mousePos(mousePos)
{
	Load("Assets/textures/bullet.png");

	shape = new b2PolygonShape();
	shape->SetAsBox((sprite.getTexture()->getSize().x / 2) / 30.f, (sprite.getTexture()->getSize().y / 2) / 30.f);
	fired = false;
	Initialize(shape, pos, dynamic);
}


Projectile::~Projectile()
{
	delete shape;
}

void Projectile::PostUpdate(float frametime)
{
	if (fired)
	{
		Player* p = dynamic_cast<Player*>(Game::entityManager->GetGameObject("Player"));

		float angleShot = p->GetAngleShot();
		std::cout << angleShot << "\n";
		body->SetAngularVelocity(cos(angleShot) * 1.0f);
	}

}

void Projectile::Draw(sf::RenderWindow & wnd)
{
	Entity::Draw(wnd);
}
