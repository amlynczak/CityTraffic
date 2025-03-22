//
// Created by adamm on 25-03-06.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>
#include "Entity.h"

class EntityManager {
private:
    std::vector<std::shared_ptr<Entity>> entities;

public:
    void addEntity(std::shared_ptr<Entity> entity);
    void updateAll(float deltaTime);
};

#endif //ENTITYMANAGER_H
