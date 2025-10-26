//
// Created by shibl on 10/25/2025.
//

#ifndef TILE_H
#define TILE_H
#include "Location.h"


class Tile {

    public:
        Location location;
        Texture2D texture;
        int id;
        Tile(Location l, Texture2D t, int i);

};



#endif //TILE_H
