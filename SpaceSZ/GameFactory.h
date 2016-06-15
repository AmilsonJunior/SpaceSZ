#ifndef GAMEFACTORY_HEADER
#define GAMEFACTORY_HEADER

#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <list>

#include "Entity.h"
#include "Game.h"
#include "TextureManager.h"
#include "GroundExample.h"
#include "Player.h"
#include "Meteor.h"
#include "Bullet.h"
#include "Score.h"

namespace
{
	//Declaração
	std::shared_ptr<Meteor> CreateMeteor(float x, float y);
	std::shared_ptr<Player> CreatePlayer();
	std::shared_ptr<Bullet> CreateBullet(float x, float y);
	std::string GenerateRandomID();

	void CreateGameObjects();
	void GameLoop();
	void Events();
	void Init();
	void SpawnMeteors();

	int gameObjectCount = 1;

	bool collision = false;

	std::vector<std::shared_ptr<Meteor>> meteorsList;
	std::vector<std::shared_ptr<Bullet>> bulletsList;

	sf::Thread threadSpawnMeteor(&SpawnMeteors);
	sf::Mutex mutex;
	sf::Sprite gameOver;

	//Implementação
	void CreateGameObjects()
	{
		Game::textureManager->AddResource("Assets/textures/meteor1.png");
		Game::textureManager->AddResource("Assets/textures/space_ship.png");
		Game::textureManager->AddResource("Assets/textures/bullet.png");
		Game::textureManager->AddResource("Assets/textures/ground.png");
		Game::textureManager->AddResource("Assets/textures/default_text.png");
		Game::textureManager->AddResource("Assets/textures/gameover.png");
		Game::textureManager->LoadAllTextures();

		gameOver.setTexture(*Game::textureManager->Get("Assets/textures/gameover.png"));
		gameOver.setOrigin(gameOver.getGlobalBounds().width / 2, gameOver.getGlobalBounds().height / 2);
		gameOver.setPosition(sf::Vector2f(Constants::WND_WIDTH / 2, Constants::WND_HEIGHT / 2));

		Init();
	}

	void Init()
	{
		if (Game::entityManager->Count() != 0)
		{
			Game::entityManager->DeleteGameObject("Player");
			Game::entityManager->DeleteAll();
		}

		mutex.lock();
		Game::entityManager->AddGameObject("Player", CreatePlayer());
		mutex.unlock();

		Game::gameState = Game::GameState::PLAYING;
	}

	void SpawnMeteors()
	{
		while (true)
		{
			sf::sleep(sf::milliseconds(250));
			mutex.lock();
			meteorsList.push_back(CreateMeteor(rand() % Constants::WND_WIDTH, -(rand() % 20)));
			mutex.unlock();
		}
	}

	void Fire()
	{
		auto playerPos = Game::entityManager->GetGameObject("Player")->GetPosition();
		Game::entityManager->AddGameObject("bullet" + GenerateRandomID(), CreateBullet(playerPos.x, playerPos.y - 50));
	}

	void Events()
	{
		Game::window.setKeyRepeatEnabled(false);
		if (sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				Fire();
			}
		}
	}

	void GameLoop()
	{
		mutex.lock();
		if (!meteorsList.empty())
		{
			Game::entityManager->AddGameObject("Meteor" + GenerateRandomID(), meteorsList.back());
			meteorsList.back() = nullptr;
			meteorsList.erase(std::remove(meteorsList.begin(), meteorsList.end(), meteorsList.back()));
		}
		mutex.unlock();	
	}

	std::shared_ptr<Bullet> CreateBullet(float x, float y)
	{
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(Game::GameWorld, true, sf::Vector2f(x, y));
		return bullet;
	}
	std::shared_ptr<Meteor> CreateMeteor(float x, float y)
	{
		std::shared_ptr<Meteor> meteor = std::make_shared<Meteor>(Game::GameWorld, sf::Vector2f(x, y), true);
		return meteor;
	}
	std::shared_ptr<Player> CreatePlayer()
	{
		std::shared_ptr<Player> player = std::make_shared<Player>(Game::GameWorld, sf::Vector2f(400, 500));
		return player;
	}
	std::string GenerateRandomID()
	{
		auto randchar = []() -> char
		{
			const char charset[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			const size_t max_index = (sizeof(charset) - 1);
			return charset[rand() % max_index];
		};

		std::string str(100, 0);
		std::generate_n(str.begin(), 100, randchar);

		return str;
	}
}

#endif