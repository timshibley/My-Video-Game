//
// Created by shibl on 1/28/2025.
//

#include "DrawingFunctions.h"

#include "Enemy.h"
#include "Macros.h"
#include "main.h"

//Draws in order of top to bottom. Things on the bottom are drawn over the top things.
void checkDrawing() {
    ClearBackground(backgroundColor);
   // Rectangle reference = visibleTiles[0][0]->rectangle;
    for (float i = 0; i < visibleTiles.size(); i++) {
        for (float j = 0; j < visibleTiles[i].size(); j++) {

            DrawTexture(visibleTiles[i][j]->texture,j*(int)(visibleTiles[i][j]->location.rectangle.width)+topLeftCornerXPos, i*(int)(visibleTiles[i][j]->location.rectangle.height)+topLeftCornerYpos, WHITE );
            if (visibleTiles[i][j]->location.entity != nullptr) {
                if (visibleTiles[i][j]->location.entity->isVisible()) {
                    DrawTexture(visibleTiles[i][j]->location.entity->getTexture(), j*(int)(visibleTiles[i][j]->location.rectangle.width)+topLeftCornerXPos, i*(int)(visibleTiles[i][j]->location.rectangle.height)+topLeftCornerYpos, WHITE );
                }
            }
        }
    }
    //Decides what needs to be drawn.
    if (attackTracker == EXECUTE_FIRE_ATTACK) {
        attackTracker = ANIMATE_FIRE_ATTACK;
        attackStartTime = GetTime();
        turnTracker = ANIMATION_IN_PROCESS;
        currentFireAttackFrame = FIRST_FRAME_FIRE_ATTACK;
    }
    if (attackTracker == ANIMATE_FIRE_ATTACK) {
        drawFireAttack();
    }
    if (mainMenu.getVisibility()) {
        mainMenu.draw();
    }
}

void drawFireAttack() {
    int playerX = player.getXVisibleCoordinate();
    int playerY = player.getYVisibleCoordinate();
    //Determines where it should drawn
    switch (player.getLookingDirection()) {
        case UP:
            playerY -= 1;
        break;
        case DOWN:
            playerY += 1;
        break;
        case LEFT:
            playerX -= 1;
        break;
        case RIGHT:
            playerX += 1;
        break;
        default:
            break;
    }
    //Draws the fire
    DrawTexture(playerAttackTextures[currentFireAttackFrame],playerX*visibleTiles[playerY][playerX]->location.rectangle.width+topLeftCornerXPos, playerY*visibleTiles[playerY][playerX]->location.rectangle.width+topLeftCornerYpos,WHITE);
    //Performs the damage and moves the turn tracker.
    if (GetTime()-attackStartTime > 1) {
        Enemy* temp = player.adjacentEnemy(player.getLookingDirection());
        if (temp != nullptr) {
            temp->setCurrentHP(temp->getCurrentHP() - 5);
            if (temp->getCurrentHP() <= 0) {
                temp->setVisibility(false);
                visibleTiles[temp->getYVisibleCoordinate()][temp->getXVisibleCoordinate()]->location.entity = nullptr;
                entityManager->deleteEntity(temp);
            }
        }
        attackTracker = EXECUTE_NOTHING;
        turnTracker = OPPONENTTURN;
    }
}

//This function changes frames
void changeFrames() {
    frameTime = GetTime();

    //This updates every single entities frames.
    if (frameTime - previousFrameTime > .2) {
        previousFrameTime = frameTime;
        for (int i = 0; i < entityManager->lengthOfID(MONSTER_ID); i++) {
            EntityNode* enemy = entityManager->findNthEntry(MONSTER_ID, i);
            enemy->entry->textureTracker++;
            if (enemy->entry->textureTracker == enemyTextures.size()) {
                enemy->entry->textureTracker = 0;
            }
            enemy->entry->setTexture(enemyTextures[enemy->entry->textureTracker]);
        }

        //Light like 3 clock cycle optimization.
        if (attackTracker == ANIMATE_FIRE_ATTACK) {
            currentFireAttackFrame++;
            if (currentFireAttackFrame >= 3) {
                currentFireAttackFrame = 0;
            }
        }

    }

}
