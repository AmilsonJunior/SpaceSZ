#pragma once
#include <iostream>
#include <map>
#include <string>
#include <SFML\Graphics.hpp>
#include <Windows.h>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void LoadAllTextures();
	sf::Texture* Get(const std::string& name) const;
	void Remove(const std::string& name);
	void AddResource(const std::string& fileName);
	int Count() const { return pTextures.size(); }
private:
	std::vector<std::string> files;
	std::map<std::string, sf::Texture*> pTextures;
};

