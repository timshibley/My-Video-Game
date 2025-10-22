//
// Created by shibl on 1/26/2025.
//

#include "Enemy.h"

#include "Macros.h"

Enemy::Enemy() {
    setId(MONSTER_ID);
    rectangle = {0, 0, 0, 0};
}

Enemy::Enemy(float x, float y, float width, float height, int i, int v, Color c, Texture2D t, int k, int xGrid, int yGrid, int hp) {
    setId(i);
    setColor(c);
    setRectangle({x, y, width, height});
    setTexture(t);
    textureTracker = k;
    setVisibility(true);
    setXGridCoordinate(xGrid);
    setYGridCoordinate(yGrid);
    healthPoints = hp;
    maxHealthPoints = hp;
}

int Enemy::getCurrentHP() {
    return healthPoints;
}

int Enemy::getMaxHP() {
    return maxHealthPoints;
}

void Enemy::setCurrentHP(int hp) {
    healthPoints = hp;
}

void Enemy::setMaxHP(int hp) {
    maxHealthPoints = hp;
}
