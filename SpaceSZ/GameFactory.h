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
#include "Meteor.h"


namespace
{
	void CreateMeteor(float x, float y);
	void CreateGameObjects();
	void CreatePlayer();
	void GameLoop();
	void MeteorFuncThread();
	void Init();

	std::string GenerateRandomID();

	int gameObjectCount = 1;

	std::vector<Entity*> meteorsList;
	std::thread* threadMeteor;
	std::mutex mu;

	sf::Sprite gameOver;

	//Create all game objects
	void CreateGameObjects()
	{
		Game::textureManager->AddResource("Assets/textures/meteor1.png");
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
			Game::entityManager->DeleteAll();
		}

		CreatePlayer();
	}

	void MeteorFuncThread()
	{
		while (true)
		{
			Sleep(100);

			if (Game::gameState == Game::GameState::PLAYING)
			{
				mu.lock();
				Meteor* box = new Meteor(Game::GameWorld, sf::Vector2f(rand() % Constants::WND_WIDTH, -(rand() % 20)), true);
				meteorsList.push_back(box);
				mu.unlock();

				std::cout << "opaaaaa" << meteorsList.size() << std::endl;
			}
			else
			{
				mu.lock();
				for (auto& x : meteorsList)
				{
					x = NULL;
					delete x;
					//meteorsList.erase(std::remove(meteorsList.begin(), meteorsList.end(), x));
				}

				meteorsList.clear();
				mu.unlock();
			}
		}
	}

	void GameLoop()
	{
		mu.lock();
		if (!meteorsList.empty())
		{
			Game::entityManager->AddGameObject("meteor" + GenerateRandomID(), meteorsList[meteorsList.size() - 1]);
			meteorsList.pop_back();
		}
		mu.unlock();
	}
	

	void CreateMeteor(float x, float y)
	{
		Meteor* meteor = new Meteor(Game::GameWorld, sf::Vector2f(x, y), true);
		Game::entityManager->AddGameObject("meteor" + GenerateRandomID(), meteor);
	}
	
	void CreatePlayer()
	{
		mu.lock();
		Player* player = new Player(Game::GameWorld, sf::Vector2f(400, 500));
		mu.unlock();
		Game::entityManager->AddGameObject("Player", player);
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