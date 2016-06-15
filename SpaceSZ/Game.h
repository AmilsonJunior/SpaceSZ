#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <thread>
#include <mutex>

#include "TextureManager.h"
#include "EntityManager.h"
#include "EngineConstants.h"
#include "Meteor.h"

class Game
{
public:
	Game();
	~Game();

	void Run();

	static std::shared_ptr<EntityManager> entityManager;
	static std::shared_ptr<TextureManager> textureManager;
	static sf::Event Event;
	static sf::RenderWindow window;
	static sf::Clock clock;
	static bool collision;

	void MainMenu();
	void GameOver();
	void PauseMenu();
	static void AddPointScore();
	static b2World* GameWorld;
	
	enum class GameState
	{
		LOADING,
		PLAYING,
		ONSTART,
		PAUSED,
		CLOSED,
		GAMEOVER
	};

	static GameState gameState;

private:
	void Render();
	void Update();
	void HandleEvents();

	b2Vec2 gravity;

};

