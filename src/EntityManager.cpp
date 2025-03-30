#include"EntityManager.h"
#include<iostream>

void EntityManager::addEntity(std::shared_ptr<Entity> entity) {
	_entities.push_back(entity);
}

void EntityManager::removeEntity(int id) {
	for (auto it = _entities.begin(); it != _entities.end(); ++it) {
		if ((*it)->getId() == id) {
			_entities.erase(it);
			break;
		}
	}
}

void EntityManager::clearAll() {
	_entities.clear();
}

void EntityManager::updateAll(float deltaTime, const Map& map) {
	for (auto& entity : _entities) {
		entity->update(deltaTime, map);
	}
}