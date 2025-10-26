//
// Created by shibl on 1/25/2025.
//

#include "Location.h"

#include "main.h"

Location::Location() {
    entity = nullptr;
    rectangle = {0,0,0,0};
}
Location::Location(Entity* e, Rectangle r, Color c) {
    entity = e;
    rectangle = r;
    color = c;
}

Location::Location(Entity *e, Rectangle r) {
    entity = e;
    rectangle = r;
}
Location::Location(Entity *e) {
    entity = e;
    rectangle = {0,0,0,0};
    color = WHITE;
}


bool Location::isEqual(Location loc) {
    bool result = false;
    if (loc.rectangle.x == rectangle.x && loc.rectangle.y == rectangle.y) {
        result = true;
    }
    return result;
}

bool Location::isEdge() {
    if (rectangle.x == 0 || rectangle.y == 0) {
        return true;
    }
    if (rectangle.x  == gridMap[0][gridMap.size()-1]->rectangle.x || rectangle.y == gridMap[gridMap.size()-1][0]->rectangle.y) {
        return true;
    }
    return false;
}
/*
void Location::draw(int x, int y) {
    DrawRectangle(x * 100, y * 100, rectangle.width, rectangle.height, color);
}*/

void Location::setColor(Color c) {
    color = c;
}

Color Location::getColor() {
    return color;
}

