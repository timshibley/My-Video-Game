// This is my base class for all entities.
// Many of the classes in this program are subclasses of the Entity class.
// Created by shibl on 1/15/2025.
//

#include "Entity.h"

#include <stdio.h>

#include "Enemy.h"
#include "Macros.h"
#include "main.h"


//This is never used, but I have it written just in case I eventually want to use it.
Entity::Entity() {
    id = 0;
    rectangle = {0, 0, 0, 0};
}

//This is the constructor I use throughout the program. I could definitely see myself creating more as I have more unique use cases.
Entity::Entity(float x, float y, float width, float height, int i, int v, Color c, Texture2D t, int k, int xGrid, int yGrid) {
    id = i;
    color = c;
    visible = true;
    rectangle = {x, y, width, height};
    texture = t;
    textureTracker = k;
    xGridCord = xGrid;
    yGridCord = yGrid;
}

//I may change a lot of these private variables into public variables, because the readability of the code is decreased due to the setters and getters.

int Entity::getXGridCoordinate() {
    return xGridCord;
}

int Entity::getYGridCoordinate() {
    return yGridCord;
}

void Entity::setXGridCoordinate(int xGrid) {
    xGridCord = xGrid;
}

void Entity::setYGridCoordinate(int yGrid) {
    yGridCord = yGrid;
}

Rectangle* Entity::getRectangle() {
    return &rectangle;
}

int Entity::getId() {
    return id;
}

Vector2 Entity::getPosition() {
    return {rectangle.x, rectangle.y};
}

Vector2 Entity::getSize() {
    return {rectangle.width, rectangle.height};
}

bool Entity::isVisible() {
    return visible;
}

Color Entity::getColor() {
    return color;
}

void Entity::setId(int id_temp) {
    id = id_temp;
}

void Entity::setRectangle(Rectangle r) {
    rectangle = r;
}

void Entity::setVisibility(bool v) {
    visible = v;
}

void Entity::setXCoordinate(float xPos) {
    rectangle.x = xPos;
}

void Entity::setYCoordinate(float yPos) {
    rectangle.y = yPos;
}

Texture2D Entity::getTexture() {
    return texture;
}

void Entity::setTexture(Texture2D t) {
    texture = t;
}


void Entity::setColor(Color c) {
    color = c;
}

int Entity::getXVisibleCoordinate() {
    return xVisibleCord;
}

int Entity::getYVisibleCoordinate() {
    return yVisibleCord;
}




//This function checks if there is a tile in the direction specified by the variable.
//The purpose of the function is to prevent an Entity from taking an action that would result in a memory error
bool Entity::isTileAdjacent(int direction) {
    bool decision = false;
    switch (direction) {
        case RIGHT:
            if (xGridCord < gridMap[0].size() -1) {
                decision =  true;
            }
        break;
        case LEFT:
            if (xGridCord > 0) {
                decision = true;
            }
        break;
        case UP:
            if (yGridCord > 0) {
                decision = true;
            }
        break;
        case DOWN:
            if (yGridCord < gridMap.size() - 1) {
                decision = true;
            }
        break;
        default:
            break;
    }
    return decision;
}


