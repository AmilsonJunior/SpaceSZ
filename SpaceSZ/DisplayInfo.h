#pragma once

#include "EngineConstants.h"
#include "Game.h"

namespace DisplayInfo
{
	sf::Text score;
	sf::Font font;

	void Init()
	{
		if (!font.loadFromFile("Assets/fonts/DejaVuSansCondensed.ttf"))
		{
			return;
		}

		score.setFont(font);
		score.setCharacterSize(20);
		score.setColor(sf::Color::White);
		score.setPosition(sf::Vector2f(10, 10));
	}

	void ShowScore(sf::RenderWindow& wnd)
	{
		score.setString("Score: " + std::to_string(Game::entityManager->Collisions()));
		wnd.draw(score);
	}
}