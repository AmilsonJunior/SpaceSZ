#include "Game.h"
#include "GameFactory.h"
#include "DisplayInfo.h"

Game::Game()
	: gravity(0, 0.0f)
{
	sf::ContextSettings cxt;
	cxt.antialiasingLevel = 8;
	
	window.create(sf::VideoMode(Constants::WND_WIDTH, Constants::WND_HEIGHT), "SpaceSZ", sf::Style::Default, cxt);
	window.setFramerateLimit(60);
	
	GameWorld = new b2World(gravity);
	
	textureManager = std::make_shared<TextureManager>();
	entityManager = std::make_shared<EntityManager>();
	window.setMouseCursorVisible(false);

	gameState = GameState::PLAYING;
	collision = false;
	CreateGameObjects();
}


Game::~Game()
{
	
}

void Game::Run()
{
	DisplayInfo::Init();

	threadSpawnMeteor.launch();

	while (window.isOpen())
	{
		HandleEvents();
		Update();
		Render();
	}

	threadSpawnMeteor.terminate();
}

void Game::GameOver()
{
	window.draw(gameOver);
}


void Game::Render()
{
	window.clear(sf::Color::Black);

	if (gameState == GameState::PLAYING)
	{
		entityManager->RenderAll(window);
	}
	else if (gameState == GameState::GAMEOVER)
	{
		GameOver();
	}

	DisplayInfo::ShowScore(window);

	window.display();
}

void Game::Update()
{
	if (gameState == GameState::PLAYING)
	{
		mutex.lock();
		GameWorld->Step(1 / 60.f, 8, 3);
		mutex.unlock();
		GameLoop();
		entityManager->UpdateAll(clock.restart().asMilliseconds());
		entityManager->RulesCollision();
	}
}

void Game::HandleEvents()
{
	while (window.pollEvent(Event))
	{
		Events();

		if (Event.type == sf::Event::Closed)
		{
			gameState = GameState::CLOSED;
			window.close();
		}

		if (gameState == GameState::GAMEOVER)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				Init();
			}
		}
	}
}

std::shared_ptr<EntityManager> Game::entityManager;
std::shared_ptr<TextureManager> Game::textureManager;
sf::RenderWindow Game::window;
sf::Event Game::Event;
sf::Clock Game::clock;
bool Game::collision;
Game::GameState Game::gameState;
b2World* Game::GameWorld;