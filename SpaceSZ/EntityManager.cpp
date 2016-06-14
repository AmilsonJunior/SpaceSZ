#include "EntityManager.h"
#include "GameFactory.h"
#include <stdlib.h>
#include <algorithm>

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
	/*for (auto& x : _objects)
		delete x.second;
	_objects.clear();*/
}

void EntityManager::AddGameObject(const std::string & _name, Entity * _obj)
{
	if (_objects.find(_name) != _objects.end())
	{
		std::cout << "Cannot register game object: " << _name <<  "\n";
		return;
	}
	_objects.insert(std::make_pair(_name, _obj));
	gameObjectCount++;
}

void EntityManager::DeleteGameObject(const std::string & _name)
{
	std::map<std::string, Entity*>::const_iterator result = _objects.find(_name);
	if (result != _objects.end())
	{
		delete &result->second;
		_objects.erase(result);
	}
}

Entity * EntityManager::GetGameObject(const std::string & _name) const
{
	std::map<std::string, Entity*>::const_iterator result = _objects.find(_name);
	if (result != _objects.end())
	{
		return result->second;
	}

	return nullptr;
}

void EntityManager::UpdateAll(float time)
{
	for (auto& x : _objects)
	{
		if (!x.second->isActive())
		{
			trash.push_back(x.first);
		}

		else
		{
			x.second->Update(time);
		}
			
	}

	for (auto& x : trash)
	{
		DeleteGameObject(x);
	}

	trash.clear();
}

void EntityManager::RenderAll(sf::RenderWindow& wnd)
{
	std::map<std::string, Entity*>::iterator it = _objects.begin();

	while (it != _objects.end())
	{
		it->second->Draw(wnd);
		it++;
	}
}

void EntityManager::DeleteAll()
{
	if (!_objects.empty())
	{
		std::map<std::string, Entity*>::iterator it = _objects.begin();

		while (it != _objects.end())
		{
			it->second = NULL;
			delete it->second;
			it++;
		}

		_objects.clear();
	}

}
