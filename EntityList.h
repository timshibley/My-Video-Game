//
// Created by shibl on 1/15/2025.
//

#ifndef ENTITYLIST_H
#define ENTITYLIST_H
#include "EntityNode.h"


class EntityList {
public:
    EntityNode* head;
   // EntityList* nextID;
    int length;
    EntityList();
    EntityList(EntityNode* e);
    //void deleteAtHead();
    void insertNewEntity(Entity* e);
    void insertNewEntity(float x, float y, float width, float height, int i, int v, Color c, Texture2D t, int k, int xGrid, int yGrid);
    int lengthOfID(int i);
    void deleteNthID(int chosenID, int n);
    void deleteEntity(Entity* e);
    EntityNode* findLastNode();
    Entity* findAtUltimateXY(int x, int y);
    Entity* findAtVisibleXY(int x, int y);
    EntityNode* findNthEntry(int chosenID, int n);
    EntityNode* findIDTree(int id);
    void deleteAllNodes();
};



#endif //ENTITYLIST_H
