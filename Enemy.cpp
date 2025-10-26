// This is my Enemy class which is a subclass of Entity
// I could definitely see myself creating subclasses of Enemy once I want to develop unique types of enemies.
// Created by shibl on 1/26/2025.
//

#include "Enemy.h"

#include "Macros.h"
/*
 *To do:
 *create a take damage function to improve readability of code(low urgency)
 */
//This is never used, but I have it written just in case I eventually want to use it.
Enemy::Enemy() {
    setId(MONSTER_ID);
    rectangle = {0, 0, 0, 0};
}


//This is my constructor I actually use throughout the program, because as of now I am accounting for knowing all of their values
//when the enemy is initialized.
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

//Getter function for healthPoints
int Enemy::getCurrentHP() {
    return healthPoints;
}

//Getter function for maxHealthPoints
int Enemy::getMaxHP() {
    return maxHealthPoints;
}

//Setter function for currentHP
void Enemy::setCurrentHP(int hp) {
    healthPoints = hp;
}

//setter function for maxHP
void Enemy::setMaxHP(int hp) {
    maxHealthPoints = hp;
}
