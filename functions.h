//
// Created by shibl on 1/13/2025.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Entity.h"
#include "EntityNode.h"
#include "Location.h"
#define STAY_STILL 0
#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4

void checkKeys();
void checkCollisions();
void checkBotAI();
int convertXPosToGrid(Location* pos);
int convertYPosToGrid(Location* pos);
EntityNode* findEntityNode(Entity e);
void upkeepEntitiesOnVisibleGrid();

#endif //FUNCTIONS_H
