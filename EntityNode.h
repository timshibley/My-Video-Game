//
// Created by shibl on 1/15/2025.
//

#ifndef ENTITYNODE_H
#define ENTITYNODE_H
#include "Entity.h"

//class Entity;

class EntityNode {
public:
    Entity* entry;
    EntityNode* next;
    EntityNode* prev;
    EntityNode* newID;
    EntityNode* prevID;
    int level;
    EntityNode();
    EntityNode(Entity* e);
    EntityNode(float x, float y, float width, float height, int i, int v, Color c, Texture2D t, int k, int xGrid, int yGrid);
};



#endif //ENTITYNODE_H
