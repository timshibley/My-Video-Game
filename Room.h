//
// Created by shibl on 10/25/2025.
//

#ifndef ROOM_H
#define ROOM_H
#include <vector>

#include "Tile.h"


class Room {
    public:
        std::vector<std::vector<Tile*>>  tiles;
        int exits;
        int id;
        int length;
        int height;
        Room(int l, int h, int e, int i);
        Room();
        void constructGrid();
};


#endif //ROOM_H
