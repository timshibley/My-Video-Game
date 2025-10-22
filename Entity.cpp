//
// Created by shibl on 1/15/2025.
//

#include "Entity.h"

#include <stdio.h>

#include "Enemy.h"
#include "Macros.h"
#include "main.h"

Entity::Entity() {
    id = 0;
    rectangle = {0, 0, 0, 0};
}
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
    return rectangle.x;
}

int Entity::getYVisibleCoordinate() {
    return rectangle.y;
}





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
bool Entity::isTileOccupied(int direction, int chosenID) {
    bool decision = false;
    if (isTileAdjacent(direction)) {
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


void Entity::moveInDirection(int dir) {
    switch (dir) {
        case UP:
            gridMap[yGridCord][xGridCord]->entity = nullptr;
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

void Entity::setVisibleCoordinates() {
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
    yVisibleCord = -1;
}

Rectangle Entity::ownedVisibleRectangle() {
    return {xVisibleCord*100+topLeftCornerXPos, yVisibleCord*100+topLeftCornerYpos, 100, 100};
}

Rectangle Entity::rightVisibleRectangle() {
    return {(xVisibleCord+1)*100+topLeftCornerXPos, yVisibleCord*100+topLeftCornerYpos, 100, 100};
}

Rectangle Entity::leftVisibleRectangle() {
    return {(xVisibleCord-1)*100+topLeftCornerXPos, yVisibleCord*100+topLeftCornerYpos, 100, 100};
}

Rectangle Entity::aboveVisibleRectangle() {
    return {xVisibleCord*100+topLeftCornerXPos, (yVisibleCord-1)*100+topLeftCornerYpos, 100, 100};
}

Rectangle Entity::belowVisibleRectangle() {
    return {xVisibleCord*100+topLeftCornerXPos, (yVisibleCord+1)*100+topLeftCornerYpos, 100, 100};
}