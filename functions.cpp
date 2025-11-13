//
// Created by shibl on 1/13/2025.
//

#include "functions.h"
#include "raylib.h"
#include "main.h"
#include <external/rprand.h>
#include "Macros.h"
#include "Entity.h"
#include <cmath>
#include "raymath.h"

//This checks all of the keys
void checkKeys() {

    //Changes direction being faced by player
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (player.isTileAdjacent(UP) && CheckCollisionPointRec(GetMousePosition(), player.aboveVisibleRectangle())) {
            player.setLookingDirection(LOOKING_UP);
            player.setTexture(playerTextures[MC_UP_TEXTURE]);
        }
        else if (player.isTileAdjacent(DOWN) && CheckCollisionPointRec(GetMousePosition(), player.belowVisibleRectangle())) {
            player.setLookingDirection(LOOKING_DOWN);
            player.setTexture(playerTextures[MC_DOWN_TEXTURE]);
        }
        else if (player.isTileAdjacent(RIGHT) && CheckCollisionPointRec(GetMousePosition(), player.rightVisibleRectangle())) {
            player.setLookingDirection(LOOKING_RIGHT);
            player.setTexture(playerTextures[MC_RIGHT_TEXTURE]);
        }
        else if (player.isTileAdjacent(LEFT) && CheckCollisionPointRec(GetMousePosition(), player.leftVisibleRectangle())) {
            player.setLookingDirection(LOOKING_LEFT);
            player.setTexture(playerTextures[MC_LEFT_TEXTURE]);
        }
    }

    //Moves player up
    if (IsKeyPressed(KEY_W)){
        if (player.isTileAdjacent(UP) && mainRoom.tiles[player.getYGridCoordinate()-1][player.getXGridCoordinate()]->location.entity == nullptr) {
            if (!visibleTiles[0][(visibleTiles[0].size()-1)/2]->location.isEdge() && walkUpDownWallCount == 0) {
                player.specialMoveScreen(UP);
            }
            else {
                player.moveInDirection(UP);
                walkUpDownWallCount++;
            }
            player.setTexture(playerTextures[MC_UP_TEXTURE]);
            player.setLookingDirection(LOOKING_UP);
            turnTracker = OPPONENTTURN;
        }

    }
    //Moves player down
    if (IsKeyPressed(KEY_S)) {
        if (player.isTileAdjacent(DOWN) && mainRoom.tiles[player.getYGridCoordinate()+1][player.getXGridCoordinate()]->location.entity == nullptr ) {
            if (!visibleTiles[visibleTiles.size()-1][(visibleTiles[0].size()-1)/2]->location.isEdge() && walkUpDownWallCount == 0) {
                player.specialMoveScreen(DOWN);
            }
            else {
                player.moveInDirection(DOWN);
                walkUpDownWallCount--;
            }
            player.setTexture(playerTextures[MC_DOWN_TEXTURE]);
            player.setLookingDirection(DOWN);
            turnTracker = OPPONENTTURN;
        }
    }

    //Moves player right
    if (IsKeyPressed(KEY_D)) {
        if (player.isTileAdjacent(RIGHT) && mainRoom.tiles[player.getYGridCoordinate()][player.getXGridCoordinate()+1]->location.entity == nullptr ) {
            if (!visibleTiles[(visibleTiles.size()-1)/2][visibleTiles[0].size()-1]->location.isEdge() && walkLeftRightWallCount == 0) {
                player.specialMoveScreen(RIGHT);
            }
            else {
                player.moveInDirection(RIGHT);
                walkLeftRightWallCount++;
            }
            player.setTexture(playerTextures[MC_RIGHT_TEXTURE]);
            player.setLookingDirection(RIGHT);
            turnTracker = OPPONENTTURN;
        }
    }

    //Moves player left
    if (IsKeyPressed(KEY_A)) {
        if (player.isTileAdjacent(LEFT)&& mainRoom.tiles[player.getYGridCoordinate()][player.getXGridCoordinate()-1]->location.entity == nullptr ) {
            if (!visibleTiles[(visibleTiles.size()-1)/2][0]->location.isEdge() && walkLeftRightWallCount == 0) {
                player.specialMoveScreen(LEFT);

            }
            else {
                player.moveInDirection(LEFT);
                walkLeftRightWallCount--;
            }
            player.setTexture(playerTextures[MC_LEFT_TEXTURE]);
            player.setLookingDirection(LEFT);
            turnTracker = OPPONENTTURN;
        }
    }
    //Uses the fire attack
    if (IsKeyPressed(KEY_B)) {
        if (player.isTileAdjacent(player.getLookingDirection())) {
            if (player.isTileOccupied(player.getLookingDirection(), MONSTER_ID)) {
                    Entity* temp = player.adjacentEntity(player.getLookingDirection());
                    if (temp != nullptr) {
                        attackTracker = EXECUTE_FIRE_ATTACK;
                    }


            }
        }
    }
    //Displays/Hides the menu
    if (IsKeyPressed(KEY_E)) {
        mainMenu.setVisibility(!mainMenu.getVisibility());
    }

}


