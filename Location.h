//
// Created by shibl on 1/25/2025.
//

#ifndef LOCATION_H
#define LOCATION_H
#include "Entity.h"
#include "raylib.h"


class Location {
    public:
    Rectangle rectangle;
    Entity* entity;
    Color color;
   // void setEntity(Entity e);
    //Entity getEntity();
    //Location();
    Location(Entity* e, Rectangle r, Color c);
    Location(Entity* e, Rectangle r);
    Location(Entity* e);
    Location();
    bool isEqual(Location loc);
    bool isEdge();
    void draw(int x, int y);
    void setColor(Color c);
    Color getColor();
};



#endif //LOCATION_H
