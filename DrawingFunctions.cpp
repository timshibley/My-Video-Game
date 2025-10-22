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
   // Rectangle reference = visibleGridLocations[0][0]->rectangle;
    for (float i = 0; i < visibleGridLocations.size(); i++) {
        for (float j = 0; j < visibleGridLocations[i].size(); j++) {

            DrawRectangleRec({j*100+topLeftCornerXPos, i*100+topLeftCornerYpos, visibleGridLocations[i][j]->rectangle.width, visibleGridLocations[i][j]->rectangle.height}, visibleGridLocations[i][j]->color);

            if (visibleGridLocations[i][j]->entity != nullptr) {
                if (visibleGridLocations[i][j]->entity->isVisible()) {
                    DrawTexture(visibleGridLocations[i][j]->entity->getTexture(), j*100+topLeftCornerXPos, i*100+topLeftCornerYpos, WHITE );
                }
            }
        }
    }
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
    DrawTexture(playerAttackTextures[currentFireAttackFrame], visibleGridLocations[playerY][playerX]->rectangle.x, visibleGridLocations[playerY][playerX]->rectangle.y,WHITE);
    if (GetTime()-attackStartTime > 1) {
        Enemy* temp = player.adjacentEnemy(player.getLookingDirection());
        if (temp != nullptr) {
            temp->setCurrentHP(temp->getCurrentHP() - 5);
            if (temp->getCurrentHP() <= 0) {
                temp->setVisibility(false);
                visibleGridLocations[temp->getYVisibleCoordinate()][temp->getXVisibleCoordinate()]->entity = nullptr;
                entityManager->deleteEntity(temp);
            }
        }
        attackTracker = EXECUTE_NOTHING;
        turnTracker = OPPONENTTURN;
    }
}

void changeFrames() {
    frameTime = GetTime();
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