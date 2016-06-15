#include "EntityManager.h"
#include "GameFactory.h"
#include "Bullet.h"
#include "Meteor.h"
#include "Score.h"
#include <stdlib.h>
#include <algorithm>


EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

void EntityManager::AddGameObject(const std::string & _name, std::shared_ptr<Entity> _obj)
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
	std::map<std::string, std::shared_ptr<Entity>>::iterator result = _objects.find(_name);
	if (result != _objects.end())
	{
		result->second = nullptr;
		_objects.erase(result);
	}
}

std::shared_ptr<Entity> EntityManager::GetGameObject(const std::string & _name) const
{
	std::map<std::string, std::shared_ptr<Entity>>::const_iterator result = _objects.find(_name);
	if (result != _objects.end())
	{
		return result->second;
	}

	return nullptr;
}

void EntityManager::RulesCollision()
{
	for (auto& x : _objects)
	{
		auto obj1 = x;

		for (auto& y : _objects)
		{
			auto obj2 = y;

			if (obj1.second->getGlobalBounds().intersects(obj2.second->getGlobalBounds()))
			{
				if ((obj1.second->typeName == "Player" && obj2.second->typeName == "Bullet")
					|| (obj1.second->typeName == "Bullet" && obj2.second->typeName == "Player")
					|| (obj1.second->typeName == "Meteor" && obj2.second->typeName == "Player")
					|| (obj1.second->typeName == "Player" && obj2.second->typeName == "Meteor")
					|| (obj1.second->typeName == obj2.second->typeName))
					continue;

				Game::AddPointScore();

				obj1.second->disable();
				obj2.second->disable();
			}
		}
	}
}

void EntityManager::UpdateAll(float time)
{
	std::map<std::string, std::shared_ptr<Entity>>::iterator it = _objects.begin();

	while (it != _objects.end())
	{
		if (it->second->isActive())
		{
			it->second->Update(time);
		}
		else
		{
			trash.push_back(it->first);
		}

		it++;;
	}

	for (auto& x : trash)
	{
		DeleteGameObject(x);
	}

	trash.clear();
}

void EntityManager::RenderAll(sf::RenderWindow& wnd)
{
	std::map<std::string, std::shared_ptr<Entity>>::iterator it = _objects.begin();

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
		std::map<std::string, std::shared_ptr<Entity>>::iterator it = _objects.begin();

		while (it != _objects.end())
		{
			it->second = nullptr;
			it++;
		}

		_objects.clear();
	}

}
