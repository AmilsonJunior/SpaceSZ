#pragma once
#include <iostream>
#include <string>
#include <map>
#include <thread>
#include "Entity.h"
#include "Game.h"
#include "TextureManager.h"
#include "GroundExample.h"
#include "Player.h"

namespace
{
	void RegisterGameObject(const std::string& _name, Entity* obj);
	void CreateBox(float x, float y);
	void CreateGameObjects();
	void CreatePlayer();
	void GameLoop();
	void CreateMeteor();
	void Init();

	std::string GenerateRandomID();

	int gameObjectCount = 1;

	std::vector<Entity*> meteorsList;
	std::thread* threadMeteor;
	std::mutex mu;

	sf::Sprite gameOver;

	//Register a game object
	void RegisterGameObject(const std::string& _name, Entity* obj)
	{
		Game::entityManager->AddGameObject(_name, obj);
	}

	//Create all game objects
	void CreateGameObjects()
	{
		Game::textureManager->AddResource("Assets/textures/box.png");
		Game::textureManager->AddResource("Assets/textures/space_ship.png");
		Game::textureManager->AddResource("Assets/textures/bullet.png");
		Game::textureManager->AddResource("Assets/textures/ground.png");
		Game::textureManager->AddResource("Assets/textures/default_text.png");
		Game::textureManager->AddResource("Assets/textures/gameover.png");
		Game::textureManager->LoadAllTextures();

		Init();

		gameOver.setTexture(*Game::textureManager->Get("Assets/textures/gameover.png"));
		gameOver.setOrigin(gameOver.getGlobalBounds().width / 2, gameOver.getGlobalBounds().height / 2);
		gameOver.setPosition(sf::Vector2f(Constants::WND_WIDTH / 2, Constants::WND_HEIGHT / 2));
	}

	void Init()
	{
		Game::gameState = Game::GameState::PLAYING;

		if (Game::entityManager->Count() != 0)
		{
			Game::entityManager->DeleteGameObject("Player");
		}

		CreatePlayer();
	}

	void CreateMeteor()
	{
		while (true)
		{
			Sleep(100);
			mu.lock();
			SimpleBox* box = new SimpleBox(Game::GameWorld, sf::Vector2f(rand() % Constants::WND_WIDTH, -(rand() % 20)), true);
			meteorsList.push_back(box);
			mu.unlock();
		}
	}

	void GameLoop()
	{
		mu.lock();
		if (!meteorsList.empty())
		{
			RegisterGameObject("meteor" + GenerateRandomID(), meteorsList[meteorsList.size() - 1]);
		}
		mu.unlock();
	}

	void CreateBox(float x, float y)
	{
		SimpleBox* box = new SimpleBox(Game::GameWorld, sf::Vector2f(x, y), true);
		RegisterGameObject("box" + GenerateRandomID(), box);
	}
	
	void CreatePlayer()
	{
		mu.lock();
		Player* player = new Player(Game::GameWorld, sf::Vector2f(400, 500));
		mu.unlock();
		RegisterGameObject("Player", player);
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