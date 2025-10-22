//
// Created by shibl on 1/13/2025.
//

#include "Player.h"
#include "functions.h"
#include "Macros.h"
#include "main.h"

Player::Player() {
    setId(PLAYER_ID);
    rectangle = {0, 0, 0, 0};
}
Player::Player(float x, float y, float height, float width, int i, Color c, Texture2D t, int k, int hp) {
    setId(i);
    setColor(c);
    setRectangle({x, y, width, height});
    setTexture(t);
    textureTracker = k;
    setVisibility(true);
    healthPoints = hp;
    maxHealthPoints = hp;
    lookingDirection = LOOKING_RIGHT;
}

int Player::getCurrentHP() {
    return healthPoints;
}

int Player::getMaxHP() {
    return maxHealthPoints;
}

int Player::getLookingDirection() {
    return lookingDirection;
}

void Player::setCurrentHP(int hp) {
    healthPoints = hp;
}

void Player::setMaxHP(int hp) {
    maxHealthPoints = hp;
}

void Player::setLookingDirection(int direction) {
    lookingDirection = direction;
}

void Player::specialMoveScreen(int direction) {
    std::vector<std::vector<Location*>> tempLocations = visibleGridLocations;
    switch (direction) {
        case UP: {
            if (walkLeftRightWallCount == 0) {
                this->moveInDirection(UP);
                for (int i = 1; i < visibleGridLocations.size(); i++) {
                    for (int j = 0; j < visibleGridLocations[0].size(); j++) {
                        visibleGridLocations[i][j] = tempLocations[i-1][j];
                    }
                }
                for (int j = 0; j < visibleGridLocations[0].size(); j++) {
                    visibleGridLocations[0][j] = gridMap[this->getYGridCoordinate()-(visibleGridLocations.size()-1)/2][this->getXGridCoordinate() -(visibleGridLocations.size()-1)/2 + j];
                }
            }
            else {
                this->moveInDirection(UP);
                for (int i = visibleGridLocations.size()-1; i >0; i--) {
                    for (int j = 0; j < visibleGridLocations[0].size(); j++) {
                        visibleGridLocations[i][j] = tempLocations[i-1][j];
                    }
                }
                for (int i = 0; i < visibleGridLocations[0].size(); i++) {
                    visibleGridLocations[0][i] = gridMap[this->getYGridCoordinate()-(visibleGridLocations.size()-1)/2][convertXPosToGrid(visibleGridLocations[0][i])];
                }
            }

            break;
        }


        case DOWN: {
            if (walkLeftRightWallCount == 0) {
                this->moveInDirection(DOWN);
                for (int i = 0; i < visibleGridLocations.size()-1; i++) {
                    for (int j = 0; j < visibleGridLocations[0].size(); j++) {
                        visibleGridLocations[i][j] = tempLocations[i+1][j];
                    }
                }
                for (int j = 0; j < visibleGridLocations[0].size(); j++) {
                    visibleGridLocations[visibleGridLocations.size()-1][j] = gridMap[this->getYGridCoordinate()+(visibleGridLocations.size()-1)/2][this->getXGridCoordinate() -(visibleGridLocations.size()-1)/2 + j];
                }
            }
            else {
                this->moveInDirection(DOWN);
                for (int i = 0; i < visibleGridLocations.size()-1; i++) {
                    for (int j = 0; j < visibleGridLocations[0].size(); j++) {
                        visibleGridLocations[i][j] = tempLocations[i+1][j];
                    }
                }
                for (int i = 0; i < visibleGridLocations[0].size(); i++) {
                    if (this->getXGridCoordinate() - walkUpDownWallCount+i>=0) {
                        visibleGridLocations[visibleGridLocations.size()-1][i] = gridMap[this->getYGridCoordinate()+(visibleGridLocations.size()-1)/2][convertXPosToGrid(visibleGridLocations[visibleGridLocations.size()-1][i])];
                    }
                }
            }


            break;
        }


        case RIGHT: {
            if (walkUpDownWallCount == 0) {
                this->moveInDirection(RIGHT);
                for (int i = 0; i < visibleGridLocations.size(); i++) {
                    for (int j = 0; j < visibleGridLocations[0].size()-1; j++) {
                        visibleGridLocations[i][j] = tempLocations[i][j+1];
                    }
                }

                for (int i = 0; i < visibleGridLocations.size(); i++) {
                    if ((this->getYGridCoordinate() -(visibleGridLocations.size()-1)/2+i)>=0) {
                        visibleGridLocations[i][visibleGridLocations[0].size()-1] = gridMap[this->getYGridCoordinate()-(visibleGridLocations.size()-1)/2+i][this->getXGridCoordinate() + (visibleGridLocations.size()-1)/2];
                    }
                }
            }
            else {
                    this->moveInDirection(RIGHT);
                    for (int i = 0; i < visibleGridLocations.size(); i++) {
                        for (int j = 0; j < visibleGridLocations[0].size()-1; j++) {
                            visibleGridLocations[i][j] = tempLocations[i][j+1];
                        }
                    }

                    for (int i = 0; i < visibleGridLocations.size(); i++) {
                        visibleGridLocations[i][visibleGridLocations[0].size()-1] = gridMap[convertYPosToGrid(visibleGridLocations[i][visibleGridLocations[0].size()-1])][this->getXGridCoordinate() + (visibleGridLocations.size()-1)/2];
                    }
            }

            break;
        }

        case LEFT: {
            if (walkUpDownWallCount == 0) {
                this->moveInDirection(LEFT);
                for (int i = 0; i < visibleGridLocations.size(); i++) {
                    for (int j = 1; j < visibleGridLocations[0].size(); j++) {
                        visibleGridLocations[i][j] = tempLocations[i][j-1];
                    }
                }
                for (int i = 0; i < visibleGridLocations.size(); i++) {
                    visibleGridLocations[i][0] = gridMap[this->getYGridCoordinate()-(visibleGridLocations.size()-1)/2+i][this->getXGridCoordinate() - (visibleGridLocations.size()-1)/2];
                }
            }
            else {
                this->moveInDirection(LEFT);
                for (int i = 0; i < visibleGridLocations.size(); i++) {
                    for (int j = 1; j < visibleGridLocations[0].size(); j++) {
                        visibleGridLocations[i][j] = tempLocations[i][j-1];
                    }
                }

                for (int i = 0; i < visibleGridLocations.size(); i++) {
                    visibleGridLocations[i][0] = gridMap[convertYPosToGrid(visibleGridLocations[i][0])][this->getXGridCoordinate() - (visibleGridLocations.size()-1)/2];
                }
            }

            break;
        }

        default: break;
    }
}

