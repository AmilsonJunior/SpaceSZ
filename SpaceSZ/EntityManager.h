#pragma once
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <memory>

#include "Entity.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void AddGameObject(const std::string& _name, std::shared_ptr<Entity> _obj);
	void DeleteGameObject(const std::string& _name);
	std::shared_ptr<Entity> GetGameObject(const std::string& _name) const;
	int Count() const { return _objects.size(); }
	void RulesCollision();
	void UpdateAll(float time);
	void RenderAll(sf::RenderWindow& wnd);
	void DeleteAll();

private:
	std::map<std::string, std::shared_ptr<Entity>> _objects;
	std::vector<std::string> trash;
};

