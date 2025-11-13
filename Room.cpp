//
// Created by shibl on 10/25/2025.
//

#include "Room.h"

#include "main.h"

Room::Room(int l, int h, int e, int i) {
    length = l;
    height = h;
    exits = e;
    id = i;
    constructGrid();
}

Room::Room() {
    length = 0;
    height = 0;
    exits = 0;
    id = 0;
}

void Room::constructGrid(){
    tiles.resize(height);
    for (auto &i : tiles) {
        i.resize(length);
    }
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < height; j++) {
            Location tempLocation;
            if (i == 0 ||j == 0 || i == length-1 || j == height-1) {
                tempLocation=  Location(nullptr, {static_cast<float>(standardWidth*visualScalingFactor*i),static_cast<float>( standardHeight*visualScalingFactor * j), static_cast<float>( standardWidth * visualScalingFactor), static_cast<float>( standardHeight * visualScalingFactor)}, RED);

            }
            else {
                tempLocation =  Location(nullptr, {static_cast<float>(standardWidth * visualScalingFactor * i),static_cast<float>( standardHeight *visualScalingFactor * j), static_cast<float>( standardWidth * visualScalingFactor), static_cast<float>( standardHeight * visualScalingFactor)}, BLUE);

            }
            Tile* temp= new Tile(tempLocation,tileTextures[0], id);
            tiles[j][i] = temp;
        }
    }
}

Entity* Room::getEntityAt(int x, int y) {
    return tiles[y][x]->location.entity;
}

void Room::setEntityAt(int x, int y, Entity *e) {
    tiles[y][x]->location.entity = e;
}


