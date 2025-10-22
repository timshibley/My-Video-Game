//
// Created by shibl on 1/13/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Location.h"
#include "raylib.h"



class Player: public Entity {

    int healthPoints;
    int maxHealthPoints;
    int lookingDirection;
    public:
    int getCurrentHP();
    int getMaxHP();
    void setCurrentHP(int hp);
    void setMaxHP(int hp);
    int getLookingDirection();
    void setLookingDirection(int direction);
    void specialMoveScreen(int direction);
    Player();
    Player(float x, float y, float width, float height, int i, Color c, Texture2D t, int k, int hp);
};



#endif //PLAYER_H