//Checks the collisions between entities.
void checkCollisions() {
    EntityNode* nodeWalker = entityManager->findIDTree(DOOR_ID);
    if (nodeWalker->entry->isVisible() == VISIBLE && CheckCollisionRecs(player.rectangle, *nodeWalker->entry->getRectangle())) {
        nodeWalker->entry->setVisibility(INVISIBLE);
        backgroundColor = BLUE;
    }
    nodeWalker = entityManager->findIDTree(MONSTER_ID);
    while (nodeWalker != nullptr) {
        if (nodeWalker->entry->isVisible() == VISIBLE && CheckCollisionRecs(player.rectangle, *nodeWalker->entry->getRectangle())) {
            mainRoom.tiles[nodeWalker->entry->getYGridCoordinate()][nodeWalker->entry->getXGridCoordinate()]->location.entity = nullptr;
            entityManager->deleteNthID(MONSTER_ID, nodeWalker->level);
        }
        nodeWalker = nodeWalker->next;
    }
}


//This runs the entity AIs
void checkBotAI() {
    EntityNode* monster = entityManager->findIDTree(MONSTER_ID);
    while (monster != nullptr) {

        if (monster->entry->isVisible() == VISIBLE) {
            //Moves towards the player if they are less than 4 tiles away from them.
             if (abs(player.getXGridCoordinate() - monster->entry->getXGridCoordinate()) <= 3 && abs(player.getYGridCoordinate() - monster->entry->getYGridCoordinate()) <= 3) {
                if (abs(player.getXGridCoordinate() - monster->entry->getXGridCoordinate()) > abs(player.getYGridCoordinate() - monster->entry->getYGridCoordinate())) {
                    if (player.getXGridCoordinate() > monster->entry->getXGridCoordinate() && mainRoom.tiles[monster->entry->getYGridCoordinate()][monster->entry->getXGridCoordinate()+1]->location.entity == nullptr) {
                        monster->entry->moveInDirection(RIGHT);
                    }
                    else if (monster->entry->getXGridCoordinate() > player.getXGridCoordinate() && mainRoom.tiles[monster->entry->getYGridCoordinate()][monster->entry->getXGridCoordinate()-1]->location.entity == nullptr) {
                        monster->entry->moveInDirection(LEFT);
                    }
                }
                else {
                    if (player.getYGridCoordinate() > monster->entry->getYGridCoordinate() && mainRoom.tiles[monster->entry->getYGridCoordinate()+1][monster->entry->getXGridCoordinate()]->location.entity == nullptr) {
                        monster->entry->moveInDirection(DOWN);
                    }
                    else if (monster->entry->getYGridCoordinate() > player.getYGridCoordinate() && mainRoom.tiles[monster->entry->getYGridCoordinate()-1][monster->entry->getXGridCoordinate()]->location.entity == nullptr) {
                        monster->entry->moveInDirection(UP);

                    }
                }
            }
            //Moves in a random direction.
             else {
                switch (rprand_get_value(0,4)) {
                    case STAY_STILL:
                        break;

                    case MOVE_UP:
                        if (!monster->entry->isTileOccupied(UP, DONT_CARE_ID)) {
                            monster->entry->moveInDirection(UP);
                        }
                        break;
                    case MOVE_DOWN:
                        if (!monster->entry->isTileOccupied(DOWN, DONT_CARE_ID)) {
                            monster->entry->moveInDirection(DOWN);
                        }
                        break;
                    case MOVE_LEFT:
                        if (!monster->entry->isTileOccupied(LEFT, DONT_CARE_ID)) {
                            monster->entry->moveInDirection(LEFT);
                        }
                        break;

                    case MOVE_RIGHT:
                        if (!monster->entry->isTileOccupied(RIGHT, DONT_CARE_ID)) {
                            monster->entry->moveInDirection(RIGHT);
                        }
                        break;

                    default:
                        break;
                }
            }

        }
        monster = monster->next;
    }
    turnTracker = PLAYERTURN;

}

int convertXPosToGrid(Location pos) {
    return pos.rectangle.x/standardWidth;
}

int convertYPosToGrid(Location pos) {
    return pos.rectangle.y/standardHeight;
}

//Checks which entities are on the visible grid.
void upkeepEntitiesOnVisibleGrid() {
    for (int i =0; i < visibleTiles.size(); i++) {
        for (int j = 0; j < visibleTiles[i].size(); j++) {
            if (visibleTiles[i][j]->location.entity != nullptr) {
                visibleTiles[i][j]->location.entity->setVisibleCoordinates(j, i);
            }
        }
    }
}




