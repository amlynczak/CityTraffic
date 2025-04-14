#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>
#include "Entity.h"

class EntityManager {
private:
    std::vector<std::shared_ptr<Entity>> _entities;

public:
    void addEntity(std::shared_ptr<Entity> entity);
	void removeEntity(int id);
    void clearAll();
    void updateAll(float deltaTime, const Map& map);

	std::vector<std::shared_ptr<Entity>>& getEntities() { return _entities; }
	//std::shared_ptr<Entity> getEntityById(int id);
	//std::shared_ptr<Entity> getEntityAt(float x, float y);
	//std::vector<std::shared_ptr<Entity>> getEntitiesInRange(float x, float y, float range);
};

#endif //ENTITYMANAGER_H
