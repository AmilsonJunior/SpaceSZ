#include "Game.h"
#include "GameFactory.h"
#include "DisplayInfo.h"

Game::Game()
	: gravity(0, 0.0f)
{
	sf::ContextSettings cxt;
	cxt.antialiasingLevel = 8;
	
	window.create(sf::VideoMode(Constants::WND_WIDTH, Constants::WND_HEIGHT), "Box2D and SFML", sf::Style::Default, cxt);
	window.setFramerateLimit(90);
	
	GameWorld = new b2World(gravity);
	
	textureManager = std::make_shared<TextureManager>();
	entityManager = std::make_shared<EntityManager>();
	window.setMouseCursorVisible(false);

	gameState = GameState::PLAYING;

	CreateGameObjects();
}


Game::~Game()
{
	//threadMeteor.detach();
	delete GameWorld;
}

void Game::Run()
{
	threadMeteor = new std::thread(MeteorFuncThread);

	DisplayInfo::Init();

	while (window.isOpen())
	{
		HandleEvents();
		Update();
		Render();
	}
}

void Game::MainMenu()
{
	std::cout << "Showing main menu\n";
}

void Game::GameOver()
{
	window.draw(gameOver);
}

void Game::PauseMenu()
{
	std::cout << "Showing pause menu\n";
}

void Game::Render()
{
	window.clear(sf::Color::Black);

	if (gameState == GameState::ONSTART)
	{
		// Show the main menu
		MainMenu();
	}
	else if (gameState == GameState::PAUSED)
	{
		PauseMenu();
	}
	else if (gameState == GameState::PLAYING)
	{
		entityManager->RenderAll(window);
	}
	else if (gameState == GameState::GAMEOVER)
	{
		// Show a message
		GameOver();
	}

	DisplayInfo::ShowObjectCounter(window);
	DisplayInfo::ShowFPS(window, clock);

	window.display();
}

void Game::Update()
{
	if (gameState == GameState::PLAYING)
	{
		mu.lock();
		GameWorld->Step(1 / 60.f, 8, 3);
		mu.unlock();

		GameLoop();
		entityManager->UpdateAll(clock.restart().asMilliseconds());
	}
}

void Game::HandleEvents()
{
	//Global events
	sf::Event ev;
	while (window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
		{
			gameState = GameState::CLOSED;
			window.close();
		}

		if (gameState == GameState::GAMEOVER)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				Init();

			}
		}
	}
}

std::shared_ptr<EntityManager> Game::entityManager;
std::shared_ptr<TextureManager> Game::textureManager;
sf::RenderWindow Game::window;
Game::GameState Game::gameState;
b2World* Game::GameWorld;