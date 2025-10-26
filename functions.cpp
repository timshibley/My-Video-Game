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
void checkKeys() {
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
    if (IsKeyPressed(KEY_W)){
        if (player.isTileAdjacent(UP) && gridMap[player.getYGridCoordinate()-1][player.getXGridCoordinate()]->entity == nullptr) {
            if (!visibleGridLocations[0][(visibleGridLocations[0].size()-1)/2]->isEdge() && walkUpDownWallCount == 0) {
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
    if (IsKeyPressed(KEY_S)) {
        if (player.isTileAdjacent(DOWN) && gridMap[player.getYGridCoordinate()+1][player.getXGridCoordinate()]->entity == nullptr ) {
            if (!visibleGridLocations[visibleGridLocations.size()-1][(visibleGridLocations[0].size()-1)/2]->isEdge() && walkUpDownWallCount == 0) {
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
    if (IsKeyPressed(KEY_D)) {
        if (player.isTileAdjacent(RIGHT) && gridMap[player.getYGridCoordinate()][player.getXGridCoordinate()+1]->entity == nullptr ) {
            if (!visibleGridLocations[(visibleGridLocations.size()-1)/2][visibleGridLocations[0].size()-1]->isEdge() && walkLeftRightWallCount == 0) {
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
    if (IsKeyPressed(KEY_A)) {
        if (player.isTileAdjacent(LEFT)&& gridMap[player.getYGridCoordinate()][player.getXGridCoordinate()-1]->entity == nullptr ) {
            if (!visibleGridLocations[(visibleGridLocations.size()-1)/2][0]->isEdge() && walkLeftRightWallCount == 0) {
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
    if (IsKeyPressed(KEY_E)) {
        mainMenu.setVisibility(!mainMenu.getVisibility());
    }

}

void checkCollisions() {
    EntityNode* nodeWalker = entityManager->findIDTree(DOOR_ID);
    if (nodeWalker->entry->isVisible() == VISIBLE && CheckCollisionRecs(player.rectangle, *nodeWalker->entry->getRectangle())) {
        nodeWalker->entry->setVisibility(INVISIBLE);
        backgroundColor = BLUE;
    }
    nodeWalker = entityManager->findIDTree(MONSTER_ID);
    while (nodeWalker != nullptr) {
        if (nodeWalker->entry->isVisible() == VISIBLE && CheckCollisionRecs(player.rectangle, *nodeWalker->entry->getRectangle())) {
            gridMap[nodeWalker->entry->getYGridCoordinate()][nodeWalker->entry->getXGridCoordinate()]->entity = nullptr;
            entityManager->deleteNthID(MONSTER_ID, nodeWalker->level);
        }
        nodeWalker = nodeWalker->next;
    }
}

void checkBotAI() {
    EntityNode* monster = entityManager->findIDTree(MONSTER_ID);
    while (monster != nullptr) {
        if (monster->entry->isVisible() == VISIBLE) {
             if (abs(player.getXGridCoordinate() - monster->entry->getXGridCoordinate()) <= 3 && abs(player.getYGridCoordinate() - monster->entry->getYGridCoordinate()) <= 3) {
                if (abs(player.getXGridCoordinate() - monster->entry->getXGridCoordinate()) > abs(player.getYGridCoordinate() - monster->entry->getYGridCoordinate())) {
                    if (player.getXGridCoordinate() > monster->entry->getXGridCoordinate() && gridMap[monster->entry->getYGridCoordinate()][monster->entry->getXGridCoordinate()+1]->entity == nullptr) {
                        monster->entry->moveInDirection(RIGHT);
                    }
                    else if (monster->entry->getXGridCoordinate() > player.getXGridCoordinate() && gridMap[monster->entry->getYGridCoordinate()][monster->entry->getXGridCoordinate()-1]->entity == nullptr) {
                        monster->entry->moveInDirection(LEFT);
                    }
                }
                else {
                    if (player.getYGridCoordinate() > monster->entry->getYGridCoordinate() && gridMap[monster->entry->getYGridCoordinate()+1][monster->entry->getXGridCoordinate()]->entity == nullptr) {
                        monster->entry->moveInDirection(DOWN);
                    }
                    else if (monster->entry->getYGridCoordinate() > player.getYGridCoordinate() && gridMap[monster->entry->getYGridCoordinate()-1][monster->entry->getXGridCoordinate()]->entity == nullptr) {
                        monster->entry->moveInDirection(UP);

                    }
                }
            }
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


int convertXPosToGrid(Location* pos) {
    return pos->rectangle.x/standardWidth;
}

int convertYPosToGrid(Location* pos) {
    return pos->rectangle.y/standardHeight;
}

void upkeepEntitiesOnVisibleGrid() {
    /*
    EntityNode* e = entityManager->head;
    while (e != nullptr) {
        e->entry->setVisibleCoordinates();
        if (e->next == nullptr) {
            e = entityManager->findIDTree(e->entry->getId());
            e = e->newID;
        }
        else {
            e = e->next;
        }
    }*/
    for (int i =0; i < visibleGridLocations.size(); i++) {
        for (int j = 0; j < visibleGridLocations[i].size(); j++) {
            if (visibleGridLocations[i][j]->entity != nullptr) {
                visibleGridLocations[i][j]->entity->setVisibleCoordinates(j, i);
            }
        }
    }
}




