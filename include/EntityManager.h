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
    void updateAll(float deltaTime);
};

#endif //ENTITYMANAGER_H
