#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include "Components/Component.h"
#include <vector>
#include <iostream>

class EntityManager
{
public:
	void ClearData();
	void Update(float deltaTime);
	void Render();
	bool HasNoEntities();
	void ListAllEntites() const;
	Entity& AddEntity(std::string entityName);
	std::vector<Entity*> GetEntities() const;
	unsigned int GetEntityCount();

private:
	std::vector<Entity*> entities;

};

#endif
