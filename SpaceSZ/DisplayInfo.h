#pragma once

#include "EngineConstants.h"
#include "Game.h"

namespace DisplayInfo
{
	sf::Text textObj, textureCounter, fpsText;
	sf::Font font;

	void Init()
	{
		if (!font.loadFromFile("Assets/fonts/DejaVuSansCondensed.ttf"))
		{
			return;
		}

		textObj.setFont(font);
		textObj.setCharacterSize(20);
		textObj.setColor(sf::Color::White);
		textObj.setPosition(sf::Vector2f(10, 10));

		textureCounter.setFont(font);
		textureCounter.setCharacterSize(20);
		textureCounter.setColor(sf::Color::White);
		textureCounter.setPosition(sf::Vector2f(10, 30));

		fpsText.setFont(font);
		fpsText.setCharacterSize(20);
		fpsText.setColor(sf::Color::Yellow);
		fpsText.setPosition(sf::Vector2f(10, 60));
	}

	void ShowObjectCounter(sf::RenderWindow& wnd)
	{
		textObj.setString("Objects: " + std::to_string(Game::entityManager->Count()));
		wnd.draw(textObj);
		textureCounter.setString("Textures loaded: " + std::to_string(Game::textureManager->Count()));
		wnd.draw(textureCounter);
	}

	void ShowFPS(sf::RenderWindow& wnd, sf::Clock& clock)
	{
		fpsText.setString("FPS: " + std::to_string(clock.restart().asMilliseconds()));
		wnd.draw(fpsText);
	}
}