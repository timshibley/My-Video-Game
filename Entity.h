//
// Created by shibl on 1/15/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
//#include "EntityNode.h"
#include "raylib.h"

class Enemy;

//class EntityNode;
class Entity {
private:
    int id;
    Texture2D texture;
    Color color;
    bool visible;
    int xGridCord, yGridCord;//These are in terms of all grid blocks
    int xVisibleCord, yVisibleCord;
public:
    int textureTracker;
    Rectangle rectangle;
    virtual ~Entity()= default;
    Entity();
    Entity(float x, float y, float width, float height, int i, int v, Color c, Texture2D t, int k, int xGrid, int yGrid);
    Rectangle* getRectangle();
    int getId();
    Vector2 getPosition();
    Vector2 getSize();
    Color getColor();
    bool isVisible();
    void setId(int i);
    void setTexture(Texture2D t);
    Texture2D getTexture();
    void setXCoordinate(float xPos);
    void setYCoordinate(float yPos);
    void setXGridCoordinate(int xGrid);
    void setYGridCoordinate(int yGrid);
    int getXVisibleCoordinate();
    int getYVisibleCoordinate();
    int getXGridCoordinate();
    int getYGridCoordinate();
    void setVisibleCoordinates();
    void setVisibility(bool v);
    void setColor(Color c);
    void setRectangle(Rectangle r);
    void moveInDirection(int dir);
    bool isTileAdjacent(int direction);
    bool isTileOccupied(int direction, int chosenID);
    Rectangle ownedVisibleRectangle();
    Rectangle rightVisibleRectangle();
    Rectangle leftVisibleRectangle();
    Rectangle aboveVisibleRectangle();
    Rectangle belowVisibleRectangle();
    Enemy* adjacentEnemy(int direction);
    Entity* adjacentEntity(int direction);
};



#endif //ENTITY_H
