#include "TextureManager.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

void TextureManager::LoadAllTextures()
{
	for (int i = 0; i < files.size(); i++)
	{
		sf::Texture* tmp = new sf::Texture();
		tmp->loadFromFile(files[i]);
		pTextures.insert(std::make_pair(files[i], tmp));
	}
}

sf::Texture* TextureManager::Get(const std::string & name) const
{
	std::map<std::string, sf::Texture*>::const_iterator it = pTextures.find(name);

	if (it != pTextures.end())
	{
		return it->second;
	}

	return NULL;
}

void TextureManager::Remove(const std::string & name)
{
}

void TextureManager::AddResource(const std::string & fileName)
{
	files.push_back(fileName);
}
