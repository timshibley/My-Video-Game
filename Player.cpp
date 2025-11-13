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


//This is used when the visible grid and player moves. The player does not move relative to the screen.
void Player::specialMoveScreen(int direction) {
    std::vector<std::vector<Tile*>> tempTiles = visibleTiles;
    switch (direction) {
        case UP: {
            //Checks if the player is near a wall.
            if (walkLeftRightWallCount == 0) {
                this->moveInDirection(UP);
                //Moves the visible grid
                for (int i = 1; i < visibleTiles.size(); i++) {
                    for (int j = 0; j < visibleTiles[0].size(); j++) {
                        visibleTiles[i][j] = tempTiles[i-1][j];
                    }
                }

                for (int j = 0; j < visibleTiles[0].size(); j++) {
                    visibleTiles[0][j] = mainRoom.tiles[this->getYGridCoordinate()-(visibleTiles.size()-1)/2][this->getXGridCoordinate() -(visibleTiles.size()-1)/2 + j];
                }
            }
            else {
                this->moveInDirection(UP);
                //Moves the visible grid
                for (int i = visibleTiles.size()-1; i >0; i--) {
                    for (int j = 0; j < visibleTiles[0].size(); j++) {
                        visibleTiles[i][j] = tempTiles[i-1][j];
                    }
                }
                for (int i = 0; i < visibleTiles[0].size(); i++) {
                    visibleTiles[0][i] = mainRoom.tiles[this->getYGridCoordinate()-(visibleTiles.size()-1)/2][convertXPosToGrid(visibleTiles[0][i]->location)];
                }
            }

            break;
        }

        /*
         *It is the same principle throughout the whole function.
         */
        case DOWN: {
            if (walkLeftRightWallCount == 0) {
                this->moveInDirection(DOWN);
                for (int i = 0; i < visibleTiles.size()-1; i++) {
                    for (int j = 0; j < visibleTiles[0].size(); j++) {
                        visibleTiles[i][j] = tempTiles[i+1][j];
                    }
                }
                for (int j = 0; j < visibleTiles[0].size(); j++) {
                    visibleTiles[visibleTiles.size()-1][j] = mainRoom.tiles[this->getYGridCoordinate()+(visibleTiles.size()-1)/2][this->getXGridCoordinate() -(visibleTiles.size()-1)/2 + j];
                }
            }
            else {
                this->moveInDirection(DOWN);
                for (int i = 0; i < visibleTiles.size()-1; i++) {
                    for (int j = 0; j < visibleTiles[0].size(); j++) {
                        visibleTiles[i][j] = tempTiles[i+1][j];
                    }
                }
                for (int i = 0; i < visibleTiles[0].size(); i++) {
                    if (this->getXGridCoordinate() - walkUpDownWallCount+i>=0) {
                        visibleTiles[visibleTiles.size()-1][i] = mainRoom.tiles[this->getYGridCoordinate()+(visibleTiles.size()-1)/2][convertXPosToGrid(visibleTiles[visibleTiles.size()-1][i]->location)];
                    }
                }
            }


            break;
        }


        case RIGHT: {
            if (walkUpDownWallCount == 0) {
                this->moveInDirection(RIGHT);
                for (int i = 0; i < visibleTiles.size(); i++) {
                    for (int j = 0; j < visibleTiles[0].size()-1; j++) {
                        visibleTiles[i][j] = tempTiles[i][j+1];
                    }
                }

                for (int i = 0; i < visibleTiles.size(); i++) {
                    if ((this->getYGridCoordinate() -(visibleTiles.size()-1)/2+i)>=0) {
                        visibleTiles[i][visibleTiles[0].size()-1] = mainRoom.tiles[this->getYGridCoordinate()-(visibleTiles.size()-1)/2+i][this->getXGridCoordinate() + (visibleTiles.size()-1)/2];
                    }
                }
            }
            else {
                    this->moveInDirection(RIGHT);
                    for (int i = 0; i < visibleTiles.size(); i++) {
                        for (int j = 0; j < visibleTiles[0].size()-1; j++) {
                            visibleTiles[i][j] = tempTiles[i][j+1];
                        }
                    }

                    for (int i = 0; i < visibleTiles.size(); i++) {
                        visibleTiles[i][visibleTiles[0].size()-1] = mainRoom.tiles[convertYPosToGrid(visibleTiles[i][visibleTiles[0].size()-1]->location)][this->getXGridCoordinate() + (visibleTiles.size()-1)/2];
                    }
            }

            break;
        }

        case LEFT: {
            if (walkUpDownWallCount == 0) {
                this->moveInDirection(LEFT);
                for (int i = 0; i < visibleTiles.size(); i++) {
                    for (int j = 1; j < visibleTiles[0].size(); j++) {
                        visibleTiles[i][j] = tempTiles[i][j-1];
                    }
                }
                for (int i = 0; i < visibleTiles.size(); i++) {
                    visibleTiles[i][0] = mainRoom.tiles[this->getYGridCoordinate()-(visibleTiles.size()-1)/2+i][this->getXGridCoordinate() - (visibleTiles.size()-1)/2];
                }
            }
            else {
                this->moveInDirection(LEFT);
                for (int i = 0; i < visibleTiles.size(); i++) {
                    for (int j = 1; j < visibleTiles[0].size(); j++) {
                        visibleTiles[i][j] = tempTiles[i][j-1];
                    }
                }

                for (int i = 0; i < visibleTiles.size(); i++) {
                    visibleTiles[i][0] = mainRoom.tiles[convertYPosToGrid(visibleTiles[i][0]->location)][this->getXGridCoordinate() - (visibleTiles.size()-1)/2];
                }
            }

            break;
        }

        default: break;
    }
}

