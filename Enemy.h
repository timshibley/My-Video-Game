//
// Created by shibl on 1/26/2025.
//

#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"


class Enemy : public Entity {

    int healthPoints;
    int maxHealthPoints;
public:
    Enemy(float x, float y, float width, float height, int i, int v, Color c, Texture2D t, int k, int xGrid, int yGrid, int hp);
    Enemy();
    int getCurrentHP();
    int getMaxHP();
    void setCurrentHP(int hp);
    void setMaxHP(int hp);
};



#endif //ENEMY_H