//Will return true if there is a wall. This is important for combat to not attack the walls.
//Eventually this could allow for entities to attack many different types of ids with priorities on certain ids
//This actually checks if there is an entity in a specific tile.
bool Entity::isTileOccupied(int direction, int chosenID) {
    bool decision = false;
    if (isTileAdjacent(direction)) {
        //This is the case if I am looking for a specific ID
        if (chosenID != DONT_CARE_ID) {
                switch (direction) {
                    case UP:
                        if (gridMap[yGridCord-1][xGridCord]->entity != nullptr && gridMap[yGridCord-1][xGridCord]->entity->getId() == chosenID) {
                            decision = true;
                        }
                        break;
                    case DOWN:
                        if (gridMap[yGridCord+1][xGridCord]->entity != nullptr && gridMap[yGridCord+1][xGridCord]->entity->getId() == chosenID) {
                            decision = true;
                        }
                        break;
                    case RIGHT:
                        if (gridMap[yGridCord][xGridCord+1]->entity != nullptr && gridMap[yGridCord][xGridCord+1]->entity->getId() == chosenID) {
                            decision = true;
                        }
                        break;
                    case LEFT:
                        if (gridMap[yGridCord][xGridCord-1]->entity != nullptr && gridMap[yGridCord][xGridCord-1]->entity->getId() == chosenID) {
                            decision = true;
                        }
                        break;
                    default:
                        break;
                }
        }

        //This is the case if I am checking if a certain tile is empty.
        else {
            switch (direction) {
                case UP:
                    if (gridMap[yGridCord-1][xGridCord]->entity != nullptr) {
                        decision = true;
                    }
                    break;
                case DOWN:
                    if (gridMap[yGridCord+1][xGridCord]->entity != nullptr) {
                        decision = true;
                    }
                    break;
                case RIGHT:
                    if (gridMap[yGridCord][xGridCord+1]->entity != nullptr) {
                        decision = true;
                    }
                    break;
                case LEFT:
                    if (gridMap[yGridCord][xGridCord-1]->entity != nullptr) {
                        decision = true;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    else {
        decision = true;
    }

    return decision;
}


//This returns a pointer to an entity at the chosen tile.
Entity* Entity::adjacentEntity(int direction) {
    Entity* pointer = nullptr;
    if (isTileAdjacent(direction)) {
        if (isTileOccupied(direction, DONT_CARE_ID)) {
            switch (direction) {
                case UP:
                    pointer = gridMap[yGridCord-1][xGridCord]->entity;
                    break;
                case DOWN:
                    pointer = gridMap[yGridCord+1][xGridCord]->entity;
                    break;
                case RIGHT:
                    pointer = gridMap[yGridCord][xGridCord+1]->entity;
                    break;
                case LEFT:
                    pointer = gridMap[yGridCord][xGridCord-1]->entity;
                    break;
                default:
                    break;
            }
        }
    }
    return pointer;
}


//This returns the pointer of an adjacent enemy.
//To do: rework this to be more general and allow the function to accept an ID to allow for more use cases.
Enemy* Entity::adjacentEnemy(int direction) {
    if (isTileOccupied(direction, MONSTER_ID)) {
        switch (direction) {
            case UP: {
                Entity* e = gridMap[yGridCord-1][xGridCord]->entity;
                return dynamic_cast<Enemy*> (e);
            }
            case DOWN: {
                Entity* e = gridMap[yGridCord+1][xGridCord]->entity;
                return dynamic_cast<Enemy*> (e);
            }
            case RIGHT: {
                Entity* e = gridMap[yGridCord][xGridCord+1]->entity;
                return dynamic_cast<Enemy*> (e);
            }
            case LEFT: {
                Entity* e = gridMap[yGridCord][xGridCord-1]->entity;
                return dynamic_cast<Enemy*> (e);
            }
            default: break;
        }
    }
    return nullptr;
}

//This moves the entity in a chosen direction.
//I may want to incorporate the checking to make sure there is a tile in that direction in this function.
void Entity::moveInDirection(int dir) {
    switch (dir) {
        case UP:
            gridMap[yGridCord][xGridCord]->entity = nullptr; //Makes sure to move the entity.
            yGridCord--;
            gridMap[yGridCord][xGridCord]->entity = this;
            break;
        case DOWN:
            gridMap[yGridCord][xGridCord]->entity = nullptr;
            yGridCord++;
            gridMap[yGridCord][xGridCord]->entity = this;
            break;
        case RIGHT:
            gridMap[yGridCord][xGridCord]->entity = nullptr;
            xGridCord++;
            gridMap[yGridCord][xGridCord]->entity = this;
            break;
        case LEFT:
            gridMap[yGridCord][xGridCord]->entity = nullptr;
            xGridCord--;
            gridMap[yGridCord][xGridCord]->entity = this;
            break;
        default: break;
    }
}


//This checks to see if the entity is within the visible grid.
//There may be a more efficient way of doing this by using the visible grid and going tile by tile
// and adjusting the entities values through that
void Entity::setVisibleCoordinates(int tempX, int tempY) {
    xVisibleCord = tempX;
    yVisibleCord = tempY;
    /*
    for (int i = 0; i < visibleGridLocations.size(); i++) {
        for (int j = 0; j < visibleGridLocations[i].size(); j++) {
            if (visibleGridLocations[i][j]->entity == this) {
                xVisibleCord = j;
                yVisibleCord = i;
                return;
            }
        }
    }
    xVisibleCord = -1;
    yVisibleCord = -1;*/
}

//These are the rectangles around the entity that are actually visible. This is used for collisions with the mouse etc.
Rectangle Entity::ownedVisibleRectangle() {
    return {xVisibleCord*(int)(standardWidth*visualScalingFactor)+topLeftCornerXPos, yVisibleCord*(int)(standardHeight*visualScalingFactor)+topLeftCornerYpos, (float)standardWidth, (float)standardHeight};
}

Rectangle Entity::rightVisibleRectangle() {
    return {(xVisibleCord+1)*(int)(standardWidth*visualScalingFactor)+topLeftCornerXPos, yVisibleCord*(int)(standardHeight*visualScalingFactor)+topLeftCornerYpos, (float)standardWidth, (float)standardHeight};
}

Rectangle Entity::leftVisibleRectangle() {
    return {(xVisibleCord-1)*(int)(standardWidth*visualScalingFactor)+topLeftCornerXPos, yVisibleCord*(int)(standardHeight*visualScalingFactor)+topLeftCornerYpos, (float)standardWidth, (float)standardHeight};
}

Rectangle Entity::aboveVisibleRectangle() {
    return {xVisibleCord*(int)(standardWidth*visualScalingFactor)+topLeftCornerXPos, (yVisibleCord-1)*(int)(standardHeight*visualScalingFactor)+topLeftCornerYpos, (float)standardWidth, (float)standardHeight};
}

Rectangle Entity::belowVisibleRectangle() {
    return {xVisibleCord*(int)(standardWidth*visualScalingFactor)+topLeftCornerXPos, (yVisibleCord+1)*(int)(standardHeight*visualScalingFactor)+topLeftCornerYpos, (float)(standardWidth*visualScalingFactor), (float)(standardHeight*visualScalingFactor)};
}